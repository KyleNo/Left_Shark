#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

class tilemap
{
    public:
        vector< vector<bool> > passableTile;
        vector<sf::Vector2i> passableTiles;
        vector<int> characterPositionsX, characterPositionsY;
        int height,width;
        int numberOfCharactersPossible;
        vector<tile>tileCollection;
        int mapSize;
        void drawTilemap(int tileBeingUsed, sf::RenderWindow& window);
        int generateTileCollection();
};

//drawToGrid() is used in drawTileMap()
int tilemap::generateTileCollection(){ //finds tile collection using tmx
    int goodtiles=0,badtiles=0;
    sf::Vector2i gridcounter;
    tmxparser::TmxMap yee; //declares tmx map
    tmxparser::TmxReturn error; //error test
    error = tmxparser::parseFromFile("tilemaps/coolmap.tmx", &yee, "tilesets/"); //parses file
    int mapSize = yee.height*yee.width; //finds map size
    int tilemapGrid[mapSize]; //array for tile map numeric values
    numberOfCharactersPossible=0;
    if (!error) //negative error test
    {

        height=yee.height; //sets map height
        width=yee.width; //sets map width
        passableTile.resize(height);
        //Because we're inefficient
        for (int i=0;i<mapSize;i++)
        {
            //tilemapGrid[i]=yee.layerCollection[0].tiles[i].gid;
            tilemapGrid[i]=yee.layerCollection[0].tiles[i].gid;
            gridcounter.x++;
            if (gridcounter.x==width)
            {
                gridcounter.x=0;
                gridcounter.y++;
            }
        }
        //me trying to be efficient
        for (int i=0;i<passableTile.size();i++)
        {
            passableTile[i].resize(width);
        }
        for (int i=0;i<height;i++)
        {
            for (int j=0;j<width;j++)
            {

                if (yee.layerCollection[1].tiles[i+j*width].gid == 6)
                {
                    numberOfCharactersPossible++;
                    characterPositionsX.push_back(gridcounter.x);
                    characterPositionsY.push_back(gridcounter.y);
                }
                cout << tilemapGrid[i+j*width];
                if (tilemapGrid[i+j*width]==2)
                {
                    passableTile[i][j]=false;
                }
                else
                {
                    passableTile[i][j]=true;
                }
            }
            cout << endl;
        }
    tilemap::tileCollection.resize(mapSize);
    int counter = 0;
    for (int bb=0;bb<6;bb++)
    {
        for (int bc=0;bc<mapSize;bc++)
        {
            if (tilemapGrid[bc]==bb)
            {
                tilemap::tileCollection[bc]=tiles[bb-1];
            }
        }
    }
    return tilemapGrid[counter];
    }
}
void tilemap::drawTilemap(int tileBeingUsed, sf::RenderWindow& window){
    int counter = 0;
    for(int aa = 0; aa < height; aa++){
        for(int ab = 0; ab < width; ab++){
            tilemap::tileCollection[counter].drawToGrid(ab,aa,window.getView(), window);
            counter++;
        }
    }
}

#endif // TILEMAP_H_INCLUDED
