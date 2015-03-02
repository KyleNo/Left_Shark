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
        int position[2];
        bool passable;
        short damagePerTurn;
        short speedBonus;
        short rangeBonus;
        void drawToGrid(int orderX, int orderY);
    protected:
    private:
};
    tile grassTile;
    tile sandTile;
    tile waterTile;


#endif // TILE_H
