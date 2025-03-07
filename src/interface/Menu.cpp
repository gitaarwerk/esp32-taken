#include <interface/Menu.h>
#include <string>

const char *menuItems[] = {"Item 1", "Item 2", "Item 3", "Item 4"};
int selectedItem = 0; // The currently selected menu item

Menu::Menu()
{
}

void Menu::drawMenu()
{
    drawItems();
    drawButtonBar();
}

void Menu::drawItems()
{
}

void Menu::drawButtonBar()
{
}