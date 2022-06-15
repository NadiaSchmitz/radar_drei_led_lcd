#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);
int led_rot = 8;
int led_gelb = 12;
int led_gruen = 13;
int echo_pin = 3;
int trig_pin = 2;
int entfernung;
int zeit;

void setup() {
  Serial.begin(9600);
  lcd.init();   
  lcd.backlight();
  
  pinMode(echo_pin, INPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(led_rot, OUTPUT);
  pinMode(led_gelb, OUTPUT);
  pinMode(led_gruen, OUTPUT);
}

void loop() {
  
  digitalWrite(trig_pin, HIGH);
  delay(1000);
  digitalWrite(trig_pin, LOW);
  zeit = pulseIn(echo_pin, HIGH);
  entfernung = (zeit / 2) / 29.1;
 Serial.print("Entfernung ");
  if (entfernung < 10) {
    lcd.setCursor(0,0);
    lcd.println("Gefahr          ");
    lcd.setCursor(0,1);
    lcd.println("*** Rot ***          ");
    digitalWrite(led_rot, HIGH);  
    digitalWrite(led_gelb, LOW);
    digitalWrite(led_gruen, LOW);
  } else if (entfernung >= 10 & entfernung < 20) {
    lcd.setCursor(0,0);
    lcd.println("Warnung          ");
    lcd.setCursor(0,1);
    lcd.println("*** Gelb ***          ");
    digitalWrite(led_rot, LOW);  
    digitalWrite(led_gelb, HIGH);
    digitalWrite(led_gruen, LOW);
  } else {
    lcd.setCursor(0,0);
    lcd.println("Ruhe              ");
    lcd.setCursor(0,1);
    lcd.println("*** Gruen ***          ");
    digitalWrite(led_rot, LOW);  
    digitalWrite(led_gelb, LOW);
    digitalWrite(led_gruen, HIGH);
  }

  Serial.print("Entfernung ");
  Serial.print("Led_Rot  ");
  Serial.print("Led_Gelb  ");
  Serial.print("Led_Gruen  ");
  Serial.println();
  Serial.print(entfernung);
  Serial.print("          ");
  Serial.print(digitalRead(led_rot));
  Serial.print("        ");
  Serial.print(digitalRead(led_gelb));
  Serial.print("         ");
  Serial.print(digitalRead(led_gruen));
  Serial.println();
  delay(1000);
}
