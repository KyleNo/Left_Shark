#include "main.h"
#include "menuDeclare.h"
#include "resources/TMXParser.h"
#include "resources/tinyxml2.h"
int main(){
    sf::RenderWindow window(sf::VideoMode(800,600), "Cool");
    window.setFramerateLimit(60);
    startMenu(window);

    return 0;
}
