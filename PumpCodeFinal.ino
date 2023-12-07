const int pump = 9;
const int S1 = 8;
const int S3 = 6;
const int S4 = 5;
const int TRIG_PIN =3   ; 
const int ECHO_PIN =4   ; 
const int LED_PIN =13;
const int trig=12;
const int echo=2;
const int comm=7;
#include <Servo.h>
Servo myservo;
int pos=0;
long dist(){
  long duration, distance; // Variables to hold the duration and distance measurements
  digitalWrite(trig, LOW); // Ensure the trigger pin is low initially
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(trig, HIGH); // Send a 10 microsecond pulse to trigger the sensor
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH); // Read the pulse from the echo pin// Calculate distance in centimeters based on the speed of sound (343m/s)
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  if(distance>15){
    digitalWrite(comm,HIGH);
  }else{
    digitalWrite(comm,LOW);
  }
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);
  
}
void setup(){
  Serial.begin(9600);
  pinMode(pump,OUTPUT);
  pinMode(S1,INPUT);
  pinMode(S3,INPUT);
  pinMode(S4,INPUT);
  myservo.attach(10);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(comm,OUTPUT);
}
void loop(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance_cm = duration * 0.034 / 2;
  dist();
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  int north = digitalRead(S1);
  int east = digitalRead(S3);
  int west = digitalRead(S4);


  if (distance_cm >=7
  ) {
    digitalWrite(LED_PIN, HIGH);  
    Serial.println("Water level is below req. LED is ON.");
    pos=90;
    myservo.write(pos); 
    digitalWrite(pump,HIGH);  
    delay(1000);
  } 
  else {
    digitalWrite(LED_PIN, LOW); 
    Serial.println("Water level is above req. LED is OFF.");
    delay(100);

  int north = digitalRead(S1);
  int east = digitalRead(S3);
  int west = digitalRead(S4);
  Serial.print("north");
  Serial.println(north);
  Serial.print("east");
  Serial.println(east);
  Serial.print("west");
  Serial.println(west);

  if(north == 0){
    pos = 0;
    myservo.write(pos);
//    delay(500);
    delay(1000);
    digitalWrite(pump,LOW);    
  }
//  else if(south == 0){
//    pos = 45;
//    myservo.write(pos);
//    delay(500);
//    digitalWrite(pump,LOW);    
//  }
  else if(west == 0){
    pos =90;
    myservo.write(pos);
    delay(1000);
    digitalWrite(pump,LOW);    
  }
  else if(east == 0){
    pos = 180;
    myservo.write(pos);
//    delay(500);
    delay(1000);
    digitalWrite(pump,LOW);
  }
  
  else{
    digitalWrite(pump,HIGH);
    pos=90;
    myservo.write(pos);
  } 
  
  Serial.println(pos);
  delay(1000);
}


}
