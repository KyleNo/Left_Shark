#include <iostream>
#include <fstream>
#include <vector>
#include "resources/TMXParser.h"

using namespace std;

class loadedmap
{
public:
    int height;
    int width;
    vector<int>data;
};

int main()
{
    loadedmap progress;
    tmxparser::TmxMap yee;
    tmxparser::TmxReturn error;
    error = tmxparser::parseFromFile("coolmap.tmx", &yee, "tilesets/");

    if (!error)
    {
        progress.height=yee.height;
        progress.width=yee.width;
        for(auto it=yee.tilesetCollection.begin();it!=yee.tilesetCollection.end();++it)
        {
            progress.data.push_back(yee.tilesetCollection[it]);
        }
    }
}
