#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <Servo.h>
#include <SD.h>

#define TFT_CS        10
#define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8


//pins
//gnd - gnd
//Vdd - 5V
//SCL - D13
//SDA - D11
//RST - D9
//DC - D8
//CS - D10
//BLK - 3.3V


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
float p = 3.1415926;

bool newData;
char recievedChar;

Servo myservo; 
const int trigPin = 6;  
const int echoPin = 7; 
float duration, distance;  

int val;
int inc = 2;

int id = 0;

int objectY;
int objectX;
int lastObjectY;
int lastObjectX;

void setup(void) {
  pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);  
  myservo.attach(4);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));

  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab


  Serial.println(F("Initialized"));

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);


  tft.fillScreen(ST77XX_BLACK);
  tft.fillCircle(64, 90, 53, 0x0184);
  tft.fillCircle(64, 90, 50, 0x03EA);


  // a single pixel
  //tft.drawPixel(tft.width()/2, tft.height()/2, ST77XX_GREEN);
}

void loop() {
  val += inc;
  if (val > 180){
    val = 180;
    inc *= -1;

    tft.fillScreen(ST77XX_BLACK);
    tft.fillCircle(64, 90, 53, 0x0184);
    tft.fillCircle(64, 90, 50, 0x03EA);
    
  }
  if (val < 0){
    val = 0;
    inc *= -1;

    tft.fillScreen(ST77XX_BLACK);
    tft.fillCircle(64, 90, 53, 0x0184);
    tft.fillCircle(64, 90, 50, 0x03EA);
  }
  myservo.write(val);

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


  
  if (distance > 100){
    distance = 100;
  }

  objectX = cos(0.01745329 * val) * (distance / 2) +64;
  objectY = sin(0.01745329 * val) * (distance / 2) +90;
  
  tft.drawLine(64, 90, objectX, objectY, 0xFFFF);
  tft.drawLine(64, 90, lastObjectX, lastObjectY, 0x03EA);
  tft.fillCircle(objectX, objectY, 2, 0xF800);
  

  lastObjectY = objectY;
  lastObjectX = objectX;
  

  /*
  tft.setCursor(tft.width()/2 - 2*8, tft.height()/2-8 + 16);
  tft.setTextColor(0xFFFF);
  tft.setTextWrap(true);
  tft.print("Radar");

  tft.drawLine(43, 24, 72, 53, 0xBFBF);
  tft.fillRect(51, 61, 6, 5, 0xFFE0);
  tft.fillCircle(centreX, centreY, topR, lineColor);
  */

  
}





