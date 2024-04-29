#include <DNSServer.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <string>

class CaptiveRequestHandler : public AsyncWebHandler
{
public:
    CaptiveRequestHandler() {}
    virtual ~CaptiveRequestHandler() {}

    bool canHandle(AsyncWebServerRequest *request);

    void handleRequest(AsyncWebServerRequest *request);
}

;

class CaptivePortal
{
private:
    bool active = false;
    String SSID;
    String portalId;
    IPAddress IP = IPAddress(192, 168, 1, 1);
    IPAddress gateway = IPAddress(192, 168, 1, 1);
    IPAddress subnet = IPAddress(255, 255, 255, 0);
    String password;
    bool requestPassword = false;
    String hostname;
    wifi_power_t power = WIFI_POWER_7dBm;
    uint8_t macAddress[6]; // Fix: Change the declaration to a fixed-size array with size 6.
    int channel = 1;
    bool hidden = false;
    int max_connection = 4;

public:
    enum class WIFI_POWER
    {
        STRENGTH_1 = WIFI_POWER_MINUS_1dBm,
        STRENGTH_2 = WIFI_POWER_2dBm,
        STRENGTH_3 = WIFI_POWER_5dBm,
        STRENGTH_4 = WIFI_POWER_7dBm,
        STRENGTH_5 = WIFI_POWER_11dBm,
        STRENGTH_6 = WIFI_POWER_13dBm,
        STRENGTH_7 = WIFI_POWER_15dBm,
        STRENGTH_8 = WIFI_POWER_19_5dBm,
        MINIMUM_STRENGTH = WIFI_POWER_MINUS_1dBm,
        MEDIUM_STRENGTH = WIFI_POWER_7dBm,
        MAXIMUM_STRENGTH = WIFI_POWER_19_5dBm
    };

    CaptivePortal();
    ~CaptivePortal();

    bool start();

    void stop();

    void setupServer();

    void restart(bool restart = true);

    void listenAndHandleRequests();

    void setSSID(String SSID, bool restart = false);

    void setPortalId(String portalId, bool restart = false);

    void setHostname(String hostname, bool restart = false);

    void setPower(String power, bool restart = false);

    void setMacAddress(uint8_t macAddress[6], bool restart = false);

    void setPassword(String password, bool restart = false);

    void setRequestPassword(bool requestPassword, bool restart = false);

    void setIP(IPAddress IP, bool restart = false);

    void setGateway(IPAddress IP, bool restart = false);

    void setSubnet(IPAddress subnet, bool restart = false);

    void setChannel(int channel, bool restart = false);

    void setHidden(bool hidden, bool restart = false);

    void setMaxConnection(int max_connection, bool restart = false);

    void setPower(WIFI_POWER power, bool restart = false);

    void randomizeMacAddress(bool restart = false);
}

;