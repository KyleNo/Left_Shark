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
        void drawToGrid(int orderX, int orderY,sf::View view, sf::RenderWindow& window);
        void isValidMovement(sf::RenderWindow& window);
    protected:
    private:
};
    tile tiles[9];
    tile grassTile;
    tile sandTile;
    tile waterTile;
    tile tileSelectorValid;
    tile tileSelectorInvalid;
    tile tileCursor;


#endif // TILE_H
