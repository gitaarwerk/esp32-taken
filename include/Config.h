#include <ArduinoJson.h>
#include <string>

#ifndef CONFIG_H
#define CONFIG_H

class Config
{
public:
    JsonDocument load(String contents);

    void save();
}

#endif
;