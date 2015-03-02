#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "rapidjson-master\include\rapidjson\document.h"
#include "rapidjson-master\include\rapidjson\writer.h"
#include "rapidjson-master\include\rapidjson\stringBuffer.h"
using namespace std;
using namespace rapidjson;
#include <vector>
#include "windows.h"
#include "tile.h"
#include "string.h"
#include <iostream>
#include <math.h>


class tilemap
{
    public:
        vector<tile>tileCollection;
        int mapSize;
        Document jsonDoc;
        void drawTilemap();
        void generateTileCollection();
    protected:
    private:
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
    vector<ability> jobAbilities;


};
class weapon{
public:
    vector<int>stats;

};


#endif // MAIN_H_INCLUDED
