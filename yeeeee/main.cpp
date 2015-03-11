#include "main.h"
#include "resources/TMXParser.h"
sf::RenderWindow window(sf::VideoMode(640,640), "Cool");



void declareTiles(){
    string tilesetlocation="tilesets/tileset.bmp";
    grassTile.tileID = 1;
    grassTile.passable = true;
    grassTile.tileFileLocation = "grass.png";
    grassTile.tileTexture.loadFromFile(grassTile.tileFileLocation);

    sandTile.tileID = 2;
    sandTile.passable = true;
    sandTile.tileFileLocation = "Sand.png";
    sandTile.tileTexture.loadFromFile(sandTile.tileFileLocation);

    waterTile.tileID = 3;
    waterTile.passable = false;
    waterTile.tileFileLocation = "Water.png";
    waterTile.tileTexture.loadFromFile(waterTile.tileFileLocation);

    tileSelectorValid.tileID = 4;
    tileSelectorValid.tileFileLocation = "SELECT.png";
    tileSelectorValid.tileTexture.loadFromFile(tileSelectorValid.tileFileLocation);

    tileSelectorInvalid.tileID = 5;
    tileSelectorInvalid.tileFileLocation = "REDSELECT.png";
    tileSelectorInvalid.tileTexture.loadFromFile(tileSelectorInvalid.tileFileLocation);
}
void tile::drawToGrid(int orderX, int orderY){
    tile::tileSprite.setTexture(tile::tileTexture);
    tile::tileSprite.setPosition(orderX*32,orderY*32);
    tile::position[0] = orderX;
    tile::position[1] = orderY;
    window.draw(tile::tileSprite);
}
void tilemap::generateTileCollection(){
    tmxparser::TmxMap yee;
    tmxparser::TmxReturn error;
    error = tmxparser::parseFromFile("tilemaps/coolmap.tmx", &yee, "tilesets/");
    int mapSize = yee.height*yee.width;
    int tilemapGrid[mapSize];
    if (!error)
    {
        height=yee.height;
        width=yee.width;
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
        tileSelectorValid.drawToGrid(tile::position[0], tile::position[1]);
    }
    else{
        tileSelectorInvalid.drawToGrid(tile::position[0], tile::position[1]);
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
                if(buttonPressed == true && framerateCounter == 1 || framerateCounter >= 90){
                    viewCounterX+=32;
                    view1.setCenter(viewCounterX,viewCounterY);
                    window.setView(view1);
                }}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                buttonPressed = true;
                framerateCounter++;
                if(buttonPressed == true && framerateCounter == 1 || framerateCounter >= 90){
                    viewCounterX-=32;
                    view1.setCenter(viewCounterX,viewCounterY);
                    window.setView(view1);

                }}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                buttonPressed = true;
                framerateCounter++;
                if(buttonPressed == true && framerateCounter == 1 || framerateCounter >= 90){
                        viewCounterY-=32;
                        view1.setCenter(viewCounterX,viewCounterY);
                        window.setView(view1);
                }}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                buttonPressed = true;
                framerateCounter++;
                if(buttonPressed == true && framerateCounter == 1 || framerateCounter >= 90){
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
