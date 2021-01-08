/*
  Devices used:
  LCD Display: LCM 1602 IIC V1
  Distance Ultrasonic Measurment: HC-SR04
  Two LEDs with resistors
*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define trigPin 2
#define echoPin 3

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 4 lines and 20 chars

int ledGreen = 6; // the pin the LED is connected to
int ledRed = 7; // the pin the LED is connected to
long distance;

void setup() {
  pinMode(trigPin, OUTPUT); //Pin, with trig as exit
  pinMode(echoPin, INPUT); //pin with echo as enter point
  lcd.init(); // initialize the lcd.
  lcd.backlight();
  lcd.setCursor(3,0);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
}

void loop() {
  lcd.setCursor(0,1);
  lcd.print("Distance(CM): ");
  lcd.setCursor(15,1);
  lcd.print(measure_distance());
  lcd.setCursor(2,3);
  if (distance < 50) {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
    lcd.print("I NEED AN ADULT!");
  } else {
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
    lcd.print("This is alright");
  }
  delay(5000);
  lcd.clear();
}

int measure_distance ()
{
  long time;
  digitalWrite(trigPin, LOW);  //set low state for 2 uS - initilize impuls
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  //set high state for 10 uS - initilize impuls
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  time = pulseIn(echoPin, HIGH);
  distance = time / 58; //width of reflected impuls in uS divided by 58  gives length in cm

  return distance;
}
