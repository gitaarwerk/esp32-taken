#include <Button.h>
#include <string>

Button::Button(byte pin, String buttonName)
{
    Serial.begin(115200);
    this->pin = pin;
    this->state = LOW;
    this->buttonName = buttonName;
    init();
}

void Button::init()
{
    pinMode(this->pin, INPUT_PULLUP);
}

bool Button::isPressed()
{
    bool reading = digitalRead(this->pin);

    if (reading != this->state)
    {
        delay(20);                        // Debounce delay. Can be adjusted based on your specific button.
        reading = digitalRead(this->pin); // Read again after delay

        this->state = reading;

        // If the button state is HIGH and enough time has passed since the last button press
        if (this->state == HIGH && (millis() - this->lastPressedTime) > 100)
        {
            this->lastPressedTime = millis();
            return true;
        }
    }

    return false;
}

bool Button::isLatching()
{
    bool reading = digitalRead(this->pin);

    if (reading != this->state)
    {
        delay(20); // Debounce delay
        reading = digitalRead(this->pin);

        if (reading != this->state)
        {
            this->state = reading;

            // If the button state is HIGH (button is pressed)
            if (this->state == HIGH)
            {
                // Toggle the latched state and return true
                this->latchedState = !this->latchedState;
                return true;
            }
        }
    }

    return false;
}

bool Button::isRepeating(int repeatDelay)
{
    bool reading = digitalRead(this->pin);
    delay(20); // Debounce delay

    if (reading == HIGH && (this->lastPressedTime + repeatDelay < millis()))
    {
        this->lastPressedTime = millis();
        return true;
    }

    return false;
}

;