#include <Arduino.h>
#include <CaptureCredentials.h>
#include <string>

CaptureCredentials::CaptureCredentials()
{
}

void CaptureCredentials::storeCaptive(String ssid, String portalId, String username, String password)
{
    Serial.println("Storing captive portal credentials");
    Serial.println("SSID: " + ssid);
    Serial.println("PortalID: " + portalId);
    Serial.println();
    Serial.println("username: " + username);
    Serial.println("password: " + password);
};
