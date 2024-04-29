# Project outline 
## Idea
To learn how to set-up an ESP32 to act like a captive portal, store login data, and copy/clone 

## Menu set-up
- Clone captive portal
  - Connect to a wifi portal
  - Clone page
  - Save to disk
- Captive portal
  - Load portal from UI
  - Set-up SSID
  - Randomize (seed)
    - Set to original
    - Randomize
    - Select #
    - Favourite
  - Favourite
  - Start/Stop
- Captives menu
  - Show capture
  - Delete
  - Navigate (up/down)
- Set-up
  - Screen auto-off
  - Language support select

## SD Card set-up
- gpio-settings.json
- settings.json
- locale
  - en.json
  - en_UK.json
- clones
  - [generated name]
- portals
  - name-of-portal
    - config.json
    - form.html
    - ackknowledgement.html
    - assets
- captives
  - all.csv 
  - [portal_name]
    - [emailaddress]_[orrurence#].txt
      - username, password, datetime(ISO), GPS location
   
## Project set-up
  - Menu with settings & actions
  - Clone & start portal
    - Select SSID, - Store SSID, - Open headless browser, download assets and store the portal, create SSID, start server, inject sniffer, save all to SD card
  - (start) portal
    - create certificate for company
    - Start webserver
    - set-up SSID
    - post call capture
    - save to SD card
