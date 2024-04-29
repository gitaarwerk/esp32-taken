
# esp32-taken
Captive portal app for ESP32. (STILL IN DEVELOPMENT)

_**For education purposes only**_


## Project description?
ESP32-Taken is a captive portal that will capture the essential look and feel of a website, and turns it into a captive wifi portal. 

## Current state of the project
Currently, this app is still in development. Not all programming will run on the flash memory, so perhaps things need to change in the scope.

### Hardware used
LilyGo TTGO T4 v1.3, including SD card and a 2.2" TFT display using a ILI9341 driver.

### Working on / Issues
- SD card is currently not yet working. For some reason, the program will crash when using SD_MMC. SD using SPI is also not working
- Captured password stays blank
- PortalId stays blank
- Need to build a menu to change settings
- When SD card is working, I can start on saving/reading configuration and portals from/to SD cards
- Using bluetooth to tether with a phone, to allow to connect to urls and generate a portal based on those sites
- Create examples
- Create multiple set-ups for various ESP32s

### If storage is not enough
If the possibility that internal memory or bluetooth tethering is not working as I want it to, I most likely will create either an API or a front-end that can generate portals.

## More information
- [Project outline](./documentation/ProjectOutline.md)

- [Using an external antenna](./documentation/ExternalAntenna.md)