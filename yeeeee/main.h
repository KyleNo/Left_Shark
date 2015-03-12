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


class tilemap
{
    public:
        int height,width;
        vector<tile>tileCollection;
        int mapSize;
        void drawTilemap(int tileBeingUsed);
        int generateTileCollection();
};
class ability{
public:

};
class heroClass{
public:
    vector<ability> jobAbilities;

};
class structure{
public:
    bool passable;
    short healingPerTurn;
    short speedBonus;
    short rangeBonus;

};
class hero{
public:
    heroClass job;
    vector<int>stats;
    vector<ability>jobAbilities;


};
class weapon{
public:
    vector<int>stats;

};


#endif // MAIN_H_INCLUDED
