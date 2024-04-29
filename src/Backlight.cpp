#include <Backlight.h>
#include <Arduino.h>
#include <SPI.h>
#include <string>

#define PWM_CHANNEL 0
#define PWM_FREQUENCY 5000 // Change to your desired frequency
#define PWM_RESOLUTION 8
#define MIN_BRIGHTNESS 10

Backlight::Backlight(int pin, bool state, int brightness)
{
    this->pin = pin;
    this->state = state;
    this->brightness = brightness;

    ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(this->pin, PWM_CHANNEL);

    this->init();
}

void Backlight::init()
{
    if (this->state)
    {
        this->on();
    }
    else
    {
        this->off();
    }
}

void Backlight::on()
{
    if (!this->state && this->brightness < MIN_BRIGHTNESS)
    {
        this->setBrightness(MIN_BRIGHTNESS);
    }

    this->state = true;
    this->setBrightness(this->brightness);
    Serial.println("backlight on");
}

void Backlight::off()
{
    this->state = false;
    ledcWrite(PWM_CHANNEL, 0);

    Serial.println("backlight off");
}

void Backlight::toggle()
{
    Serial.println("backlight toggle");
    this->state ? this->off() : this->on();
}

void Backlight::setBrightness(int brightness)
{
    this->brightness = brightness;
    this->state = true;
    ledcWrite(PWM_CHANNEL, this->brightness);

    Serial.println("Setting brightness to " + String(this->brightness));
}

// 10 is lowest
void Backlight::decreaseBrightness(int stepSize)
{
    this->brightness -= stepSize;

    if (this->brightness < 10)
    {
        this->brightness = 10;
    }
    this->setBrightness(this->brightness);
}

void Backlight::increaseBrightness(int stepSize)
{
    this->brightness += stepSize;
    if (this->brightness > 255)
    {
        this->brightness = 255;
    }
    this->setBrightness(this->brightness);
}

bool Backlight::getStatus()
{
    return this->state;
}

int Backlight::getBrightness()
{
    return this->brightness;
}
