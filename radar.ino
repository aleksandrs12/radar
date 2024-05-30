#include <Servo.h>
#include <SPI.h>
#include <SD.h>


File myFile;
String Input;

Servo myservo; 
int val;
int inc = 10;

const int trigPin = 6;  
const int echoPin = 7; 
float duration, distance;  

void setup() {

  
  pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);  
  pinMode(8, OUTPUT);

  myservo.attach(4);

	Serial.begin(9600);
  Serial.setTimeout(1); 



}

void loop() {
  val += inc;
  if (val > 180){
    val = 180;
    inc *= -1;
  }
  if (val < 0){
    val = 0;
    inc *= -1;
  }
  myservo.write(val);

  delay(50);  

  digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;  
  Serial.print(val);  
  Serial.print(" ");
	Serial.println(distance);  

	delay(50);  

}
