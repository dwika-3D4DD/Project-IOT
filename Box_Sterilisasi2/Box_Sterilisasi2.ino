#include <ESP32Servo.h>

const int trigPin = 12;
const int echoPin = 14;

Servo myServo;

const int relay = 2;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034

long duration;
float distanceCm;
int i = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relay, OUTPUT);

  myServo.attach(27);
  digitalWrite(relay, LOW);
  myServo.write(0);
  }

void loop() {

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
    digitalWrite(relay, LOW);
    delay(2000);
    myServo.write(225);
    delay(5000);
    myServo.write(0);
    digitalWrite(relay, HIGH);
    delay (10000);
    digitalWrite(relay, LOW);
    delay(2000);
    myServo.write(225);
    delay(5000);
    myServo.write(0);
    i++;
  } else {
    Serial.println("Jarak lebih dari 60 cm");
    digitalWrite(relay, LOW);
    delay (100);
  }
  Serial.println("=======================================");

  delay(50);
  Serial.print("Total steril: ");
  Serial.println(i);
  Serial.println(" ");
}
