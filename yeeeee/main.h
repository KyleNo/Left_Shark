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

    tile tiles[9];
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
    bool startPress =false;
    //setup functions
    declareTiles();
    loading(window);
    abilityDeclare();
    //declare variables
    int selectedHero=-1;
    int tileBeingUsed;
    int viewCounterX = 0;
    int viewCounterY = 0;
    int framerateCounter = 0;
    int nice=0;
    int mouseCounter = 0;
    bool leftPressed=false;
    bool mouseHovering=false;
    bool actionMenu = false;
    bool drawingTiles=false;

    sf::Vector2i startLocation;

    vector<sf::Vector2i> validtiles, attackrange;
    vector<tile> stepOnMe, attackMe;

    //set up the window
    window.setSize(sf::Vector2u(800,640));
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(800, 640));
    view1.setCenter(0,0);
    window.setView(view1);
    window.setFramerateLimit(60);
    tilemap testmap;
    testmap.mapSize = 400;
    vector<bool> heroesReady;
    int teamActive = -1;

    tileBeingUsed=testmap.generateTileCollection(mapChoice,tiles);



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
    jobAtk.declareButton(sf::Vector2i(100,25), "Job Ability", arial);
    cancelAtk.declareButton(sf::Vector2i(70,25), "Cancel", arial);

    //designate characters
    hero heroes[testmap.numberOfCharactersPossible];
    const char* heroNames[4]={"David","Kyle","Doesntdoshit","Nathaniel"};
    for (int i=0;i<testmap.numberOfCharactersPossible;i++)
    {
        heroes[i].assignhero(heroNames[i]);
        heroes[i].heroId = i;
    }
    bool teamFinished = false;
    bool buttonPressed = false;
    bool checkingValidity = false;
    bool mousePressed = false;
    bool attackMenu = false;
    //here we go again figuring out this tinyxml bs

    bool releasedMouse=false;
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
            if (event.type == sf::Event::EventType::MouseButtonReleased)
            {
                releasedMouse=true;
            }
            else
            {
                releasedMouse=false;
            }
        }
        //screen movement
        /*
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
        */

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) and view1.getCenter().x < testmap.width*32-400)
        {//right
            framerateCounter++;
            if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 5))
            {
                view1.move(32,0);
                viewCounterX+=32;
                window.setView(view1);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) and view1.getCenter().x>400 )
        {//left
            framerateCounter++;
            if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 5))
            {
                view1.move(-32,0);
                viewCounterX-=32;
                window.setView(view1);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) and view1.getCenter().y > 320)
        {//up
            framerateCounter++;
            if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 5))
            {
                view1.move(0,-32);
                viewCounterY-=32;
                window.setView(view1);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) and view1.getCenter().y < testmap.height*32-320)
        {//down
            framerateCounter++;
            if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 5))
            {
                view1.move(0,32);
                viewCounterY+=32;
                window.setView(view1);
            }
        }
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) and view1.getCenter().x < testmap.width*32-400) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) and view1.getCenter().x>400 ) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) and view1.getCenter().y > 320) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) and view1.getCenter().y < testmap.height*32-320))
        {
            buttonPressed = true;
        }
        else
        {
            buttonPressed = false;
        }
        //alternative movement system                                                       you have to check whether every single button is being hovered over... idk what else to do; I put these in parenthesis
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) and !mouseHovering and ((!moveHero.hover and !actHero.hover and !cancelHero.hover and !wepAtk.hover and !jobAtk.hover and !cancelAtk.hover) or !actionMenu) and !startPress)
        {
            startPress=true;
            startLocation=sf::Mouse::getPosition();
        }
        if (startPress==true)
        {

            sf::Vector2f difference=sf::Vector2f(0,0);
            int temp;
            difference.x=sf::Mouse::getPosition().x - startLocation.x;
            difference.y=sf::Mouse::getPosition().y - startLocation.y;
            startLocation=sf::Mouse::getPosition();
            //cout << difference.x << "," << difference.y << endl;

            //view1.move(-difference.x,0);

            //cout << viewCounterX<<", "<< viewCounterY<<endl;

            if((difference.x<0 and viewCounterX<testmap.width*32-800) or (difference.x>0 and viewCounterX>0))
            {
                if(viewCounterX-difference.x<0)
                {
                    difference.x=viewCounterX;
                }
                else if(viewCounterX-difference.x>testmap.width*32-800)
                {
                    difference.x=-((testmap.width*32-800)-viewCounterX);
                }
                view1.move(-difference.x,0);
                viewCounterX-=difference.x;
            }
            if((difference.y<0 and viewCounterY<testmap.height*32-640) or (difference.y>0 and viewCounterY>0))
            {
                if(viewCounterY-difference.y<0)
                {
                    difference.y=viewCounterY;
                }
                else if(viewCounterY-difference.y>testmap.height*32-640)
                {
                    difference.y=-((testmap.height*32-640)-viewCounterY);
                }

                view1.move(0,-difference.y);
                viewCounterY-=difference.y;
            }
            window.setView(view1);
        }
        if(releasedMouse)
        {
            startPress=false;
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
            if (event.mouseButton.button == sf::Mouse::Left && !drawingTiles)
            {
                for (int i=0;i<testmap.numberOfCharactersPossible;i++)
                {
                    if (tiles[8].tileSprite.getPosition().x==(heroes[i].sprite.getPosition().x/32)*32 && tiles[8].tileSprite.getPosition().y==(heroes[i].sprite.getPosition().y/32)*32 and !actionMenu and !drawingTiles and heroes[i].team == teamActive)
                    {
                        selectedHero=i;
                        mouseHovering=true;
                        break;
                    }
                    else
                    {
                        mouseHovering=false;
                    }
                }
                if(selectedHero > -1 and !drawingTiles)
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
            View windowView = window.getView();
            Vector2i screenPosition = window.mapCoordsToPixel(windowView.getCenter());

            //Move buttons to encompass character
            moveHero.setPosition(((user.Position.x)*32) + 50, user.Position.y*32);
            actHero.setPosition(((user.Position.x)*32) - 125, user.Position.y*32);
            cancelHero.setPosition(((user.Position.x)*32) - 35 , user.Position.y*32 - 35);

            if ((event.mouseButton.button == Mouse::Left))
            {
                if(moveHero.hovercheck(tiles[8].position*32, mousePressed)==true and !attackMenu)
                {
                    validtiles=heroes[selectedHero].rangecheck(testmap.passableTile, window, false);
                    stepOnMe.resize(validtiles.size());
                    mousePressed=true;
                    actionMenu=false;
                }
                else if(actHero.hovercheck(tiles[8].position*32, mousePressed)==true && !user.action and !attackMenu)
                {
                    attackMenu = true;
                    actionMenu = false;
                    mousePressed=true;
                }
                else if(cancelHero.hovercheck(tiles[8].position*32, mousePressed)==true)
                {
                    mousePressed=true;
                    actionMenu=false;
                    attackMenu=false;
                    heroes[selectedHero].moved = true;
                    heroes[selectedHero].action = true;
                    selectedHero=-1;
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
        if(attackMenu==true)
        {
            hero target;
            target = heroes[selectedHero+1];

            View windowView = window.getView();
            Vector2i screenPosition = window.mapCoordsToPixel(windowView.getCenter());


            if ((event.type == sf::Event::MouseButtonPressed) and !mousePressed)
            {
                if(wepAtk.hovercheck(tiles[8].position*32, mousePressed) && !user.action)
                {
                    ability testAbility;
                    testAbility.isAttack = true;
                    testAbility.isBuff = false;
                    testAbility.isHeal = false;
                    testAbility.abilityPotency = 5;
                    testAbility.range = 1000;
                    testAbility.abilityModifier = 1;
                    target = user.useAbility(testAbility, target);
                    heroes[selectedHero] = target;
                    heroes[selectedHero] = user;
                    attackrange=heroes[selectedHero].rangecheck(testmap.passableTile, window, true);
                }
                if(jobAtk.hovercheck(tiles[8].position*32, mousePressed) && !user.action)
                {
                    ability testAbility;
                    testAbility.isAttack = true;
                    testAbility.isBuff = false;
                    testAbility.isHeal = false;
                    testAbility.abilityPotency = 5;
                    testAbility.range = 1000;
                    testAbility.abilityModifier = 1;
                    target = user.useAbility(testAbility, target);
                    heroes[selectedHero+1] = target;
                    heroes[selectedHero] = user;
                    attackrange=heroes[selectedHero].rangecheck(testmap.passableTile, window, true);
                }
                attackMe.resize(attackrange.size());
                attackMenu=false;
                actionMenu=false;
                }
        }
        if (!drawingTiles)
        {
            for (int i=0;i<validtiles.size();i++)
            {
                stepOnMe[i]=tiles[7];
                stepOnMe[i].tileSprite.setPosition(validtiles[i].x*32,validtiles[i].y*32);
            }
            for (int i=0;i<attackrange.size();i++)
            {
                attackMe[i]=tiles[6];
                attackMe[i].tileSprite.setPosition(attackrange[i].x*32,attackrange[i].y*32);
            }
        }
        if (selectedHero>=0)
        {
            if (!actionMenu and !heroes[selectedHero].moved or !actionMenu and !heroes[selectedHero].action)
            {
                for (int i=0;i<stepOnMe.size();i++)
                {
                    window.draw(stepOnMe[i].tileSprite);
                    drawingTiles=true;
                }
                for(int i=0;i<attackMe.size();i++)
                {
                    window.draw(attackMe[i].tileSprite);
                    drawingTiles=true;
                }
                if (!mousePressed and Mouse::isButtonPressed(Mouse::Left))
                {
                    for (int i=0;i<validtiles.size();i++)
                    {
                        if (tiles[8].tileSprite.getPosition().x==heroes[selectedHero].sprite.getPosition().x and tiles[8].tileSprite.getPosition().y==heroes[selectedHero].sprite.getPosition().y)
                        {
                            stepOnMe.clear();
                            drawingTiles=false;
                            mousePressed=true;
                            actionMenu=true;
                        }
                        else if (tiles[8].tileSprite.getPosition().x==stepOnMe[i].tileSprite.getPosition().x and tiles[8].tileSprite.getPosition().y==stepOnMe[i].tileSprite.getPosition().y)
                        {
                            heroes[selectedHero].placehero(window,heroes[selectedHero].sprite.getPosition().x,heroes[selectedHero].sprite.getPosition().y, false, stepOnMe[i].tileSprite.getPosition());
                            drawingTiles=false;
                            mousePressed=true;
                            actionMenu=true;
                            stepOnMe.clear();
                        }
                    }
                    for (int i=0;i<attackrange.size();i++)
                    {
                        if (tiles[8].tileSprite.getPosition().x==attackMe[i].tileSprite.getPosition().x and tiles[8].tileSprite.getPosition().y==attackMe[i].tileSprite.getPosition().y)
                        {
                            drawingTiles=false;
                            mousePressed=true;
                        }
                    }
                }
            }
        }
        if (drawingTiles==false and actionMenu==false and attackMenu==false)
        {
            selectedHero=-1;
            attackMe.clear();
        }
        if (!Mouse::isButtonPressed(sf::Mouse::Left) && mousePressed)
        {
            mouseCounter++;
            if(mouseCounter>=20){
                mousePressed=false;
                mouseCounter = 0;
            }
        }
        heroesReady.resize(testmap.numberOfCharactersPossible);
        vector<int>teamRecorder;
        int teamCounter = 0;

        for(int q = 0; q < testmap.numberOfCharactersPossible; q++){
            if(heroes[q].action && heroes[q].moved && teamActive == heroes[q].team){//checks all heroes on active team
                heroesReady[q] = true;
            }
        }
        for(int w = 0; w < testmap.numberOfCharactersPossible; w++){
            if(heroes[w].team = teamActive){
                teamCounter++;
            }
        }
        for(int x = 0; x < testmap.numberOfCharactersPossible; x++){
            if(heroesReady[x]&&teamActive == heroes[x].team){//holds all exerted heroes position in heroes
                teamRecorder.push_back(x);
            }
        }
        cout << teamActive << endl;
        for(int z = 0; z < teamRecorder.size(); z++){
            if(teamRecorder.size() == teamCounter){//resets
                heroes[teamRecorder[z]].moved = false;
                heroes[teamRecorder[z]].action = false;
                teamFinished = true;
            }
        }
        if(teamFinished){
            if(teamActive == 1 || teamActive == 2){
                    teamActive++;
                    teamFinished = false;
                }else if(teamActive == 3){
                    teamActive = 1;
                    teamFinished = false;
        }
        }
        if(teamActive == -1){
            cout << "Init game" << endl;
            teamActive = 1;
            for(int zz = 0; zz > testmap.numberOfCharactersPossible; zz++){
                heroes[zz].moved = true;
                heroes[zz].action = true;
            }
        }
        for (int i=0;i<testmap.numberOfCharactersPossible;i++)
        {
            window.draw(heroes[i].sprite);
            tiles[8].drawToGrid(tiles[8].position.x, tiles[8].position.y,window.getView(), window);
        }
        if(actionMenu)
        {
            drawingTiles=false;
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
        if (stepOnMe.size()!=0)
        {
            for (int i=0;i<stepOnMe.size();i++)
            {
                window.draw(stepOnMe[i].tileSprite);
            }
        }
        window.display();
        window.clear();
        }
    }







#endif // MAIN_H_INCLUDED
