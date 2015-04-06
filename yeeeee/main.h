#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <SFML/Graphics.hpp>
using namespace std;
#include <vector>
#include "windows.h"
#include "tile.h"
#include "string.h"
#include <iostream>
#include <math.h>
#include "resources/TMXParser.h"
#include "herofunctions.h"



class tilemap
{
    public:
        vector<int> passableTileX, passableTileY;
        vector<int> characterPositionsX, characterPositionsY;
        int height,width;
        int numberOfCharactersPossible;
        vector<tile>tileCollection;
        int mapSize;
        void drawTilemap(int tileBeingUsed, sf::RenderWindow& window);
        int generateTileCollection();
};

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

//drawToGrid() is used in drawTileMap()
int tilemap::generateTileCollection(){ //finds tile collection using tmx
    int goodtiles=0,badtiles=0;
    sf::Vector2i gridcounter;
    tmxparser::TmxMap yee; //declares tmx map
    tmxparser::TmxReturn error; //error test
    error = tmxparser::parseFromFile("tilemaps/coolmap.tmx", &yee, "tilesets/"); //parses file
    int mapSize = yee.height*yee.width; //finds map size
    int tilemapGrid[mapSize]; //array for tile map numeric values
    numberOfCharactersPossible=0;
    if (!error) //negative error test
    {
        height=yee.height; //sets map height
        width=yee.width; //sets map width
        for (int i =0;i<mapSize;i++)
        {

            tilemapGrid[i]=yee.layerCollection[0].tiles[i].gid;
            if (tilemapGrid[i]==2)
            {
                tilemap::passableTileX.push_back(1);
                tilemap::passableTileY.push_back(1);
            }
            else
            {
                tilemap::passableTileX.push_back(0);
                tilemap::passableTileY.push_back(0);
            }
            if (passableTileX[i]==1 and passableTileY[i]==1)
            {
                badtiles++;
            }
            else
            {
                goodtiles++;
            }
            if (yee.layerCollection[1].tiles[i].gid == 6)
            {
                numberOfCharactersPossible++;
                characterPositionsX.push_back(gridcounter.x);
                characterPositionsY.push_back(gridcounter.y);
            }
            if (gridcounter.x==width)
            {
                gridcounter.x=0;
                gridcounter.y++;
            }
            else
            {
                gridcounter.x++;
            }
            if (gridcounter.x==width)
            {
                gridcounter.x=0;
                gridcounter.y++;
            }
        }
        vector<int> sortingvector;
        for (int i=0;i<passableTileX.size();i++)
        {
            sortingvector.push_back(passableTileX[i]);
        }
        passableTileX=sortingvector;
        for (int i=0;i<passableTileY.size();i++)
        {
            sortingvector.push_back(passableTileY[i]);
        }
        passableTileY=sortingvector;
    }
    tilemap::tileCollection.resize(mapSize);
    int counter = 0;
    for (int bb=0;bb<6;bb++)
    {
        for (int bc=0;bc<mapSize;bc++)
        {
            if (tilemapGrid[bc]==bb)
            {
                tilemap::tileCollection[bc]=tiles[bb-1];
            }
        }
    }

    cout << "Good tiles:" << goodtiles;
    cout << endl << "Bad tiles:" << badtiles << endl;
    return tilemapGrid[counter];
}
void tilemap::drawTilemap(int tileBeingUsed, sf::RenderWindow& window){
    int counter = 0;
    for(int aa = 0; aa < height; aa++){
        for(int ab = 0; ab < width; ab++){
            tilemap::tileCollection[counter].drawToGrid(ab,aa,window.getView(), window);
            counter++;
        }
    }
}

void selectTile(sf::Vector2i screenPos, sf::RenderWindow& window){
    tiles[7].drawToGrid(screenPos.x/32 + .5, screenPos.y/32 + .5,window.getView(), window);
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

void tileDraw(sf::RenderWindow& window, int numberofcharacterspossible)
{
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
    int viewCounterX = -64;
    int viewCounterY = -0;
    int framerateCounter = 0;
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(800, 640));
    view1.setCenter(0,0);
    window.setView(view1);
    window.setFramerateLimit(60);
    tilemap testmap;
    testmap.mapSize = 400;
    tileBeingUsed=testmap.generateTileCollection();
    //this is where we designate the heroes.
    //we should split this into a different header file.
    hero heroes[testmap.numberOfCharactersPossible];
    for (int i=0;i<testmap.numberOfCharactersPossible;i++)
    {
        heroes[i].assignhero();
    }

    bool buttonPressed = false;
    bool checkingValidity = false;
    bool mousePressed = false;
    sf::Vector2i mousePos;
    view1.move(400,320); //sets view to top left corner
    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
                    {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)){//tile validity
            screenText.setString("Tile Validity Shown");
            checkingValidity = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)or true){//screen movement
            screenText.setString("View movement enabled, use the arrow keys");
            cout << sf::Mouse::getPosition(window).x << "\t" << sf::Mouse::getPosition(window).y << endl;
            if(sf::Mouse::getPosition(window).x > 768 and view1.getCenter().x < testmap.width*32-400){//right
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 30)){
                    view1.move(32,0);
                    viewCounterX+=32;
                    window.setView(view1);
                }}
            else if(sf::Mouse::getPosition(window).x < 32 and view1.getCenter().x>400 ){//left
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 30)){
                    view1.move(-32,0);
                    viewCounterX-=32;
                    window.setView(view1);

                }}
            else if(sf::Mouse::getPosition(window).y < 32 and view1.getCenter().y > 320){//up
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 30)){
                        view1.move(0,-32);
                        viewCounterY-=32;
                        window.setView(view1);
                }}
            else if(sf::Mouse::getPosition(window).y > 608 and view1.getCenter().y < testmap.height*32-320){//down
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 30)){
                    view1.move(0,32);
                    viewCounterY+=32;
                    window.setView(view1);
                }}
            else {
                buttonPressed = false;
                framerateCounter = 0;
            }}
        else {
                screenText.setString("null");
                buttonPressed = false;
                checkingValidity = false;
            }
        //Mouse tile stuff
        sf::Vector2i screenPos;
        mousePos = sf::Mouse::getPosition(window);
        screenPos.x = window.mapPixelToCoords(mousePos).x;
        screenPos.y = window.mapPixelToCoords(mousePos).y;
        tiles[8].position.x = screenPos.x/32+.5;
        tiles[8].position.y = screenPos.y/32+.5;
        if (event.type == sf::Event::MouseButtonPressed){
                sf::Vector2i playerPosition;
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    screenText.setString("Mouse pressed");
                    mousePressed = true;
                    for (int i=0;i<testmap.numberOfCharactersPossible;i++)
                    {
                        int mousePositionx=(mousePos.x/32)*32, mousePositiony=(mousePos.y/32)*32;
                        if (mousePositionx==(heroes[i].sprite.getPosition().x/32)*32 && mousePositiony==(heroes[i].sprite.getPosition().y/32)*32)
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
                    heroes[selectedHero].rangecheck(testmap.passableTileX,testmap.passableTileY,window);
                }
            }
        else mousePressed = false;

        //Mouse tile stuff
        testmap.drawTilemap(tileBeingUsed, window);
        if(checkingValidity){
            for(int aa = 0; aa < testmap.tileCollection.size(); aa++){
                testmap.tileCollection[aa].isValidMovement(window);
            }}
        if(mousePressed) selectTile(screenPos, window);

        for (int i=0;i<testmap.numberOfCharactersPossible;i++)
        {
            heroes[i].placehero(window, testmap.characterPositionsX[i]*32,testmap.characterPositionsY[i]*32);
        }
        screenText.setOrigin(-viewCounterX + 310, -viewCounterY + 310);
        tiles[8].drawToGrid(tiles[8].position.x, tiles[8].position.y,window.getView(), window);
        window.draw(screenText);
        window.display();
        window.clear();
    }

}










#endif // MAIN_H_INCLUDED
