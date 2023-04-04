#include <virtuabotixRTC.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
// definitions for the lcd 
#define I2C_ADDR 0x27
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
// definitons for the dht11 or dht22
#define DHTPIN 2
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
virtuabotixRTC myRTC(6, 7, 8); 
DHT dht(DHTPIN,DHT11);

void setup() {
 Serial.begin(9600);
 dht.begin();
 lcd.begin (16,2); 
 lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
 lcd.setBacklight(HIGH);
 lcd.home ();

 myRTC.setDS1302Time(50, 43, 9, 2, 4, 4, 2023); // enter in (second, minute, hour, day of the week, day of the month, month, year) format, all int
 // this line is for setting the time up. first, write the time and date you want and upload, then delete or comment this line and upload again
}

void loop() {
lcd.clear(); 
myRTC.updateTime();

int hum  = dht.readHumidity();    // read humidity
int temp = dht.readTemperature(); // read temperature
  
 lcd.setCursor(0,0); //first row of the LCD
 lcd.print(myRTC.dayofmonth);
 lcd.print("/");
 lcd.print(myRTC.month);
 lcd.print("/");
 lcd.print(myRTC.year);
// days of the week conditions, if you use sunday as the first day of the week, change the numbers 
if (myRTC.dayofweek == 1)
lcd.print("  Mon");
if (myRTC.dayofweek == 2)
lcd.print("  Tue");
if (myRTC.dayofweek == 3)
lcd.print("  Wed");
if (myRTC.dayofweek == 4)
lcd.print("  Thu");
if (myRTC.dayofweek == 5)
lcd.print("  Fri");
if (myRTC.dayofweek == 6)
lcd.print("  Sat");
if (myRTC.dayofweek == 7)
lcd.print("  Sun");

lcd.setCursor(0,1); // second line of the LCD
lcd.print(myRTC.hours);
lcd.print(":");
lcd.print(myRTC.minutes);
lcd.print(":");
lcd.print(myRTC.seconds);
lcd.print(" ");
lcd.print(temp);
lcd.print((char)223); // code for the ° character
lcd.print("C");
lcd.print(" ");
lcd.print(hum);  
lcd.print("%");
delay(1000);
}