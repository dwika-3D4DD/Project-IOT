#include <ESP32Servo.h>

#include "CTBot.h"
CTBot myBot;

//#include <Servo.h>
const int trigPin = 14;
const int echoPin = 12;
const int led = 2;
//Servo servo;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
int i = 0;

String ssid = "AGNI_2021";
String pass = "AGNI_2021";
String token = "5244122309:AAHinraMeVCliDsapx8X2g3OgE1a2zaSzxg";
const int id = 1080766143;

Servo myServo;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);

  myServo.attach(27, 1000, 2000);
  digitalWrite(led, LOW);
  myServo.write(10);
  
  Serial.println("Starting TelegramBot...");

  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);

  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");

}

void loop() {
  TBMessage msg;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED / 2;

  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  if (distanceCm <= 60) {
    Serial.println("Jarak kurang dari 60 cm");
    digitalWrite(led, LOW);
    delay(2000);
    myServo.write(170);
    delay(5000);
    myServo.write(10);
    i++;
  } else {
    Serial.println("Jarak lebih dari 60 cm");
    digitalWrite(led, HIGH);
    myServo.write(10);
    delay (100);
  }
  Serial.println("=======================================");

  delay(50);
  Serial.print("Total steril: ");
  Serial.println(i);
  if (CTBotMessageText == myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("jumlah sterilisasi")) {
      myBot.sendMessage(id, String(i));
    }
    else if (msg.text.equalsIgnoreCase("jarak")){
      myBot.sendMessage(id, String(distanceCm));
    }
    else {
      myBot.sendMessage(id, "Wrong message, try again");
    }
  }
}
