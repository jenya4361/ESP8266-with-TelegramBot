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
    , botToken( "611112968:AAFmVifZwM9vI-ws_tabN91X0HcdbuMMGCc" )
  {}
  
  void init();

  String makeRequest(String url);
  void sendMessage(char* text, unsigned int chatId);
  void getUpdates(String offset, int limit);
  void checkCommands(String message);
  
  const WiFiClientSecure& getClient() const { return m_client; };

  private:
  char* host;
  char* fingerprint;
  String botToken;
  
  WiFiClientSecure m_client;
};

