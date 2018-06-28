#include <ESP8266WiFi.h>
#include "TelegramBot.h"
const char* ssid = "Rexxar";
const char* password = "na46-w3cp-16yg";

unsigned long long int prev = 0;
bool isValOne = false;
TelegramBot bot;
void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Use WiFiClientSecure class to create TLS connection
  bot.init();
  bot.sendMessage("Somebody Opened Your Door!",316978348);
}

void loop() {
}
