#include <Arduino.h>
#include <ArduinoJson.h>
#include <AppState.h>
#include <AppConfig.h>
#include <Config.h>
#include <Backlight.h>
#include <Button.h>
#include "SDCard.h"
#include <CaptivePortal.h>
#include <string>

#define BACKLIGHT_PIN 4      // The Backlight pin ESP32 IO04
#define BUTTON_PIN_LEFT 38   // The ESP32 IO38
#define BUTTON_PIN_MIDDLE 37 // The ESP32 IO38
#define BUTTON_PIN_RIGHT 39  // The ESP32 IO39

Config configuration;
AppConfig appConfig;
AppState appState;
CaptivePortal captivePortal;
Backlight backlight(BACKLIGHT_PIN, true, 40);
Button leftButton(BUTTON_PIN_LEFT, "left");
Button middleButton(BUTTON_PIN_MIDDLE, "middle");
Button rightButton(BUTTON_PIN_RIGHT, "right");

void setup()
{
  Serial.begin(115200);

  JsonDocument document = configuration.load("{\"SSID\":\"A_New_world\", \"portalId\":\"RandomPortal\", \"autoLocaleOfBrowser\": true,\"defaultLocale\":\"nl_NL\",\"screensaver\":false}");
  appConfig.setValue("hostname", document["hostname"]);
  appConfig.setValue("SSID", document["SSID"]);
  captivePortal.setSSID(appConfig.SSID);
  Serial.println(appConfig.hostname.c_str());

  init();
}

void init()
{
  appState.menuActive = "home";
  const bool hasStarted = captivePortal.start();

  if (hasStarted)
  {
    appState.menuActive = "portal";
    appState.portalStarted = true;
  }
}

String randomStringFromArray(String array[], int arrayLength)
{
  int randomIndex = random(arrayLength);
  return array[randomIndex];
}

void loop()
{
  if (appState.menuActive == "portal")
  {
    if (leftButton.isPressed())
    {
      Serial.println("Going to home menu");

      appState.menuActive = "home";
    }

    if (middleButton.isPressed())
    {
      if (appState.portalStarted)
      {
        Serial.println("Stopping captive portal");

        captivePortal.stop();
        appState.portalStarted = false;
      }
      else
      {
        Serial.println("Starting captive portal");

        captivePortal.start();
        appState.portalStarted = true;
      }
    }

    if (rightButton.isPressed())
    {
      Serial.println("Changing SSID");
      String strings[] = {
          "GoGoGadgetInternet",
          "TellMyWiFiLoveHer",
          "Pretty Fly For a Wi-fi",
          "Routers of Rohan",
          "Winter WonderLAN",
          "The LAN Before Time",
          "LAN of Milk and Honey",
          "Silence of the LANs",
          "The Promised LAN",
          "The LAN Down Under",
          "Area 51 Test Site",
          "Drive-By Wi-Fi",
          "Wu Tang LAN",
          "Darude LANstorm",
          "Yell ____ for Password",
          "The Password is 1234",
          "The Password is Password"};

      int arrayLength = sizeof(strings) / sizeof(strings[0]);
      String randomString = randomStringFromArray(strings, arrayLength);
      Serial.println(randomString);
      captivePortal.setSSID(randomString, true);
    }
  }

  if (appState.menuActive == "brightness")
  {
    if (leftButton.isPressed())
    {
      Serial.println("Going to home menu");

      appState.menuActive = "home";
    }

    if (middleButton.isPressed())
    {
      backlight.decreaseBrightness(5);
    }

    if (rightButton.isPressed())
    {
      backlight.increaseBrightness(5);
    }
  }

  if (appState.menuActive == "display")
  {
    if (leftButton.isPressed())
    {
      Serial.println("Going to home menu");

      appState.menuActive = "home";
    }

    if (middleButton.isPressed())
    {
      backlight.off();
    }

    if (rightButton.isPressed())
    {
      backlight.on();
    }
  }

  if (appState.menuActive == "home")
  {
    if (leftButton.isPressed())
    {
      appState.menuActive = "portal";
    }

    if (middleButton.isPressed())
    {
      appState.menuActive = "display";
    }

    if (rightButton.isPressed())
    {
      appState.menuActive = "brightness";
    }
  }

  captivePortal.listenAndHandleRequests();

  delay(5);
}