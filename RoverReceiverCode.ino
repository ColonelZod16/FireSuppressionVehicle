#include <RH_ASK.h>
#include <SPI.h>
#include <string.h>

RH_ASK driver;

int in1 = 5;
int in2 = 4;
int enA = 2;
int in3 = 8;
int in4 = 9;
int enB = 12; // Example motor B pin for direction control
int trig = 13;
int echo = 10;
int comm =7;
// Define constants for motor control
const int motorSpeed = 255; // Speed value (0-255) for both motors
const unsigned long turnDuration = 500; // Duration for a 90-degree turn in milliseconds

void setup() {
  Serial.begin(9600);
  pinMode(comm,INPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  if (!driver.init())
    Serial.println("init failed");
}
long getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  long duration = pulseIn(echo, HIGH);
  long distance = duration * 0.034 / 2; // Speed of sound is 0.034 cm/microsecond
  
  return distance;
}
void performAction(const char* action) {
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);
  int c = digitalRead(comm);
  Serial.println(c);
  if (strcmp(action, "1") == 0 && c==1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);    //move forward
    digitalWrite(in4, HIGH);   // Set motor B speed
  } else if (strcmp(action, "2") == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);   // Set motor A speed
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else if (strcmp(action, "3") == 0) {
    // Right turn for 90 degrees
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);   //right turn
    digitalWrite(in4, LOW);
    delay(turnDuration);
    stopMotors();
  } else if (strcmp(action, "4") == 0) {
    // Left turn for 90 degrees
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(turnDuration);
    stopMotors();
  } else {
    stopMotors();
  }
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)) {
    buf[buflen] = '\0';
    Serial.print("Received: ");
    Serial.println((char*)buf);
    performAction((char*)buf);
  }
}
