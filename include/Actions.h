#include <AppState.h>
#include <map>
#include <vector>
#include <string>
#include <variant>

class Actions
{
private:
    std::map<std::string, std::map<std::string, std::variant<std::string, int, bool>>> getAction(std::string option);

public:
    Actions();
    void fireAction(std::string buttonPressed);
    std::map<std::string, std::variant<std::string, int, bool>> getButtonActions(std::string option); // change to array of options
};