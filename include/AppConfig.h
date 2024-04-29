#include <string>

#ifndef APPCONFIG_H
#define APPCONFIG_H

struct AppConfig
{
    // locales
    bool autoLocaleOfBrowser;
    String defaultLocale;

    // Screen
    bool screensaver;
    int screensaverTimeoutInSeconds;

    // Wifi / network
    bool randomizeMacAddress;
    String SSID;
    String hostname;

    // Portal
    bool autoStartPortal;
    String autoStartPortalWith;

    AppConfig() : autoLocaleOfBrowser(true),
                  defaultLocale("en_US"),
                  screensaver(true),
                  screensaverTimeoutInSeconds(30),
                  randomizeMacAddress(true),
                  autoStartPortal(false),
                  SSID("ESP32-CaptivePortal"),
                  hostname("ESPTaken")
    {
    }
    void setValue(String key, String value)
    {
        if (key == "autoLocaleOfBrowser")
        {
            autoLocaleOfBrowser = value == "true";
        }
        else if (key == "defaultLocale")
        {
            defaultLocale = value;
        }
        else if (key == "screensaver")
        {
            screensaver = value == "true";
        }
        else if (key == "screensaverTimeoutInSeconds")
        {
            screensaverTimeoutInSeconds = value.toInt();
        }
        else if (key == "randomizeMacAddress")
        {
            randomizeMacAddress = value == "true";
        }
        else if (key == "hostname")
        {
            hostname = value;
        }
        else if (key == "autoStartPortal")
        {
            autoStartPortal = value == "true";
        }
        else if (key == "SSID")
        {
            SSID = value.c_str();
        }
        else if (key == "autoStartPortalWith")
        {
            autoStartPortalWith = value;
        }
    }
};

extern AppConfig appConfig;

#endif
;