#include <iostream>
#include "resources/TMXParser.h"

void loadMap(std::string filename, std::string tilesetFilePath)
{
    tmxparser::TmxMap tilemap;
    tmxparser::TmxReturn error;
    tmxparser::parseFromFile("otherplace", &tilemap, "place");
}
