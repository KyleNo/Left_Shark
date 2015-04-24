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
    bool hovercheck(sf::Vector2i mousePos, int viewCounterX, int viewCounterY);
    sf::Vector2i bSize;
};
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

bool buttonTemplate::hovercheck(sf::Vector2i mousePos, int viewCounterX, int viewCounterY)
{
<<<<<<< HEAD
    //cout << "______________________________________________________________\n";
    //cout << mousePos.x << "," << mousePos.y << endl;
    //cout << coordinates.x << "\t" << coordinates.y << endl;
    //cout << "______________________________________________________________\n";
    if((mousePos.x >= coordinates.x and mousePos.x <=coordinates.x + bSize.x and mousePos.y >= coordinates.y and mousePos.y <= coordinates.y + bSize.y) /*and sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)*/)
=======
//    cout << "______________________________________________________________\n";
    cout << mousePos.x << "," << mousePos.y << endl;
//    cout << coordinates.x << "\t" << coordinates.y << endl;
//    cout << "______________________________________________________________\n";
    if((mousePos.x >= coordinates.x  and mousePos.x <=coordinates.x + bSize.x  and mousePos.y >= coordinates.y  and mousePos.y <= coordinates.y + bSize.y ) /*and sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)*/)
>>>>>>> 9285f1ba5dbebba2482c502d0eeca84414e3ab73
    {
        hover=true;
        return true;
        cout << ":p";
    }
    else
    {
        hover=false;
        return false;
    }
}


