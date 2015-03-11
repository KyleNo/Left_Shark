#include "main.h"
#include "resources/TMXParser.h"
sf::RenderWindow window(sf::VideoMode(640,640), "Cool"); //renders window



void declareTiles(){
    string tilesetlocation="tilesets/tileset.bmp"; //sets tileset
    //tiles:
    grassTile.tileID = 1; //gives grass tiles numeric value for drawing
    grassTile.passable = true; //determines whether or not a tile can be traveled on
    grassTile.tileFileLocation = "grass.png"; //selects image for tile
    grassTile.tileTexture.loadFromFile(grassTile.tileFileLocation); //loads tile from tile set

    sandTile.tileID = 2;
    sandTile.passable = true;
    sandTile.tileFileLocation = "Sand.png";
    sandTile.tileTexture.loadFromFile(sandTile.tileFileLocation);

    waterTile.tileID = 3;
    waterTile.passable = false;
    waterTile.tileFileLocation = "Water.png";
    waterTile.tileTexture.loadFromFile(waterTile.tileFileLocation);
    //tile validity:
    tileSelectorValid.tileID = 4;
    tileSelectorValid.tileFileLocation = "SELECT.png";
    tileSelectorValid.tileTexture.loadFromFile(tileSelectorValid.tileFileLocation);

    tileSelectorInvalid.tileID = 5;
    tileSelectorInvalid.tileFileLocation = "REDSELECT.png";
    tileSelectorInvalid.tileTexture.loadFromFile(tileSelectorInvalid.tileFileLocation);
}
void tile::drawToGrid(int orderX, int orderY){  //orderX is for the x coordinate; orderY for y co. each tile is 1 value.
    tile::tileSprite.setTexture(tile::tileTexture);
    tile::tileSprite.setPosition(orderX*32,orderY*32);//multiply coordinates by size of tiles
    tile::position.x = orderX; //position 0 is arbitrarily selected for x coordintes in quantities of 32
    tile::position.y = orderY; //position 1 for y
    window.draw(tile::tileSprite); //draws tile
}
//drawToGrid() is used in drawTileMap()
void tilemap::generateTileCollection(){ //finds tile collection using tmx
    tmxparser::TmxMap yee; //declares tmx map
    tmxparser::TmxReturn error; //error test
    error = tmxparser::parseFromFile("tilemaps/coolmap.tmx", &yee, "tilesets/"); //parses file
    int mapSize = yee.height*yee.width; //finds map size
    int tilemapGrid[mapSize]; //array for tile map numeric values
    if (!error) //negative error test
    {
        height=yee.height; //sets map height
        width=yee.width; //sets map width
        for (int i =0;i<mapSize;i++)
        {
            tilemapGrid[i]=yee.layerCollection[0].tiles[i].gid;
        }
    }
    tilemap::tileCollection.resize(mapSize);
    int counter = 0;
    for(int bb = 0; bb < mapSize; bb++){
        if(tilemapGrid[counter] == 1){
           tilemap::tileCollection[bb] = grassTile;
            counter++;
        }
        else if(tilemapGrid[counter] == 2){
            tilemap::tileCollection[bb] = sandTile;
            counter++;
        }
        else if(tilemapGrid[counter] == 3){
            tilemap::tileCollection[bb] = waterTile;
            counter++;
        }
        else if(tilemapGrid[counter] == 0){
            counter++;
        }
    }
}
void tilemap::drawTilemap(){
    int counter = 0;
    for(int aa = 0; aa < height; aa++){
        for(int ab = 0; ab < width; ab++){
            tilemap::tileCollection[counter].drawToGrid(ab,aa);
            counter++;
        }
    }
}
void tile::isValidMovement(){
    if(tile::isOccupied == false && tile::passable == true){
        tileSelectorValid.drawToGrid(tile::position.x, tile::position.y);
    }
    else{
        tileSelectorInvalid.drawToGrid(tile::position.x, tile::position.y);
    }
}
int main(){
    sf::Font font;
    font.loadFromFile("neoteric.ttf");
    sf::Text screenText;
    screenText.setString("null");
    screenText.setFont(font);
    screenText.setCharacterSize(12);
    screenText.setColor(sf::Color::Red);
    declareTiles();
    int viewCounterX = 0;
    int viewCounterY = 0;
    int framerateCounter = 0;
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(640, 640));
    view1.setCenter(0,0);
    window.setView(view1);
    window.setFramerateLimit(60);

 tilemap testmap;
    testmap.mapSize = 400;
    testmap.generateTileCollection();
    bool buttonPressed = false;
    bool checkingValidity = false;
    sf::Vector2f mousePos;
    while (window.isOpen()){
        screenText.setOrigin(-viewCounterX + 310, -viewCounterY + 310);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)

                window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed){
            if (event.mouseButton.button == sf::Mouse::Left){
                screenText.setString("Mouse pressed");
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)){//tile validity
            screenText.setString("Tile Validity Shown");
            checkingValidity = true;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){//screen movement
            screenText.setString("View movement enabled, use the arrow keys");
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 90)){
                    viewCounterX+=32;
                    view1.setCenter(viewCounterX,viewCounterY);
                    window.setView(view1);
                }}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 90)){
                    viewCounterX-=32;
                    view1.setCenter(viewCounterX,viewCounterY);
                    window.setView(view1);

                }}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 90)){
                        viewCounterY-=32;
                        view1.setCenter(viewCounterX,viewCounterY);
                        window.setView(view1);
                }}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 90)){
                    viewCounterY+=32;
                    view1.setCenter(viewCounterX,viewCounterY);
                    window.setView(view1);
                }}
            else {
                buttonPressed = false;
                framerateCounter = 0;
            }}
        else {
                screenText.setString("null");
                buttonPressed = false;
                checkingValidity = false;
            }
        window.clear();
        testmap.drawTilemap();
        if(checkingValidity){
            for(int aa = 0; aa < testmap.tileCollection.size(); aa++){
                testmap.tileCollection[aa].isValidMovement();
            }
        }
        window.draw(screenText);
        window.display();
    }
    return 0;
}
