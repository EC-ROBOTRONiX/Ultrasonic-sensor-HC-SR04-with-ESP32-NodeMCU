/*
  HC-SR04

  Vcc to 5V Pin of the Arduino.
  Gnd to Gnd Pin of the Arduino.
  Trig to Digital Pin 9 .
  Echo to Digital Pin 10.
*/
#include <DHT.h>
#include <WiFi.h>
#include <MQ135.h>
#include <ThingSpeak.h>

const int trigPin = 35; //5
const int echoPin = 34; //6
const int buzzer = 32;  //7
const char* ssid = "BitByte_Robotronix";
const char* pass = "Bitbytedikwzceh@";
unsigned long myChannelNumber = 1548426;
const char * myWriteAPIKey = "0NNDK9YTGFVOYCZL";
WiFiClient client;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  Serial.print("Connecting to Wi-Fi : ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
   Serial.println("");
   Serial.println("WiFi connected\n");
   delay(500);
   ThingSpeak.begin(client);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm.");
  Serial.println("\n...Sending data to cloud...\n");
  Serial.println("------------------------------------------------------------------------------------------\n");
  ThingSpeak.setField(1, distance);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
//  delay(5000); 
  if(distance > 25)
  {
    digitalWrite(buzzer, LOW);  
  }
  else
  {
    digitalWrite(buzzer, HIGH);
  }
  
}
