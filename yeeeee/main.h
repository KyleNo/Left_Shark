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
#include "resources/tinyxml2.h"
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

void tileDraw(sf::RenderWindow& window, int numberofcharacterspossible, string mapChoice)
{
    int nice=0;
    //setup functions
    declareTiles();
    loading(window);
    abilityDeclare();
    //declare variables
    int selectedHero=-1;
    int tileBeingUsed;
    int viewCounterX = -64;
    int viewCounterY = -0;
    int framerateCounter = 0;

    bool mouseHovering=false;
    bool actionMenu = false;

    vector<sf::Vector2i> validtiles;
    vector<tile> stepOnMe;
    tile tiles[9];

    //set up the window
    window.setSize(sf::Vector2u(800,640));
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(800, 640));
    view1.setCenter(0,0);
    window.setView(view1);
    window.setFramerateLimit(60);
    tilemap testmap;
    testmap.mapSize = 400;


    tileBeingUsed=testmap.generateTileCollection(mapChoice);

    sf::Texture bckgrnd;
    if (!bckgrnd.loadFromFile("resources/images/blackbutt-10x10.png"))
    {
        //error...
    }

    //apply a font
    sf::Font arial;
    if(!arial.loadFromFile("resources/Fonts/arial.ttf"))
    {
        //error...
    }

    //declare new buttons
    button moveHero;
    button actHero;
    button cancelHero;
    moveHero.declareButton(sf::Vector2i(70,25), "Move", arial);
    actHero.declareButton(sf::Vector2i(70,25), "Action", arial);
    cancelHero.declareButton(sf::Vector2i(70,25), "Cancel", arial);

    button wepAtk;
    button jobAtk;
    button cancelAtk;
    wepAtk.declareButton(sf::Vector2i(70,25), "Attack", arial);
    jobAtk.declareButton(sf::Vector2i(70,25), "Job Ability", arial);
    cancelAtk.declareButton(sf::Vector2i(70,25), "Cancel", arial);

    //designate characters
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
    bool attackMenu = false;
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
        //screen movement
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
        {
            sf::Vector2i playerPosition;
            if (event.mouseButton.button == sf::Mouse::Left)
            {
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

        }
        //Mouse tile stuff
        hero user;
        testmap.drawTilemap(tileBeingUsed, window);
        if(actionMenu)
        {

            user = heroes[selectedHero];
            hero target = heroes[user.heroId+1];
            View windowView = window.getView();
            Vector2i screenPosition = window.mapCoordsToPixel(windowView.getCenter());

            //Move buttons to encompass character
            moveHero.setPosition(((user.Position.x)*32) + 50, user.Position.y*32);
            actHero.setPosition(((user.Position.x)*32) - 125, user.Position.y*32);
            cancelHero.setPosition(((user.Position.x)*32) - 35 , user.Position.y*32 - 35);

            if ((event.mouseButton.button == Mouse::Left)||mousePressed)
            {
                    if(moveHero.hovercheck(tiles[8].position*32)==true)
                    {
                        validtiles=heroes[selectedHero].rangecheck(testmap.passableTile, window);
                        stepOnMe.resize(validtiles.size());
                        int counter=validtiles.size();
                        cout << counter << endl;
                        mousePressed=true;
                        actionMenu=false;
                    }
                    else if(actHero.hovercheck(tiles[8].position*32)==true && !user.action)
                    {
                        attackMenu = true;
                        actionMenu = false;
                    }
                    else if(cancelHero.hovercheck(tiles[8].position*32)==true)
                    {
                        actionMenu=false;
                    }
                }
            }
            else
            {
                mousePressed = false;

                tiles[8].drawToGrid(tiles[8].position.x, tiles[8].position.y,window.getView(), window);
            }
            wepAtk.setPosition(((user.Position.x)*32) + 50, user.Position.y*32);
            jobAtk.setPosition(((user.Position.x)*32) - 125, user.Position.y*32);
            cancelAtk.setPosition(((user.Position.x)*32) - 35 , user.Position.y*32 - 35);
        if(attackMenu);
        {
            View windowView = window.getView();
            Vector2i screenPosition = window.mapCoordsToPixel(windowView.getCenter());
            //Move buttons to encompass character


            if ((event.mouseButton.button == Mouse::Left)||mousePressed)
            {
                    if(wepAtk.hovercheck(tiles[8].position*32)==true && !user.action)
                    {
                        ability testAbility;
                        testAbility.isAttack = true;
                        testAbility.isBuff = false;
                        testAbility.isHeal = false;
                        testAbility.abilityPotency = 5;
                        testAbility.range = 1000;
                        testAbility.abilityModifier = 1;
                        //target.team = 1;
                        user.team = 0;
                        //target = user.useAbility(testAbility, target);
                        //heroes[selectedHero+1] = target;
                        heroes[selectedHero] = user;
                       // cout << target.currentHealth << endl;
                    }
                    if(jobAtk.hovercheck(tiles[8].position*32) == true && !user.action){
                                                ability testAbility;
                        testAbility.isAttack = true;
                        testAbility.isBuff = false;
                        testAbility.isHeal = false;
                        testAbility.abilityPotency = 5;
                        testAbility.range = 1000;
                        testAbility.abilityModifier = 1;
                        //target.team = 1;
                        user.team = 0;
                        //target = user.useAbility(testAbility, target);
                        //heroes[selectedHero+1] = target;
                        heroes[selectedHero] = user;
                       // cout << target.currentHealth << endl;
                    }
            }
        }
        for (int i=0;i<stepOnMe.size();i++)
        {
            stepOnMe[i]=tiles[6];
            stepOnMe[i].tileSprite.setPosition(validtiles[i].x*32,validtiles[i].y*32);
        }
        if (selectedHero>=0)
        {
            if (!actionMenu and !heroes[selectedHero].moved)
            {
                for (int i=0;i<stepOnMe.size();i++)
                {
                    window.draw(stepOnMe[i].tileSprite);
                }
                if (event.mouseButton.button == Mouse::Right)
                {
                    for (int i=0;i<validtiles.size();i++)
                    {
                        if (tiles[8].tileSprite.getPosition().x==stepOnMe[i].tileSprite.getPosition().x and tiles[8].tileSprite.getPosition().y==stepOnMe[i].tileSprite.getPosition().y)
                        {
                            heroes[selectedHero].placehero(window,heroes[selectedHero].sprite.getPosition().x,heroes[selectedHero].sprite.getPosition().y, false, stepOnMe[i].tileSprite.getPosition());
                        }
                    }
                }
            }
        }

        for (int i=0;i<testmap.numberOfCharactersPossible;i++)
        {
            window.draw(heroes[i].sprite);
            tiles[8].drawToGrid(tiles[8].position.x, tiles[8].position.y,window.getView(), window);
        }
        if(actionMenu)
        {
            validtiles.clear();
            if(selectedHero >=0 and !heroes[selectedHero].action){
                actHero.drawButton(window);
            }
            if (selectedHero>=0 and !heroes[selectedHero].moved)
            {
                moveHero.drawButton(window);
            }
            cancelHero.drawButton(window);
        }
        if(attackMenu){
            wepAtk.drawButton(window);
            jobAtk.drawButton(window);
            cancelAtk.drawButton(window);
        }
<<<<<<< HEAD
        if (stepOnMe.size()!=0)
        {
            for (int i=0;i<stepOnMe.size();i++)
            {
                window.draw(stepOnMe[i].tileSprite);
                cout << "LIFE IS GOOM\n";
            }
        }
=======
        cout << attackMenu << actionMenu << endl;
>>>>>>> origin/WiP
        window.display();
        window.clear();
        }
    }







#endif // MAIN_H_INCLUDED
