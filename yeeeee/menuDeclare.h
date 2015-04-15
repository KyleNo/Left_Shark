#ifndef MENUDECLARE_H_INCLUDED
#define MENUDECLARE_H_INCLUDED
#include "menu.h"
#include "main.h"
void tileDraw(sf::RenderWindow& window, int numberofcharectorspossible);
void startMenu(RenderWindow& window)
{
    Vector2i position;
    Texture menuLoadingTexture;
    buttonTemplate Button1;
    buttonTemplate Button2;
    Button1.setButton(200,300,"resources/images/startbutton.png");
    Button2.setButton(200,410,"resources/images/button420.png");
    if (!menuLoadingTexture.loadFromFile("resources/images/menushark2.png"))
    {

    }


    Sprite menu;

    menu.setTexture(menuLoadingTexture);
    window.setFramerateLimit(300);
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
                        window.setFramerateLimit(60);
                        tileDraw(window,NULL);
                        //cout << "Button 1 pressed.\n";
                        //Button1.addon=1.2;
                    }
                    else
                    {
                        //cout << "Button 2 pressed.\n";
                        //Button2.addon=1.2;
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

void actionMenu(hero user, RenderWindow& window){
    buttonTemplate heroMove;
    buttonTemplate heroAction;
    View windowView = window.getView();
    Vector2i screenPosition = window.mapCoordsToPixel(windowView.getCenter());
    heroMove.setButton(500, 1000, "resources/images/attackButton.png");
      Event event;
        while(window.pollEvent(event)){
            if (event.type == Event::Closed)window.close();
            if (event.type == Event::MouseButtonPressed){
                if (event.mouseButton.button == Mouse::Left and (heroMove.hover==true || heroAction.hover == true)){
                    if(heroMove.hover==true){
                        //attackMenu(user, window);
                    }
                    else if(heroAction.hover == true){
                        //null
                    }
                }
            }
        }

        window.draw(heroMove.button);
}


#endif // MENUDECLARE_H_INCLUDED
