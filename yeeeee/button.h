#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>



class button{
public:
    sf::Vector2i position;
    sf::Vector2i buttonSize;
    sf::Sprite buttonBackg;
    sf::Text text;
    string name;
    void declareButton(sf::Vector2i buSize, string Name);
    void setPosition(int x, int y);
    void moveButton(int x, int y);
};


void button::declareButton(sf::Vector2i buSize, string Name)
{
    button.buttonSize=buSize;
    sf::Font arial;
    if(!arial.loadFromFile(resources/Fonts/arial.ttf))
    {
        //error...
    }
    button.text.setFont(arial);
    button.text.setString(Name);
}


void button::setPosition(int x, int y)
{
    button.position=sf::Vector2i(x,y);
    button.buttonBackg.setPosition(x,y);
    button.text.setPosition(x+10,y+10);
}

void button::moveButton(int x, int y)
{
    button.setPosition(button.position.x + x, button.position.y + y);
}

#endif // BUTTON_H_INCLUDED
