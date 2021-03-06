/*
  Devices used:
  LCD Display: LCM 1602 IIC V1
  Distance Ultrasonic Measurment: HC-SR04
*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define trigPin 2
#define echoPin 3

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 4 lines and 20 chars

int led = 6; // the pin the LED is connected to

void setup()
{
  pinMode(trigPin, OUTPUT); //Pin, with trig as exit
  pinMode(echoPin, INPUT); //pin with echo as enter point
  lcd.init(); // initialize the lcd.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("STAY AWAY!");
  pinMode(led, OUTPUT);
}

void loop()
{
  lcd.setCursor(2,1);
  lcd.print("Something is");
  lcd.setCursor(10,2);
  lcd.print(measure_distance());
  lcd.setCursor(2,3);
  lcd.print("cms away!");
  digitalWrite(led, HIGH);
  delay(5000);
  digitalWrite(led, LOW);
  delay(2000);
  lcd.clear();
}

//this method relies on the impuls devise documentation https://www.mpja.com/download/hc-sr04_ultrasonic_module_user_guidejohn.pdf
int measure_distance ()
{
  long time, distance;
  
  digitalWrite(trigPin, LOW);  //set low state for 2 uS - initilize impuls
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  //set high state for 10 uS - initilize impuls
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  time = pulseIn(echoPin, HIGH);
  distance = time / 58; //width of reflected impuls in uS divided by 58  gives length in cm

  return distance;
}
