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
  Serial.print("connecting to ");
  Serial.println(host);
  if (!m_client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return "";
  }
  
  Serial.print("requesting URL: ");
  Serial.println(url);

  m_client.println("GET /" + url + "Connection: close");
  /*m_client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");
*/
  Serial.println("request sent");
  /*while (m_client.connected()) {
    String line = m_client.readStringUntil('+');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }*/
  String line = m_client.readStringUntil('+');
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
    
    char* newResult = new char[result.length()];
    int i = 0;
    int j = 0;
    while(result[i] != '\0')
    {
      char character = result[i];
      i++;
      if( character == '\n' )
      {
        Serial.println("n");
        continue;
      }
      if( character == '\r' )
      {
        Serial.println("r");
        continue;
      }
      newResult[j] = character;
      j++;
    }

    Serial.println(newResult);
    
    DynamicJsonBuffer jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(newResult); 

    if(!root.success())
    {
       Serial.println("parse failed");
       return;
    }
    JsonArray& list = root["result"];
    
    for (auto& request : list) 
    {
       int type = request["type"];
       JsonObject& value = request["message"];
       const char* text = value["text"];
       Serial.println(text);
       checkCommands(String(text));
    }
} 

void TelegramBot::checkCommands(String message)
{
  if( message == "temp" )
  {
    Serial.println("YESS!");
    sendMessage("No temperature sensor found", 316978348);
  }
}

