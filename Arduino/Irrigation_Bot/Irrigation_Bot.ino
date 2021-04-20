#include <SimpleDHT.h>
#include <LiquidCrystal.h>

int pinDHT11 = 40;
SimpleDHT11 dht11(pinDHT11);



int gasValue;



const int trigPin = 49;
const int echoPin = 47;

long duration;
int distance;



const int buzzer = 44;




const int rs = 12, en = 11, d4 = 22, d5 = 26, d6 = 30, d7 = 34;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);




#define LM1 2 
#define LM2 3 
#define RM1 4 
#define RM2 5 


char val;


void setup() 
{
  pinMode(buzzer, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.begin(20, 4);

pinMode(51, OUTPUT);
digitalWrite(51, HIGH);
pinMode(53, OUTPUT);
digitalWrite(53, HIGH);

pinMode(LM1, OUTPUT);
pinMode(LM2, OUTPUT);
pinMode(RM1, OUTPUT);
pinMode(RM2, OUTPUT);

  Serial.begin(9600);
}


void loop() 
{

  // Soil Moisture Code Start
  
  int moistureValue = analogRead(A1);
  Serial.print("Soil Moisture : ");
  Serial.println(moistureValue);
  if(moistureValue<380)
  {
    Serial.println("The Soil is Highly Moist");
  }
  else if(moistureValue>=380 && moistureValue<650)
  {
    Serial.println("The Soil is Moderately Moist");
  }
  else if(moistureValue>=650 && moistureValue<900)
  {
    Serial.println("The Soil is Dry");
  }
    else if(moistureValue>=900)
  {
    Serial.println("The Soil is Very Dry");
    Serial.println("Urgently Need Water Irrigation !!");
  }
  Serial.println("***************************************************************");
  delay(100); 

  // SoilMoisture Code End




  // dht11 Code Start

  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
  {
    Serial.print("Read DHT11 failed, err=");
    Serial.println(err);
    delay(100);
    return;
  }

   Serial.print("Temperature :");
  Serial.print((int)temperature);
  Serial.println(" *C  "); 
  Serial.println("***************************************************************");

  Serial.print("Humidity :");
  Serial.print((int)humidity);
  Serial.println("% H");
  
  Serial.println("***************************************************************");
  delay(150);

  //dht11 Code End





//MQ135 COde Start

gasValue = analogRead(A0);
Serial.print("Air Quality : ");
Serial.println(gasValue);

if(gasValue<=95)
{
  Serial.println("Normal Air");
}
else if(gasValue>95 && gasValue<=150)
{
  Serial.println("Moderately Affected Air Quality");
}
else if(gasValue>150 && gasValue<=250)
{
  Serial.println("High Affected Air Quality");
}
else if(gasValue>250)
{
  Serial.println("Very Highly Affected Air Quality");
}

Serial.println("***************************************************************");
  delay(150);

  //MQ135 Code End





//HC-SR04 Code Start

digitalWrite(trigPin, LOW);
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distance= duration*0.034/2;

Serial.print("Water Level : ");
Serial.println(distance);

Serial.println("***************************************************************");
  delay(150);
  
//HC-SR04 Code Start






// Buzzer Code Start

if(distance>=9)
{
  tone(buzzer, 1000); 
  delay(5000);       
  noTone(buzzer);     
  delay(50); 
}


if(humidity>=65)
{
  tone(buzzer, 1000); 
  delay(5000);       
  noTone(buzzer);     
  delay(50); 
}


//Buzzer Code End  






//LCD Code Start

lcd.print("Temp.:");
lcd.print(temperature);
lcd.print("*C");
lcd.print(",");
lcd.print("Water:");
lcd.print(distance);

lcd.setCursor(0, 1);
lcd.print("Humidity : ");
lcd.print(humidity);
lcd.print("% H");


lcd.setCursor(0, 2);
lcd.print("Air Quality :");
lcd.print(gasValue);  
if(gasValue<=120)
{
  lcd.print(",Pure");
}
else
{
  lcd.print(",Impure");
}



lcd.setCursor(0, 3);
lcd.print("Moisture:");
lcd.print(moistureValue);
if(moistureValue<400)
{
  lcd.print(",Wet");
}
else if(moistureValue>=400 && moistureValue<=750)
{
  lcd.print(",Moist");
}
else if(moistureValue<400)
{
  lcd.print(",Dry");
}


lcd.setCursor(0, 0);

//LCD Code End





// RelayModule Code Start

if(moistureValue>=850)
{
  digitalWrite(51,LOW);
}
else
{
  digitalWrite(51,HIGH);
}
delay(200);




if(temperature>=32)
{
  digitalWrite(53,LOW);
}
else
{
  digitalWrite(53,HIGH);
}
delay(200);




if(gasValue>=200)
{
  digitalWrite(53,LOW);
}
else
{
  digitalWrite(53,HIGH);
}
delay(200);


//RelayModule Code End 






//Bluetooth Bot Code Start

while (Serial.available() > 0)
  {
  val = Serial.read();
  Serial.println(val);
  }
 
  if( val == 'F') // Forward
    {
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);  
    }
  else if(val == 'B') // Backward
    {
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH); 
    }
  
    else if(val == 'L') //Left
    {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    }
    else if(val == 'R') //Right
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW); 
    }
    
  else if(val == 'S') //Stop
    {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW); 
    }
  else if(val == 'I') //Forward Right
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    }
  else if(val == 'J') //Backward Right
    {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    }
   else if(val == 'G') //Forward Left
    {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    }
  else if(val == 'H') //Backward Left
    {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH); 
    }

//Bluetooth Bot Code End



delay(100);

}
