#ifndef INTERFACE_H
#define INTERFACE_H

#include <Adafruit_ILI9341.h>

#define TFT_CLK 18
#define TFT_MISO 12
#define TFT_MOSI 23
#define TFT_CS 27
#define TFT_DC 32
#define TFT_RST 5

class Interface
{
public:
    static Interface &getInstance();
    void operator=(const Interface &) = delete;
    void draw();

private:
    Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
    Interface();
    Interface(const Interface &) = delete;
};

#endif // INTERFACE_H