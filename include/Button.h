#include <Arduino.h>
#include <AppConfig.h>
#include <string>

class Button
{
private:
    byte pin;
    String buttonName;
    byte state;
    byte latchedState;
    unsigned long lastPressedTime = 0; // the last time the output pin was toggled

public:
    Button(byte pin, String buttonName);

    void init();

    bool isPressed();

    bool isLatching();

    bool isRepeating(int repeatDelay = 100);
};