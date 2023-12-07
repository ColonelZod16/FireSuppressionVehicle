#include <RH_ASK.h>
#include <SPI.h>
const int vrx = 0;
const int vry = 1;
const int sw = 2;
RH_ASK driver;
void setup() {
  pinMode(sw, INPUT);
  digitalWrite(sw, HIGH);
  Serial.begin(9600);
  if (!driver.init())
    Serial.println("init failed");
}
void loop() {
  int xValue = analogRead(vrx);
  int yValue = analogRead(vry);
  Serial.print("Switch:  ");
  Serial.print(digitalRead(sw));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(xValue);
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(yValue);
  Serial.print("\n\n");
  delay(500);
  const char *msg; 
  if (xValue < 300) {
    msg = "1";
  } else if (xValue > 700) {
    msg = "2";
  } else if (yValue < 300) {
    msg = "3";
  } else if (yValue > 700) {
    msg = "4";
  } else {
    msg = "5";
  }
  
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  delay(100);
}
