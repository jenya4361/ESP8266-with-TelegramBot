#include <ESP8266WiFi.h>
#include "TelegramBot.h"
const char* ssid = "TPLink-12345";
const char* password = "12345678";

const char* botToken = "Your bot token.";

// Telegram chat ids
unsigned int recipients[] = 
{
  111111111,
  222222222
};

void setup() {

  // Connecting
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while( WiFi.status() != WL_CONNECTED )
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Initializing
  TelegramBot::Instance()->init( botToken, recipients );

  // Send msg
  TelegramBot::Instance()->sendMessage( "Somebody Opened Your Door!" );
}

void loop() {
}
