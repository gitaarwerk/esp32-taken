#include <Actions.h>
#include <map>
#include <string>
#include <variant>
#include <vector>

Actions::Actions(){};

std::map<std::string, std::map<std::string, std::variant<std::string, int, bool>>> Actions::getAction(std::string option)
{
    std::map<std::string, std::map<std::string, std::variant<std::string, int, bool>>> actionList;

    if (option == "home")
    {
        bool portalStarted = appState.getPortalStarted();

        actionList["actions"]["L"] = std::variant<std::string, int, bool>(!portalStarted ? "true" : "false");
        actionList["actions"]["M"] = std::variant<std::string, int, bool>("stats");
        actionList["actions"]["R"] = std::variant<std::string, int, bool>("settings");

        actionList["menuBar"]["L"] = !portalStarted ? "on" : "off";
        actionList["menuBar"]["M"] = "stats";
        actionList["menuBar"]["R"] = "settings";
    }

    return actionList;
}

void Actions::fireAction(std::string buttonPressed)
{

    std::string activeOption = appState.getActiveOption();

    auto actionList = this->getAction(activeOption);
    auto &actions = actionList["actions"];

    // if (actions.count(buttonPressed) > 0)
    // {
    //     auto &action = actions[buttonPressed];
    //     if (std::holds_alternative<int>(action))
    //     {
    //         std::string value = std::get<int>(action);
    //         appState.setActiveOption(value.c_str());
    //     }
    // }
}

std::map<std::string, std::variant<std::string, int, bool>> Actions::getButtonActions(std::string option)
{
    std::string activeOption = appState.getActiveOption();

    auto actionList = this->getAction(activeOption);
    auto &menubar = actionList["menuBar"];

    return menubar;
}