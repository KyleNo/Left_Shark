#ifndef TILE_H
#define TILE_H
#include "main.h"
#include <iostream>
using namespace std;
using namespace sf;

class tile
{
public:
    int tileID;
    string tileFileLocation;
    sf::Texture tileTexture;
    sf::Sprite tileSprite;
    sf::Vector2i position;
    bool passable;
    bool isOccupied;
    short damagePerTurn;
    short speedBonus;
    short rangeBonus;
    void drawToGrid(int orderX, int orderY,sf::View view, sf::RenderWindow& window);
};

void tile::drawToGrid(int orderX, int orderY,sf::View view, sf::RenderWindow& window){  //orderX is for the x coordinate; orderY for y co. each tile is 1 value.
    view=window.getView();
    sf::FloatRect rect(sf::Vector2f(view.getCenter().x - (view.getSize().x)/2, view.getCenter().y - (view.getSize().y)/2) , view.getSize());
    tile::tileSprite.setPosition(orderX*32,orderY*32);//multiply coordinates by size of tiles
    tile::position.x = orderX; //position 0 is arbitrarily selected for x coordintes in quantities of 32
    tile::position.y = orderY; //position 1 for y
    if (rect.intersects(tile::tileSprite.getGlobalBounds()))
    {
        window.draw(tile::tileSprite);
    }
}



#endif // TILE_H
