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
    //void moveButton(int x, int y);
};


void declareButton(sf::Vector2i buSize, string Name)
{

}


void button::setPosition(int x, int y)
{
    //button.position=sf::Vector2i(x,y);
}


#endif // BUTTON_H_INCLUDED
