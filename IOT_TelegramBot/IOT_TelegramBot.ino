#include <CTBot.h>

CTBot myBot;

String ssid = "AGNI_2021";
String pass = "AGNI_2021";
String token = "5137592914:AAEW13gp0Sfaj8kUgHRFMByfh6HeOG2S4F8";
const int id = 1375638875;

void setup() {
  
  // put your setup code here, to run once:
  Serial.begin (9600);
  Serial.println ("Starting telegramBot...");
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken (token);

  if (myBot.testConnection()){
    Serial.println("koneksi bagus");
  }else{
    Serial.println ("koneksi jelek");
  }

  myBot.sendMessage(id, "Tes kelas Robot");
  Serial.println ("Pesan Terkirim");
}

void loop() {
  // put your main code here, to run repeatedly:

}
