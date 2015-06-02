#include <iostream>
#include "simplex.h"
#include <SFML/Graphics.hpp>

using namespace std;

class tile
{
public:
    sf::RectangleShape tile;
};

class water
{
public:
    sf::RectangleShape waterSprite;
    double amountOfWater;
    void waterMovement(double heightmap[50][50], water waterTiles[50][50], int orientation);
};

void water::waterMovement(double heightmap[50][50], water waterTiles[50][50], int orientation)
{
    int resolution, mapsize;
    sf::Vector2i waters;
    waters.x=waterSprite.getPosition().x/10;
    waters.y=waterSprite.getPosition().y/10;
    vector<sf::Vector2i> waterPositions;
    double amountOfWaterToFlow=0;
    if (amountOfWater<.001)
    {
        amountOfWater=0;
    }
    if (waters.x-1>=0 and waters.y-1>=0 and waters.x+1<50 and waters.y+1<50 and amountOfWater>0)
    {
        if (waterTiles[waters.x][waters.y-1].amountOfWater+heightmap[waters.x][waters.y-1]<amountOfWater+heightmap[waters.x][waters.y] and amountOfWater>=.001)
        {
            cout << "one\n";
            waterPositions.push_back(sf::Vector2i(waters.x,waters.y-1));
        }
        if (waterTiles[waters.x+1][waters.y].amountOfWater+heightmap[waters.x+1][waters.y]<amountOfWater+heightmap[waters.x][waters.y] and amountOfWater>=.001)
        {
            cout << "two\n";
            waterPositions.push_back(sf::Vector2i(waters.x+1,waters.y));
        }
        if (waterTiles[waters.x][waters.y+1].amountOfWater+heightmap[waters.x][waters.y+1]<amountOfWater+heightmap[waters.x][waters.y] and amountOfWater>=.001)
        {
            cout << "three\n";
            waterPositions.push_back(sf::Vector2i(waters.x,waters.y+1));
        }
        if (waterTiles[waters.x-1][waters.y].amountOfWater+heightmap[waters.x-1][waters.y]<amountOfWater+heightmap[waters.x][waters.y] and amountOfWater>=.001)
        {
            cout << "four\n";
            waterPositions.push_back(sf::Vector2i(waters.x-1,waters.y));
        }
        amountOfWaterToFlow=amountOfWater/waterPositions.size();
        cout << "\t" << amountOfWater << "\t" << waterPositions.size() << endl;
    }
    for (int i=0;i<waterPositions.size();i++)
    {
        waterTiles[waterPositions[i].x][waterPositions[i].y].amountOfWater+=amountOfWaterToFlow;
    }
    waterPositions.clear();
    amountOfWater-=amountOfWaterToFlow;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "SFML Sucks!");
    window.setFramerateLimit(60);
    double heightmap[50][50];
    water waterTiles[50][50];
    for (int i=0;i<50;i++)
    {
        for (int j=0;j<50;j++)
        {
            waterTiles[i][j].amountOfWater=0;
            waterTiles[i][j].waterSprite.setPosition(i*10,j*10);
            waterTiles[i][j].waterSprite.setFillColor(sf::Color(0,0,255,0));
            waterTiles[i][j].waterSprite.setSize(sf::Vector2f(10,10));
        }
    }
    float islands[3] = {.0015,.0048,.0135};
<<<<<<< HEAD
    int islandsColors[4][3] = {{0, 0, 250},{204, 204, 0},{51,153,51},{102,153,153}};
=======
    int islandsColors[4][3] = {{165, 136, 92},{204, 204, 0},{51,153,51},{102,153,153}};
>>>>>>> origin/WiP
    float plains[3] = {-.01,0,.01};
    int plainsColors[4][3] = {{0, 128, 41},{0, 153, 51},{51, 153, 51},{0, 153, 0}};
    tile tileMap[50][50];
    //1.0 initialize some variables
	time_t beginning = time(NULL);//these two are used to time our algorithm

	srand((unsigned)beginning);//set the random seed

	float map[50][50];//make the empty array

	float min,max; //used to normalize the map

	//now that the blank map is set up, unblank it
	fillMap(map, min, max);
	for (int i=0;i<50;i++)
    {
        for (int j=0;j<50;j++)
        {
            tileMap[i][j].tile.setSize(sf::Vector2f(10,10));
            tileMap[i][j].tile.setPosition(sf::Vector2f(i*10,j*10));
            if (map[i][j]<=islands[0])
            {
                tileMap[i][j].tile.setFillColor(sf::Color(islandsColors[0][0],islandsColors[0][1],islandsColors[0][2]));
                heightmap[i][j]=0;
            }
            else if (map[i][j]<=islands[1])
            {
                tileMap[i][j].tile.setFillColor(sf::Color(islandsColors[1][0],islandsColors[1][1],islandsColors[1][2]));
                heightmap[i][j]=1;
            }
            else if (map[i][j]<=islands[2])
            {
                tileMap[i][j].tile.setFillColor(sf::Color(islandsColors[2][0],islandsColors[2][1],islandsColors[2][2]));
                heightmap[i][j]=2;
            }
            else
            {
                tileMap[i][j].tile.setFillColor(sf::Color(islandsColors[3][0],islandsColors[3][1],islandsColors[3][2]));
                heightmap[i][j]=3;
            }
        }
    }
	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.Closed)
            {
                window.close();
            }
        }
        waterTiles[24][24].amountOfWater=1;
        for (int i=0;i<50;i++)
        {
            for (int j=0;j<50;j++)
            {
                for (int k=0;k<4;k++)
                {
                    waterTiles[i][j].waterMovement(heightmap, waterTiles, k);
                }
                if (waterTiles[i][j].amountOfWater>1)
                {
                    waterTiles[i][j].waterSprite.setFillColor(sf::Color(0,0,255,255));
                }
                else
                {
                    waterTiles[i][j].waterSprite.setFillColor(sf::Color(0,0,255,255*waterTiles[i][j].amountOfWater*10));
                }
            }
        }
        window.clear();
        for (int i=0;i<50;i++)
        {
            for (int j=0;j<50;j++)
            {
                window.draw(tileMap[i][j].tile);
<<<<<<< HEAD
            }
        }
        for (int i=0;i<50;i++)
        {
            for (int j=0;j<50;j++)
            {
                //window.draw(waterTiles[i][j].waterSprite);
=======
                window.draw(waterTiles[i][j].waterSprite);
>>>>>>> origin/WiP
            }
        }

        window.display();
    }
}
