#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
class buttonTemplate
{
public:
    Texture buttonLoadingTexture;
    Vector2i coordinates;
    Sprite button;
    void setButton(int x, int y);
    Vector2i buttonSelection(Vector2i coordinates, Vector2i position);
    double buttonscale(double addon);
    bool hover=false;
    double addon=1;
};

void buttonTemplate::setButton(int x, int y)
{
    if (!buttonLoadingTexture.loadFromFile("button420.png"))
    {

    }
    button.setTexture(buttonLoadingTexture);
    coordinates.x=x;
    coordinates.y=y;
}

Vector2i buttonTemplate::buttonSelection(Vector2i coordinates, Vector2i position)
{
    if (position.x >coordinates.x and position.x < coordinates.x+200 and position.y > coordinates.y and position.y<coordinates.y+100)
    {
        if (coordinates.x<250)
        {
            coordinates.x++;
        }
        hover=true;
    }
    else
    {
        if (coordinates.x>200)
        {
            coordinates.x--;
        }
        hover=false;
    }
    return coordinates;
}

double buttonTemplate::buttonscale(double addon)
{
    if(addon>1)
    {
        addon=addon-.002;
    }
    return addon;
}

int main()
{
    Vector2i position;
    RenderWindow window(sf::VideoMode(800, 600), "SFML Saves!");
    Texture menuLoadingTexture;
    buttonTemplate Button1;
    buttonTemplate Button2;
    Button1.setButton(200,300);
    Button2.setButton(200,410);

    if (!menuLoadingTexture.loadFromFile("menushark2.png"))
    {

    }


    Sprite menu;

    menu.setTexture(menuLoadingTexture);

    while (window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left and (Button1.hover==true or Button2.hover==true))
                {
                    if(Button1.hover==true)
                    {
                        //cout << "Button 1 pressed.\n";

                        Button1.addon=1.2;
                    }
                    else
                    {
                        //cout << "Button 2 pressed.\n";
                        Button2.addon=1.2;
                    }
                }
            }
        }

        position=Mouse::getPosition(window);
        window.clear();
        Button1.coordinates=Button1.buttonSelection(Button1.coordinates, position);
        Button1.button.setPosition(Button1.coordinates.x,Button1.coordinates.y);
        Button2.coordinates=Button2.buttonSelection(Button2.coordinates, position);
        Button2.button.setPosition(Button2.coordinates.x,Button2.coordinates.y);
        Button1.button.setScale(Button1.addon,Button1.addon);
        Button2.button.setScale(Button2.addon,Button2.addon);
        Button1.addon=Button1.buttonscale(Button1.addon);
        Button2.addon=Button2.buttonscale(Button2.addon);

        window.draw(menu);
        window.draw(Button1.button);
        window.draw(Button2.button);
        window.display();
    }
}