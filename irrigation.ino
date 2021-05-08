#include <DHT.h>
//#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = A1, d4 = 12, d5 = 11, d6 = 10, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define DHTPIN   2        // GPIO Pin where the dht11 is connected
DHT dht(DHTPIN, DHT11);
const int moisturePin = A0;             // moisteure sensor pin
const int ldrPin = A2;
const int relay = 4;
const int relay2 = 3;
unsigned long interval = 10000;
unsigned long previousMillis = 0;
unsigned long interval1 = 1000;
unsigned long previousMillis1 = 0;
float moisturePercentage;              //moisture reading
float h;                  // humidity reading
float t;                  //temperature reading
unsigned long timer=0;
void setup()
{
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.print("hello, world!");
  delay(10);
  pinMode(ldrPin, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(relay2, OUTPUT);
  dht.begin();
  digitalWrite(relay, LOW);
}

void loop()
{
  lcd.clear();
  unsigned long currentMillis = millis(); // grab current time
  int ldrStatus = analogRead(ldrPin);
  ldrStatus = map(ldrStatus,0,1023,0,100);
 //Serial.print(" ldr: :");
 //Serial.print(ldrStatus);
  h = dht.readHumidity();     // read humiduty
  t = dht.readTemperature();     // read temperature
   //Serial.print(" Temperature: :");
   //Serial.print(t);
   //Serial.print(" C, Humidity: :");
   //Serial.print(h);
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.setCursor(5,0);
  lcd.print(t);
  lcd.setCursor(9,0);
  lcd.print("Hum:");
  lcd.setCursor(14,0);
  lcd.print(h);
  lcd.setCursor(0,1);
  lcd.print("light:");
  lcd.setCursor(7,1);
  lcd.print(ldrStatus);
  lcd.print("%");
  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  moisturePercentage = analogRead(moisturePin);
  moisturePercentage= map(moisturePercentage,1023,0,0,100);
  lcd.setCursor(9,1);
  lcd.print("moi:");
  lcd.setCursor(13,1);
  lcd.print(moisturePercentage);
  delay(100);
/*  if ((unsigned long)(currentMillis - previousMillis1) >= interval1) {
   //Serial.print("Soil Moisture is  = ");
   //Serial.print(moisturePercentage);
   //Serial.println("%");
    previousMillis1 = millis();
    delay(1000);
  }*/
  if(millis()-timer>10000)
  {
    Serial.println("$"+String(t)+","+String(h)+","+String(moisturePercentage)+",");
    timer=millis();
  }

if (moisturePercentage<30) {
  digitalWrite(relay2, HIGH);
  lcd.clear(); 
  lcd.setCursor(0,0);
  lcd.print("DRY soil");
  lcd.setCursor(0,1);
  lcd.print("pump on");// tun on motor
  delay(1000);
}
else
{
  digitalWrite(relay2, LOW); 
}
if (h> 80) {
  digitalWrite(relay, HIGH);   
  lcd.clear(); 
  lcd.setCursor(0,0);
  lcd.print("high humidity");
  lcd.setCursor(0,1);
  lcd.print("bulb on");// tun on motor
  delay(1000);
}
else
{
  digitalWrite(relay, LOW); 
}
}
