#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "windows.h"
#include "tile.h"
#include <string.h>
#include <iostream>
#include <math.h>
#include "resources/TMXParser.h"
#include "herofunctions.h"
#include "menuDeclare.h"
#include "tilemap.h"
#include "button.h"
#include "abilities.h"
#include <SFML/Audio.hpp>


using namespace std;

class structure{
public:
    bool passable;
    short healingPerTurn;
    short speedBonus;
    short rangeBonus;

};



void declareTiles()
{
    int tilex=0,tiley=0;
    for (int i=0;i<9;i++)
    {
        tiles[i].tileID=i+1;
        tiles[i].tileTexture.loadFromFile("tilesets/tileset.png");
        tiles[i].tileSprite.setTexture(tiles[i].tileTexture);
        tiles[i].tileSprite.setTextureRect(sf::IntRect(tilex,tiley,32,32));
        if (tiles[i].tileID==3)
        {
            tiles[i].passable=false;
        }
        else
        {
            tiles[i].passable=true;
        }
        tilex+=32;
        if (tilex==96)
        {
            tilex=0;
            tiley+=32;
        }
    }
}



void selectTile(sf::Vector2i screenPos, sf::RenderWindow& window){
    tiles[8].drawToGrid(screenPos.x/32 + .5, screenPos.y/32 + .5,window.getView(), window);
}


void loading(sf::RenderWindow& window)
{
    sf::Texture loadingScreen;
    sf::Sprite loadingSprite;
    loadingScreen.loadFromFile("resources/images/Loading.png");
    loadingSprite.setTexture(loadingScreen);
    window.clear();
    window.draw(loadingSprite);
    window.display();
}
    //buttonTemplate heroMove;
    //buttonTemplate heroAction;
    //buttonTemplate menuCancel;
    bool actionMenu = false;

void tileDraw(sf::RenderWindow& window, int numberofcharacterspossible)
{
//    sf::Music music;
//    if (!music.openFromFile("mynameisnathaniel.ogg"))
//    {
        //reerer
//    }
    vector<tile> validtiles;
    tile tiles[9];
    bool mouseHovering=false;
    int selectedHero;
    window.setSize(sf::Vector2u(800,640));
    loading(window);
    int tileBeingUsed;
    sf::Font font;
    font.loadFromFile("neoteric.ttf");
    sf::Text screenText;
    screenText.setString("null");
    screenText.setFont(font);
    screenText.setCharacterSize(12);
    screenText.setColor(sf::Color::Red);
    declareTiles();
    abilityDeclare();
    int viewCounterX = -64;
    int viewCounterY = -0;
    int framerateCounter = 0;
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(800, 640));
    view1.setCenter(0,0);
    window.setView(view1);
    window.setFramerateLimit(60);
    tilemap testmap;
    testmap.mapSize = 400;
<<<<<<< HEAD
    tileBeingUsed=testmap.generateTileCollection("tilemaps/coolmap.tmx");

    //apply a font
=======
    tileBeingUsed=testmap.generateTileCollection();
    sf::Texture bckgrnd;
    if (!bckgrnd.loadFromFile("resources/images/blackbutt-10x10.png"))
    {
        //error...
    }
    sf::Font arial;
>>>>>>> parent of 1ab1039... <3
    if(!arial.loadFromFile("resources/Fonts/arial.ttf"))
    {
        //error...
    }
    sf::Text testt;
    testt.setCharacterSize(16);
    testt.setString("Hello");
    testt.setColor(sf::Color::White);
    testt.setFont(arial);
    testt.setPosition(400,400);
    //declare new buttons

    button moveHero;
    button actHero;
    button cancelHero;



    moveHero.declareButton(sf::Vector2i(70,25), "Move", arial);
    actHero.declareButton(sf::Vector2i(70,25), "Attack", arial);
    cancelHero.declareButton(sf::Vector2i(70,25), "Cancel", arial);

    //this is where we designate the heroes.
    hero heroes[testmap.numberOfCharactersPossible];
    for (int i=0;i<testmap.numberOfCharactersPossible;i++)
    {
        heroes[i].assignhero();
        heroes[i].currentHealth = 50;
        heroes[i].heroId = i;
    }
    bool buttonPressed = false;
    bool checkingValidity = false;
    bool mousePressed = false;
    sf::Vector2i mousePos;
    view1.move(400,320); //sets view to top left corner
    for (int i=0;i<testmap.numberOfCharactersPossible;i++)
    {
        heroes[i].placehero(window, testmap.characterPositionsX[i]*32,testmap.characterPositionsY[i]*32, true, sf::Vector2f(0,0));
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
        {//tile validity

            screenText.setString("Tile Validity Shown");
            checkingValidity = true;
        }
        else
        {
            checkingValidity = false;
        }
        //screen movement
        screenText.setString("View movement enabled, use the arrow keys");
        if(sf::Mouse::getPosition(window).x > 672 and view1.getCenter().x < testmap.width*32-400)
        {//right
            framerateCounter++;
            if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 5))
            {
                view1.move(32,0);
                viewCounterX+=32;
                window.setView(view1);
            }
        }
        if(sf::Mouse::getPosition(window).x < 128 and view1.getCenter().x>400 )
        {//left
            framerateCounter++;
            if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 5))
            {
                view1.move(-32,0);
                viewCounterX-=32;
                window.setView(view1);
            }
        }
        if(sf::Mouse::getPosition(window).y < 128 and view1.getCenter().y > 320)
        {//up
            framerateCounter++;
            if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 5))
            {
                view1.move(0,-32);
                viewCounterY-=32;
                window.setView(view1);
            }
        }
        if(sf::Mouse::getPosition(window).y > 472 and view1.getCenter().y < testmap.height*32-320)
        {//down
            framerateCounter++;
            if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 5))
            {
                view1.move(0,32);
                viewCounterY+=32;
                window.setView(view1);
            }
        }
        if((sf::Mouse::getPosition(window).y > 472 and view1.getCenter().y < testmap.height*32-320) or (sf::Mouse::getPosition(window).y < 128 and view1.getCenter().y > 320) or (sf::Mouse::getPosition(window).x < 128 and view1.getCenter().x>400 ) or (sf::Mouse::getPosition(window).x > 672 and view1.getCenter().x < testmap.width*32-400))
        {
            buttonPressed = true;
        }
        else
        {
            buttonPressed = false;
        }
        sf::Vector2i screenPos;
        mousePos = sf::Mouse::getPosition(window);
        screenPos.x = window.mapPixelToCoords(mousePos).x;
        screenPos.y = window.mapPixelToCoords(mousePos).y;
        tiles[8].position.x = screenPos.x/32+.5;
        tiles[8].position.y = screenPos.y/32+.5;
        int mousePositionx=(mousePos.x/32)*32, mousePositiony=(mousePos.y/32)*32;
        if (((event.type == sf::Event::MouseButtonPressed) || mousePressed) and actionMenu == false)
        {mousePressed = true;
            sf::Vector2i playerPosition;
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                screenText.setString("Mouse pressed");
                mousePressed = true;
                for (int i=0;i<testmap.numberOfCharactersPossible;i++)
                {
                    if (tiles[8].tileSprite.getPosition().x==(heroes[i].sprite.getPosition().x/32)*32 && tiles[8].tileSprite.getPosition().y==(heroes[i].sprite.getPosition().y/32)*32)
                    {
                        selectedHero=i;
                        mouseHovering=true;
                        break;
                    }
                    else
                    {
                        mouseHovering=false;
                        selectedHero = -1;
                    }
                }
                if(selectedHero > -1)
                {
                    actionMenu = true;
                }
            }

        } else mousePressed = false;

    //Mouse tile stuff
        testmap.drawTilemap(tileBeingUsed, window);
        if(checkingValidity)
        {
            for(int aa = 0; aa < testmap.tileCollection.size(); aa++)
            {
                testmap.tileCollection[aa].isValidMovement(window);
            }
        }
        if(actionMenu)
        {
//            music.play();
            hero user;
            user = heroes[selectedHero];
            hero target = heroes[user.heroId+1];
            View windowView = window.getView();
            Vector2i screenPosition = window.mapCoordsToPixel(windowView.getCenter());
            //new buttons

            moveHero.setPosition(((user.Position.x)*32) + 50, user.Position.y*32);
            actHero.setPosition(((user.Position.x)*32) - 125, user.Position.y*32);
            cancelHero.setPosition(((user.Position.x)*32) - 35 , user.Position.y*32 - 35);

        //if (event.type == Event::MouseButtonPressed){
            //heroes[selectedHero].rangecheck(testmap.passableTile, window);
    if ((event.mouseButton.button == Mouse::Left)||mousePressed){mousePressed = true;
            if(!event.mouseButton.button&&mousePressed){
                if(moveHero.hovercheck(tiles[8].position*32)==true)
                {
                    for (int i=-5;i<=5;i++)
                    {
                        for (int j=-(5-abs(i));j<=5-abs(i);j++)
                        {
                            validtiles.push_back(heroes[selectedHero].rangecheck(testmap.passableTile, window,j,i));
                            int counter=validtiles.size();
                        }
                    }
                    actionMenu=false;
                }
                else if(actHero.hovercheck(tiles[8].position*32)==true)
                {//IM SETTING IT UP DONT WORRY
                    cout << user.heroId << endl;

                    ability testAbility;
                    testAbility.isAttack = true;
                    testAbility.isBuff = false;
                    testAbility.abilityPotency = 500;
                    testAbility.range = 1000;
                    testAbility.abilityModifier = 1;
                    target.team = 1;
                    user.team = 0;
                    user.useAbility(testAbility, target, user);
                    cout << target.heroId << endl;
                    cout << target.currentHealth << endl;
                }
                else if(cancelHero.hovercheck(tiles[8].position*32)==true)
                {
                    actionMenu=false;
                    }
                }
            }
            else mousePressed = false;
        }
        if (!actionMenu)
        {
            selectTile(screenPos, window);
        }
        screenText.setOrigin(-viewCounterX + 310, -viewCounterY + 310);
        tiles[8].drawToGrid(tiles[8].position.x, tiles[8].position.y,window.getView(), window);
        window.draw(screenText);
        if (!actionMenu)
        {
            //cout << 5 << endl;
            for (int i=0;i<validtiles.size();i++)
            {
                window.draw(validtiles[i].tileSprite);
            }
            //cout << 6 << endl;
            if (event.mouseButton.button == Mouse::Right and actionMenu== false)
            {
                for (int i=0;i<validtiles.size();i++)
                {
                    if (tiles[8].tileSprite.getPosition().x==validtiles[i].tileSprite.getPosition().x and tiles[8].tileSprite.getPosition().y==validtiles[i].tileSprite.getPosition().y)
                    {

                        heroes[selectedHero].placehero(window,heroes[selectedHero].sprite.getPosition().x,heroes[selectedHero].sprite.getPosition().y, false, validtiles[i].tileSprite.getPosition());
                    }
                }
            }
        }
        for (int i=0;i<testmap.numberOfCharactersPossible;i++)
        {
            window.draw(heroes[i].sprite);
        }
        if(actionMenu)
        {
            validtiles.clear();

            actHero.drawButton(window);
            moveHero.drawButton(window);
            cancelHero.drawButton(window);
        }
        window.display();
        window.clear();
    }
}








#endif // MAIN_H_INCLUDED
