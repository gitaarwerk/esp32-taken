#include <string>

#ifndef APPSTATE_H
#define APPSTATE_H

struct AppState
{
    // locales
    bool isSleeping;
    bool portalStarted = false;
    std::string menuActive = "home";

    AppState() : isSleeping(false)
    {
    }
};

extern AppState appState;

#endif
;