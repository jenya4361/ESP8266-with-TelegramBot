#include <WiFiClientSecure.h>
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate

class TelegramBot
{
  public:

  TelegramBot()
    : host( "api.telegram.org" )
    , fingerprint( "37:21:36:77:50:57:F3:C9:28:D0:F7:FA:4C:05:35:7F:60:C1:20:44" )
  {}
  
  void init();

  void sendMessage(char* text, unsigned int chatId);
  
  const WiFiClientSecure& getClient() const { return m_client; };

  private:
  char* host;
  char* fingerprint;
  
  WiFiClientSecure m_client;
};

