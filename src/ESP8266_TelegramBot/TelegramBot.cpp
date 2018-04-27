#include <ArduinoJson.h>

#include "TelegramBot.h"

void TelegramBot::init()
{
  Serial.print("connecting to ");
  Serial.println(host);
  if (!m_client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (m_client.verify(fingerprint, host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }

}

String TelegramBot::makeRequest(String url)
{
  Serial.print("requesting URL: ");
  Serial.println(url);

  m_client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (m_client.connected()) {
    String line = m_client.readStringUntil(']') + "}";
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = m_client.readStringUntil(']') + "}";
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");

  return line;
}
  
void TelegramBot::sendMessage(char* text, unsigned int chatId)
{
  String url = "/bot" + botToken + "/sendMessage?chat_id=" + static_cast<String>(chatId) + "&text=" + text;
  makeRequest(url);
}

void TelegramBot::getUpdates(String offset, int limit)  
{
    String url = "/bot" + botToken + "/getUpdates?offset=" + offset + "&limit=" + limit;
    String result = makeRequest(url);
    StaticJsonBuffer<500> jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(result); 

    if(!root.success())
    {
       Serial.println("parse failed");
       return;
    }
    JsonArray& list = root["result"];
    for (auto& request : list) 
    {
       int type = request["type"];
       int value = request["update_id"];
       Serial.println(value);
    }
} 

