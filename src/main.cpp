#include <Arduino.h>
#include <ArduinoJson.h>
#include <Actions.h>
#include <AppState.h>
#include <AppConfig.h>
#include <Config.h>
#include <Backlight.h>
#include <Button.h>
#include <SDCard.h>
#include <CaptivePortal.h>
#include <Interface.h>
#include <string>

#define BACKLIGHT_PIN 4      // The Backlight pin ESP32 IO04
#define BUTTON_PIN_LEFT 38   // The ESP32 IO38
#define BUTTON_PIN_MIDDLE 37 // The ESP32 IO38
#define BUTTON_PIN_RIGHT 39  // The ESP32 IO39

Config configuration;
AppConfig appConfig;
AppState appState;
CaptivePortal captivePortal;
Actions actions;
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

  Serial.println(appConfig.hostname.c_str());
  Serial.println(appConfig.SSID.c_str());

  delay(100);
  captivePortal.setSSID(appConfig.SSID);
  Serial.println(appConfig.hostname.c_str());

  init();
}

void init()
{
  const bool hasStarted = captivePortal.start();

  if (hasStarted)
  {
    appState.setPortalStarted(true);
  }
}

String randomStringFromArray(String array[], int arrayLength)
{
  int randomIndex = random(arrayLength);
  return array[randomIndex];
}

void loop()
{
  if (leftButton.isPressed())
  {
    std::string activeScreen = appState.getActiveScreen();

    Serial.println("left is pressed");
    Serial.println("state:");
    Serial.println(activeScreen.c_str());
    actions.fireAction("L");
  }

  if (leftButton.isLatching())
  {
    Serial.println("left is pressed long");
    actions.fireAction("LL");
  }

  if (middleButton.isPressed())
  {
    Serial.println("middle button pressed");
    actions.fireAction("M");
  }

  if (middleButton.isLatching())
  {
    Serial.println("middle button pressed long");
    actions.fireAction("ML");
  }

  if (rightButton.isPressed())
  {
    Serial.println("right is pressed");
    actions.fireAction("R");
  }

  if (rightButton.isLatching())
  {
    Serial.println("right is pressed long");
    actions.fireAction("RL");
  }

  // if (state.activeScreen == "portal")
  // {
  //   if (leftButton.isPressed())
  //   {
  //     Serial.println("Going to home menu");
  //     state.activeScreen = "home";
  //     AppState::getInstance().setState(state);
  //   }

  //   if (middleButton.isPressed())
  //   {
  //     if (state.portalStarted)
  //     {
  //       Serial.println("Stopping captive portal");

  //       captivePortal.stop();
  //       state.portalStarted = false;
  //       AppState::getInstance().setState(state);
  //     }
  //   }

  //   if (rightButton.isPressed())
  //   {
  //     Serial.println("Changing SSID");
  //     String strings[] = {
  //         "GoGoGadgetInternet",
  //         "TellMyWiFiLoveHer",
  //         "Pretty Fly For a Wi-fi",
  //         "Routers of Rohan",
  //         "Winter WonderLAN",
  //         "The LAN Before Time",
  //         "LAN of Milk and Honey",
  //         "Silence of the LANs",
  //         "The Promised LAN",
  //         "The LAN Down Under",
  //         "Area 51 Test Site",
  //         "Drive-By Wi-Fi",
  //         "Wu Tang LAN",
  //         "Darude LANstorm",
  //         "Yell 'VELMA!!!' for Password",
  //         "The Password is 1234",
  //         "The Password is Password"};

  //     int arrayLength = sizeof(strings) / sizeof(strings[0]);
  //     String randomString = randomStringFromArray(strings, arrayLength);
  //     Serial.println(randomString);
  //     captivePortal.setSSID(randomString, true);
  //   }
  // }

  // if (state.activeScreen.c_str() == "brightness")
  // {
  //   Serial.println("brightness menu");

  //   if (leftButton.isPressed())
  //   {
  //     Serial.println("Going to home menu");

  //     state.activeScreen = "home";
  //     AppState::getInstance().setState(state);
  //   }

  //   if (middleButton.isPressed())
  //   {
  //     backlight.decreaseBrightness(5);
  //   }

  //   if (rightButton.isPressed())
  //   {
  //     backlight.increaseBrightness(5);
  //   }
  // }

  // if (state.activeScreen.c_str() == "display")
  // {
  //   Serial.println("display menu");

  //   if (leftButton.isPressed())
  //   {
  //     Serial.println("Going to home menu");

  //     state.activeScreen = "home";
  //     AppState::getInstance().setState(state);
  //   }

  //   if (middleButton.isPressed())
  //   {
  //     backlight.off();
  //   }

  //   if (rightButton.isPressed())
  //   {
  //     backlight.on();
  //   }
  // }

  // if (state.activeScreen.c_str() == "home")
  // {
  //   Serial.println("Home menu");
  //   if (leftButton.isPressed())
  //   {
  //     state.activeScreen = "portal";
  //     AppState::getInstance().setState(state);
  //   }

  //   if (middleButton.isPressed())
  //   {
  //     state.activeScreen = "display";
  //     AppState::getInstance().setState(state);
  //   }

  //   if (rightButton.isPressed())
  //   {
  //     state.activeScreen = "brightness";
  //     AppState::getInstance().setState(state);
  //   }
  // }

  captivePortal.listenAndHandleRequests();

  delay(10);
}