#include "resources/rapidjson/rapidjson.h"
#include "resources/rapidjson/filestream.h"
#include "resources/rapidjson/document.h"
#include <iostream>
#include <fstream>
#include <vector>

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
    loadedmap shittyshit;
    FILE * pFile = fopen ("minimal.json" , "r");
    rapidjson::FileStream is(pFile);
    rapidjson::Document document;
    document.ParseStream<0>(is);
    const rapidjson::Value& a = document["data"];
//    assert(document["height"].IsInt());
//    assert(document["height"].IsInt());
//    shittyshit.height=document["height"];
//    shittyshit.width=document["width"];
    shittyshit.height=100;
    shittyshit.width=100;
    for (rapidjson::SizeType i=0;i<sizeof(a);i++)
    {
        shittyshit.data.push_back(a[i].GetInt());
    }
    for (int i=0;i<shittyshit.height;i++)
    {
        for (int j=0;j<shittyshit.width;j++)
        {
            cout << shittyshit.data[i*shittyshit.height+j];
        }
        cout << endl;
    }
}
