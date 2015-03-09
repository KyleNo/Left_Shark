#include <iostream>
#include <fstream>
#include <vector>
#include "resources/TMXParser.h"

using namespace std;



int main()
{
    tmxparser::TmxMap yee;
    tmxparser::TmxReturn error;
    error = tmxparser::parseFromFile("coolmap.tmx", &yee, "tilesets/");

    if (!error)
    {
        for (int i =0;i<512;i++)
        {
        cout << yee.layerCollection[0].tiles[i].gid << endl;
        }
    }
}

