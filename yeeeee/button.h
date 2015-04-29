#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>



class button{
public:
    sf::Vector2i position;
    sf::Vector2i buttonSize;
    sf::Sprite buttonBackg;
    sf::RectangleShape blackButt;
    sf::Text text;
    string name;
    void declareButton(sf::Vector2i buSize, string Name);
    void setPosition(int x, int y);
    void moveButton(int x, int y);
    bool hovercheck(sf::Vector2i mousePos);
    bool hover= false;
};


void button::declareButton(sf::Vector2i buSize, string Name)
{
    buttonSize=buSize;
    sf::Font arial;
    if(!arial.loadFromFile("resources/Fonts/arial.ttf"))
    {
        //error...
    }


    text.setFont(arial);
    text.setString(Name);
    text.setScale(1,1);
    blackButt.setSize(sf::Vector2f(buttonSize.x, buttonSize.y));
    blackButt.setFillColor(sf::Color(0,0,0));
}


void button::setPosition(int x, int y)
{
    button::position=sf::Vector2i(x,y);
    button::blackButt.setPosition(x,y); //moves button sprite to set position
    button::text.setPosition(x+10,y+10); //offsets text
}

void button::moveButton(int x, int y)
{
    button::setPosition(button::position.x + x, button::position.y + y);
}
bool button::hovercheck(sf::Vector2i mousePos)
{
//    cout << "______________________________________________________________\n";
    //cout << mousePos.x << "," << mousePos.y << endl;
//    cout << coordinates.x << "\t" << coordinates.y << endl;
//    cout << "______________________________________________________________\n";
    if((mousePos.x >= position.x  and mousePos.x <=position.x + buttonSize.x  and mousePos.y >= position.y  and mousePos.y <= position.y + buttonSize.y ) /*and sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)*/)

    {
        hover=true;
        return true;
    }
    else
    {
        hover=false;
        return false;
    }
}
#endif // BUTTON_H_INCLUDED
