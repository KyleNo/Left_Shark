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
    void declareButton(sf::Vector2i buSize, string Name, sf::Font& arial);
    void setPosition(int x, int y);
    void moveButton(int x, int y);
    void drawButton(sf::RenderWindow& window);
    bool hovercheck(sf::Vector2i mousePos, bool mouseclicked);
    bool hover= false;

    void test();



};


void button::declareButton(sf::Vector2i buSize, string Name, sf::Font& arial)
{
    buttonSize=buSize;
    name=Name;

    text.setFont(arial);
    text.setString(Name);
    text.setCharacterSize(16);
    text.setColor(sf::Color::White);
    text.setStyle(sf::Text::Style::Bold);
    blackButt.setSize(sf::Vector2f(buttonSize.x, buttonSize.y));
    blackButt.setFillColor(sf::Color(0,0,0));
}


void button::setPosition(int x, int y)
{
    position=sf::Vector2i(x,y);
    blackButt.setPosition(x,y); //moves button sprite to set position
    text.setPosition(x+10,y+10); //offsets text
    text.setPosition(x+5,y+5); //offsets text
}

void button::moveButton(int x, int y)
{
    setPosition(position.x + x, position.y + y);
}
bool button::hovercheck(sf::Vector2i mousePos, bool mouseclicked)
{
    if (!mouseclicked)
    {
        if(mousePos.x >= position.x  and mousePos.x <=position.x + buttonSize.x  and mousePos.y >= position.y  and mousePos.y <= position.y + buttonSize.y)
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
    return false;
}

void button::drawButton(sf::RenderWindow& window)
{
    window.draw(blackButt);
    window.draw(text);
}









#endif // BUTTON_H_INCLUDED
