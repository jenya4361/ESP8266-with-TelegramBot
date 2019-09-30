#include <WiFiClientSecure.h>
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate

class TelegramBot
{
  private:
    static TelegramBot* m_instance;

    TelegramBot()
      : m_host( "api.telegram.org" )
      , m_fingerprint( "37:21:36:77:50:57:F3:C9:28:D0:F7:FA:4C:05:35:7F:60:C1:20:44" )
    {}

    String makeRequest(String url);

  public:

    inline static TelegramBot* Instance() { return m_instance; }

    void init( const char* botToken, unsigned int recipients[] );
    void sendMessage(const char* text);
    const WiFiClientSecure& getClient() const { return m_client; };

  private:
    unsigned int* m_recipients;
    int m_recipientsSize;
    char* m_host;
    char* m_fingerprint;
    String m_botToken;

    WiFiClientSecure m_client;
};
