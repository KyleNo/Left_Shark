#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class buttonTemplate
{
public:
    sf::Texture buttonLoadingTexture;
    sf::Vector2i coordinates;
    sf::Sprite button;
    void setButton();
    sf::Vector2i buttonSelection(sf::Vector2i coordinates, sf::Vector2i position);
};

void buttonTemplate::setButton()
{
    if (!buttonLoadingTexture.loadFromFile("button420.png"))
    {

    }
    button.setTexture(buttonLoadingTexture);
    coordinates.x=200;
    coordinates.y=300;
}

sf::Vector2i buttonTemplate::buttonSelection(sf::Vector2i coordinates, sf::Vector2i position)
{
    cout << coordinates.x << " " << coordinates.y << endl;
    if (position.x >coordinates.x and position.x < coordinates.x+200 and position.y > coordinates.y and position.y<coordinates.y+100)
        {
            if (coordinates.x<250)
            {
                coordinates.x++;
            }
        }
        else
        {
            if (coordinates.x>200)
            {
               coordinates.x--;
            }
        }
        return coordinates;
}

int main()
{
    sf::Vector2i position;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Saves!");
    sf::Texture menuLoadingTexture;
    buttonTemplate Button1;
    buttonTemplate Button2;
    Button1.setButton();
    Button2.setButton();

    if (!menuLoadingTexture.loadFromFile("menu420.png"))
    {

    }


    sf::Sprite menu;

    menu.setTexture(menuLoadingTexture);

    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        position=sf::Mouse::getPosition(window);
        window.clear();
        Button1.coordinates=Button1.buttonSelection(Button1.coordinates, position);
        Button1.button.setPosition(Button1.coordinates.x,Button1.coordinates.y);
        Button2.coordinates=Button2.buttonSelection(Button2.coordinates, position);
        Button2.button.setPosition(Button2.coordinates.x,Button2.coordinates.y+110);
        window.draw(menu);
        window.draw(Button1.button);
        window.draw(Button2.button);
        window.display();
    }
}
