#ifndef TILE_H
#define TILE_H
#include "string.h"
#include "main.h"

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
        void drawToGrid(int orderX, int orderY);
        void isValidMovement();
    protected:
    private:
        int tileLocationArray[3][4]={{0,32,32,32},{0,0,32,32},{0,64,32,32}};
};
    tile grassTile;
    tile sandTile;
    tile waterTile;
    tile tileSelectorValid;
    tile tileSelectorInvalid;
    tile tileCursor;


#endif // TILE_H
