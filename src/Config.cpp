#include <Config.h>
#include <ArduinoJson.h>
#include <string>

JsonDocument Config::load(String contents)
{
    JsonDocument doc;

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, contents);

    // Test if parsing succeeds.
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
    }

    // Fetch values.
    //
    // Most of the time, you can rely on the implicit casts.
    // In other case, you can do doc["time"].as<long>();
    const char *sensor = doc["sensor"];
    long time = doc["time"];
    double latitude = doc["data"][0];
    double longitude = doc["data"][1];

    // Print values.
    // Serial.println(sensor);
    // Serial.println(time);
    // Serial.println(latitude, 6);
    // Serial.println(longitude, 6);

    // appConfig.time = time;

    // Serial.println(appConfig.time);

    return doc;
}
void Config::save()
{
    Serial.println("Saving config...");
}

; // don't forget the semicolon at the end of the class