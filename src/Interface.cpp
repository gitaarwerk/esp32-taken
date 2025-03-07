#include <Interface.h>
#include <AppState.h>

Interface::Interface() // Private constructor
{
    tft.begin();
    tft.fillScreen(ILI9341_BLACK); // Clear the screen
}

Interface &Interface::getInstance()
{
    static Interface instance; // Guaranteed to be destroyed.
                               // Instantiated on first use.
    return instance;
}

void Interface::draw()
{
    bool portalStarted = appState.getPortalStarted();
    std::string activeScreen = appState.getActiveScreen();
    std::string activeOption = appState.getActiveOption();

    tft.fillScreen(ILI9341_BLACK); // Clear the screen
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(0, 0);
    tft.setTextSize(2);

    tft.println(activeOption.c_str());

    if (activeScreen == "home")
    {
        // Draw the bar
        int barHeight = 20; // Adjust as needed
        int barY = tft.height() - barHeight;
        tft.fillRect(0, barY, tft.width(), barHeight, ILI9341_WHITE);

        // Draw the labels for the buttons
        tft.setTextColor(ILI9341_BLACK);
        tft.setTextSize(2);
        int buttonWidth = tft.width() / 3;

        tft.setCursor(0, barY);

        bool isOn = portalStarted;
        tft.println(!isOn ? "On" : "Off");

        tft.setCursor(buttonWidth, barY);
        tft.println("Restart");

        tft.setCursor(2 * buttonWidth, barY);
        tft.println("Settings");
    }

    if (activeScreen == "portal")
    {
        // Draw the bar
        int barHeight = 20; // Adjust as needed
        int barY = tft.height() - barHeight;
        tft.fillRect(0, barY, tft.width(), barHeight, ILI9341_WHITE);

        // Draw the labels for the buttons
        tft.setTextColor(ILI9341_BLACK);
        tft.setTextSize(2);
        int buttonWidth = tft.width() / 3;

        tft.setCursor(0, barY);

        tft.println("home");

        tft.setCursor(buttonWidth, barY);
        tft.println("Stop");

        tft.setCursor(2 * buttonWidth, barY);
        tft.println("Start");
    }
}
// Usage: Interface& interface = Interface::getInstance();