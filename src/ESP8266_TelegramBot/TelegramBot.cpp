#include "TelegramBot.h"

void TelegramBot::init( const char* botToken, unsigned int recipients[] )
{
  m_botToken = botToken;
  m_recipients = recipients;
  m_recipientsSize = sizeof(recipients)/sizeof(*recipients);
  
  Serial.print("connecting to ");
  Serial.println(m_host);
  if( !m_client.connect(m_host, httpsPort) )
  {
    Serial.println("connection failed");
    return;
  }

  if( m_client.verify(m_fingerprint, m_host) ) 
  {
    Serial.println("certificate matches");
  } 
  else 
  {
    Serial.println("certificate doesn't match");
  }
}

String TelegramBot::makeRequest(String url)
{
  Serial.print("connecting to ");
  Serial.println(m_host);
  if( !m_client.connect(m_host, httpsPort) )
  {
    Serial.println("connection failed");
    return "";
  }
  
  Serial.print("requesting URL: ");
  Serial.println(url);

  m_client.println("GET /" + url + "Connection: close");
  
  Serial.println("request sent");
  String line = m_client.readStringUntil('+');
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");

  return line;
}
  
void TelegramBot::sendMessage(const char* text)
{
  for( int i = 0; i < m_recipientsSize; i++ )
  {
    unsigned int chatId = m_recipients[i];
    
    String url = "/bot" + m_botToken + "/sendMessage?chat_id=" + static_cast<String>(chatId) + "&text=" + text;
    makeRequest(url);
  }
}

TelegramBot* TelegramBot::m_instance = new TelegramBot();
