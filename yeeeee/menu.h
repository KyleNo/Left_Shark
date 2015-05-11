#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "main.h"


#endif // MENU_H_INCLUDED
using namespace std;
using namespace sf;
class buttonTemplate{
public:
    Texture buttonLoadingTexture;
    Texture startButtonTexture;
    Vector2i coordinates;
    Sprite button;
    void setButton(int x, int y, string filename);
    Vector2i buttonSelection(Vector2i coordinates, Vector2i position);
    double buttonscale(double addon);
    bool hover=false;
    double addon=1;
    bool hovercheck(sf::Vector2i mousePos);
    sf::Vector2i bSize;
};

class mapThumbnail{
public:
    Texture texture;
    Sprite sprite;
    Vector2i coordinates;
    string fileLocation;
    void setThumbnail(sf::Vector2i location, string filename, string imagename);

};




string chewsMap(sf::Sprite& menuBack, sf::RenderWindow& window);

void buttonTemplate::setButton(int x, int y, string filename)
{
    if (!buttonLoadingTexture.loadFromFile(filename))
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
            coordinates.x+=1;
        }
        hover=true;
    }
    else
    {
        if (coordinates.x>200)
        {
            coordinates.x-=1;
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

bool buttonTemplate::hovercheck(sf::Vector2i mousePos)
{
//    cout << "______________________________________________________________\n";
    //cout << mousePos.x << "," << mousePos.y << endl;
//    cout << coordinates.x << "\t" << coordinates.y << endl;
//    cout << "______________________________________________________________\n";
    if((mousePos.x >= coordinates.x  and mousePos.x <=coordinates.x + bSize.x  and mousePos.y >= coordinates.y  and mousePos.y <= coordinates.y + bSize.y ) /*and sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)*/)

    {
        //hover=true;
        return true;
    }
    else
    {
        //hover=false;
        return false;
    }
}
void mapThumbnail::setThumbnail(sf::Vector2i location, string filename, string imagename)
{
    coordinates = location;
    fileLocation = filename;
    sprite.setPosition(sf::Vector2f(location.x, location.y));
    texture.loadFromFile(imagename);
    sprite.setTexture(texture);
}

string chewsMap(sf::Sprite& menuBack, sf::RenderWindow& window)
{
    sf::RectangleShape faded;
    faded.setFillColor(sf::Color(0,0,0,180));
    faded.setSize(sf::Vector2f(800,600));
    faded.setPosition(0,0);
    sf::Text title;
    title.setString("Choose map");
    mapThumbnail coolMapPic;
    mapThumbnail islandPic;
    coolMapPic.setThumbnail(sf::Vector2i(120,150),"tilemaps/coolmap.tmx", "resources/images/coolmapthumbnail.png");
    islandPic.setThumbnail(sf::Vector2i(480,150),"tilemaps/island.tmx", "resources/images/islandthumbnail.png");
    while (window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && sf::Mouse::getPosition(window).x > coolMapPic.coordinates.x && sf::Mouse::getPosition(window).x < coolMapPic.coordinates.x+200 && sf::Mouse::getPosition(window).y >coolMapPic.coordinates.y && sf::Mouse::getPosition(window).y < coolMapPic.coordinates.y + 200)
        {
            return coolMapPic.fileLocation;
        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && sf::Mouse::getPosition(window).x > islandPic.coordinates.x && sf::Mouse::getPosition(window).x < islandPic.coordinates.x+200 && sf::Mouse::getPosition(window).y >islandPic.coordinates.y && sf::Mouse::getPosition(window).y < islandPic.coordinates.y + 200)
        {
            return islandPic.fileLocation;
        }

        window.clear();
        window.draw(menuBack);
        window.draw(faded);
        window.draw(coolMapPic.sprite);
        window.draw(islandPic.sprite);

        window.display();
    }
}
