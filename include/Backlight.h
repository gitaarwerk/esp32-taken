#include <Arduino.h>
#include <SPI.h>

#ifndef BACKLIGHT_H
#define BACKLIGHT_H

class Backlight
{
private:
    int pin;
    bool state;
    int brightness; // 0 to 255
    int dutyCycle;

public:
    Backlight(int pin, bool state, int brightness);

    void init();

    void on();

    void off();

    void toggle();

    void setBrightness(int brightness = 10);

    void decreaseBrightness(int stepSize);

    void increaseBrightness(int stepSize);

    bool getStatus();

    int getBrightness();

    void emit();
}
#endif
;