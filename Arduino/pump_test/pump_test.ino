int ACWATERPUMP = 13; //You can remove this line, it has no use in the program.
//int sensor = A0; //You can remove this line, it has no use in the program.
int val; //This variable stores the value received from Soil moisture sensor.
void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT); //Set pin 13 as OUTPUT pin, to send signal to relay
  pinMode(A0,INPUT); //Set pin 8 as input pin, to receive data from Soil moisture sensor.
}

void loop() { 
  val = digitalRead(8);
  Serial.println(val); //Read data from soil moisture sensor  
//if(val>=300)
  if(val == LOW) 
  {
 digitalWrite(13,LOW); //if soil moisture sensor provides LOW value send LOW value to relay
  }
  else
  {
  digitalWrite(13,HIGH); //if soil moisture sensor provides HIGH value send HIGH value to relay
  }
  delay(400); //Wait for few second and then continue the loop.
}
