#ifndef APPSTATE_H
#define APPSTATE_H

#include <string>
#include <variant>

class AppState
{
private:
    std::string activeOption;
    std::string activeScreen;
    int highlightedOption;

    // Portal
    bool portalStarted;

public:
    AppState() : activeScreen("home"),
                 activeOption(""),
                 highlightedOption(-1),
                 portalStarted(false)
    {
    }

    void setPortalStarted(bool portalStarted);

    bool getPortalStarted();

    void setHighlightedOption(int highlightedOption);

    int getHighlightedOption();

    void setActiveScreen(std::string activeScreen);

    std::string getActiveScreen();

    void setActiveOption(std::string activeOption);

    std::string getActiveOption();
};

extern AppState appState;

#endif
