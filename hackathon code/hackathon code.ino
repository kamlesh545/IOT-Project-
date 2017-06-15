
#include <LiquidCrystal.h>
#include "DHT.h"


#define DHTPIN 9


LiquidCrystal lcd(10, 11, 8, 7, 6, 5);
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
char incomingByte; 
int  LED = 12;
void setup() {
  
    pinMode(LED, OUTPUT);
  lcd.begin(16, 2);
  dht.begin();
  
  
  lcd.print("Welcome !!!! ");
  delay(5000);
  lcd.clear();
    lcd.setCursor(0,0);

  lcd.print("Temp:  Humidity:");
}
void loop() {
  delay(500);
   if (Serial.available() > 0) {  
    incomingByte = Serial.read(); 
    if(incomingByte == '0') {
       digitalWrite(LED, LOW);  
    }
    if(incomingByte == '1') {
       digitalWrite(LED, HIGH); 
    }
  }
  
  lcd.setCursor(0, 1);
  
  int h = dht.readHumidity();
  
  float f = dht.readTemperature(true);

  //int c = (f  -  32)  *  5/9;

  if (isnan(h) || isnan(f)) {
    lcd.print("ERROR");
    return;
  }
    int c = (f  -  32)  *  5/9;
  lcd.print(c);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(7,1);
  lcd.print(h);
  lcd.print("%");  
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
    lcd.print("Contact Us");
      lcd.setCursor(0, 1);
lcd.print("9856235698");
delay(5000);
lcd.clear();
  lcd.print("Temp:  Humidity:");
}
