#include <SimpleDHT.h>
#include <LiquidCrystal.h>

int pinDHT11 = 8;
SimpleDHT11 dht11(pinDHT11);

int sensorValue;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  Serial.begin(9600);

  pinMode(13,OUTPUT);
  pinMode(A1,INPUT);

  lcd.begin(20, 4);

}

void loop()
{
  Serial.println("=================================");
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
    Serial.print("Read DHT11 failed, err=");
    Serial.println(err);
    delay(1000);
    return;
  }
  Serial.print("Temperature :");
  Serial.print((int)temperature);
  Serial.println(" *C, ");
  Serial.print("Humidity :");
  Serial.print((int)humidity);
  Serial.println("% H");

  delay(1500);

Serial.println("=================================");

  sensorValue = analogRead(A0);
  Serial.print("Air Quality Value :");
  Serial.println(sensorValue);
  
  delay(1000);


Serial.println("=================================");

  int moistureValue = analogRead(A1);
  Serial.print("Soil Moisture :");
  Serial.println(moistureValue);
  delay(1000);

Serial.println("=================================");


lcd.print("Temperature : ");
lcd.print(temperature);
lcd.print(" *C, ");


lcd.setCursor(0, 1);
lcd.print("Humidity : ");
lcd.print(humidity);
lcd.print("% H");


lcd.setCursor(0, 2);
lcd.print("Air Quality : ");
lcd.print(sensorValue);

lcd.setCursor(0, 3);
lcd.print("Soil Moisture : ");
lcd.print(moistureValue);

lcd.setCursor(0, 0);

if(moistureValue<=300)
{
  digitalWrite(13,HIGH);
}
else
{
  digitalWrite(13,LOW);
}
delay(5000);
}
