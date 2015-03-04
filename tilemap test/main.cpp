#include <iostream>
#include <fstream>
#include <vector>
#include "resources/tmxparser.h"

using namespace std;

class loadedmap
{
public:
    int height;
    int width;
    vector<int> data;
};

int main()
{
    tmxparser::TmxMap yee;
    tmxparser::TmxReturn error = tmxparser::parseFromFile() )
}
