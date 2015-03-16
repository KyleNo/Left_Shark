#include "main.h"
#include "resources/TMXParser.h"
sf::RenderWindow window(sf::VideoMode(800,600), "Cool");


void declareTiles(){
    grassTile.tileID = 1;
    grassTile.passable = true;
    grassTile.tileTexture.loadFromFile("tilesets/tileset.bmp");
    grassTile.tileSprite.setTexture(grassTile.tileTexture);
    grassTile.tileSprite.setTextureRect(sf::IntRect(32,0,32,32));

    sandTile.tileID = 2;
    sandTile.passable = true;
    sandTile.tileTexture.loadFromFile("tilesets/tileset.bmp");
    sandTile.tileSprite.setTexture(sandTile.tileTexture);
    sandTile.tileSprite.setTextureRect(sf::IntRect(0,0,32,32));

    waterTile.tileID = 3;
    waterTile.passable = false;
    waterTile.tileTexture.loadFromFile("tilesets/tileset.bmp");
    waterTile.tileSprite.setTexture(waterTile.tileTexture);
    waterTile.tileSprite.setTextureRect(sf::IntRect(64,0,32,32));

    tileSelectorValid.tileID = 4;
    tileSelectorValid.tileFileLocation = "SELECT.png";
    tileSelectorValid.tileTexture.loadFromFile(tileSelectorValid.tileFileLocation);

    tileSelectorInvalid.tileID = 5;
    tileSelectorInvalid.tileFileLocation = "REDSELECT.png";
    tileSelectorInvalid.tileTexture.loadFromFile(tileSelectorInvalid.tileFileLocation);

    tileCursor.tileID = 6;
    tileCursor.tileFileLocation = "WHITESELECT.png";
    tileCursor.tileTexture.loadFromFile(tileCursor.tileFileLocation);
    tileCursor.tileSprite.setTexture(tileCursor.tileTexture);
}
void tile::drawToGrid(int orderX, int orderY){  //orderX is for the x coordinate; orderY for y co. each tile is 1 value.
    tile::tileSprite.setTexture(tile::tileTexture);
    tile::tileSprite.setPosition(orderX*32,orderY*32);//multiply coordinates by size of tiles
    tile::position.x = orderX; //position 0 is arbitrarily selected for x coordintes in quantities of 32
    tile::position.y = orderY; //position 1 for y
    window.draw(tile::tileSprite); //draws tile
}
//drawToGrid() is used in drawTileMap()
int tilemap::generateTileCollection(){ //finds tile collection using tmx
    tmxparser::TmxMap yee; //declares tmx map
    tmxparser::TmxReturn error; //error test
    error = tmxparser::parseFromFile("tilemaps/island.tmx", &yee, "tilesets/"); //parses file
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
           tilemap::tileCollection[bb] = sandTile;
            counter++;
        }
        else if(tilemapGrid[counter] == 2){
            tilemap::tileCollection[bb] = grassTile;
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
    return tilemapGrid[counter];
}
void tilemap::drawTilemap(int tileBeingUsed){
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
void selectTile(sf::Vector2i screenPos){
    tileSelectorInvalid.drawToGrid(screenPos.x/32 + .5, screenPos.y/32 + .5);
}
int main(){
    int tileBeingUsed;
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
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(800, 600));
    view1.setCenter(0,0);
    window.setView(view1);
    window.setFramerateLimit(60);

 tilemap testmap;
    testmap.mapSize = 400;
    tileBeingUsed=testmap.generateTileCollection();
    bool buttonPressed = false;
    bool checkingValidity = false;
    bool mousePressed = false;
    sf::Vector2i mousePos;
    while (window.isOpen()){
        screenText.setOrigin(-viewCounterX + 310, -viewCounterY + 310);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
                    {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)){//tile validity
            screenText.setString("Tile Validity Shown");
            checkingValidity = true;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){//screen movement
            screenText.setString("View movement enabled, use the arrow keys");
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 30)){
                    view1.move(32,0);
                    window.setView(view1);
                }}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 30)){
                    view1.move(-32,0);
                    window.setView(view1);

                }}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 30)){
                        view1.move(0,-32);
                        window.setView(view1);
                }}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 30)){
                    view1.move(0,32);
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
        //Mouse tile stuff
        sf::Vector2i screenPos;
        mousePos = sf::Mouse::getPosition(window);
        screenPos.x = window.mapPixelToCoords(mousePos).x;
        screenPos.y = window.mapPixelToCoords(mousePos).y;
        tileCursor.position.x = screenPos.x/32+.5;
        tileCursor.position.y = screenPos.y/32+.5;
        if (event.type == sf::Event::MouseButtonPressed){
            if (event.mouseButton.button == sf::Mouse::Left){
                screenText.setString("Mouse pressed");
                mousePressed = true;
            }
        }else mousePressed = false;
        //Mouse tile stuff
        if(mousePressed) selectTile(screenPos);
        testmap.drawTilemap(tileBeingUsed);
        if(checkingValidity){
            for(int aa = 0; aa < testmap.tileCollection.size(); aa++){
                testmap.tileCollection[aa].isValidMovement();
            }}
        tileCursor.drawToGrid(tileCursor.position.x, tileCursor.position.y);
        window.draw(screenText);
        window.display();
        window.clear();
    }
    return 0;
}
