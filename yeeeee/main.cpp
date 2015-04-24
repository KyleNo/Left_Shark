#include "main.h"
#include "menuDeclare.h"
#include "resources/TMXParser.h"
sf::RenderWindow window(sf::VideoMode(800,600), "Cool");
int main(){
    window.setFramerateLimit(60);
    startMenu(window);

    return 0;
}
