#include "AppState.h"

bool AppState::getPortalStarted()
{
    return this->portalStarted;
}

void AppState::setPortalStarted(bool portalStarted)
{
    this->portalStarted = portalStarted;
}

int AppState::getHighlightedOption()
{
    return this->highlightedOption;
}

void AppState::setHighlightedOption(int highlightedOption)
{
    this->highlightedOption = highlightedOption;
}

std::string AppState::getActiveScreen()
{
    return this->activeScreen;
}

void AppState::setActiveScreen(std::string activeScreen)
{
    this->activeScreen = activeScreen;
}

std::string AppState::getActiveOption()
{
    return this->activeOption;
}

void AppState::setActiveOption(std::string activeOption)
{
    this->activeOption = activeOption;
}