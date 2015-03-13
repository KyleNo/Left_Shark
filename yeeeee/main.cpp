#include "main.h"
#include "resources/TMXParser.h"
sf::RenderWindow window(sf::VideoMode(800,600), "Cool");


void declareTiles(){
    int texturex=0,texturey=0;

    for (int i=0;i<6;i++)  //This loop sets up the tileset
    {
        tiles[i].tileID=i+1;
        tiles[i].tileTexture.loadFromFile("tilesets/tileset.bmp");
        tiles[i].tileSprite.setTexture(tiles[i].tileTexture);
        tiles[i].tileSprite.setTextureRect(sf::IntRect(texturex,texturey,32,32));
        if(i==3)
        {
            tiles[i].passable=false;
        }
        else
        {
            tiles[i].passable=true;
        }
        texturex+=32;
        if (i==3)
        {
            texturey+=32;
            texturex=0;
        }
    }
    tileSelectorValid.tileID = 4;
    tileSelectorValid.tileFileLocation = "SELECT.png";
    tileSelectorValid.tileTexture.loadFromFile(tileSelectorValid.tileFileLocation);

    tileSelectorInvalid.tileID = 5;
    tileSelectorInvalid.tileFileLocation = "REDSELECT.png";
    tileSelectorInvalid.tileTexture.loadFromFile(tileSelectorInvalid.tileFileLocation);
}
void tile::drawToGrid(int orderX, int orderY, sf::View view){  //orderX is for the x coordinate; orderY for y co. each tile is 1 value.
    sf::FloatRect rect(sf::Vector2f(view.getCenter().x - (view.getSize().x)/2, view.getCenter().y - (view.getSize().y)/2) , view.getSize());
    tile::tileSprite.setPosition(orderX*32,orderY*32);//multiply coordinates by size of tiles
    tile::position.x = orderX; //position 0 is arbitrarily selected for x coordintes in quantities of 32
    tile::position.y = orderY; //position 1 for y
    if (rect.intersects(tile::tileSprite.getGlobalBounds()))
    {
        window.draw(tile::tileSprite);
    }
}
//drawToGrid() is used in drawTileMap()
int tilemap::generateTileCollection(sf::View view){ //finds tile collection using tmx
    tmxparser::TmxMap yee; //declares tmx map
    tmxparser::TmxReturn error; //Will be used to check if there's an error in parsing
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
           tilemap::tileCollection[bb] = tiles[0];
            counter++;
        }
        else if(tilemapGrid[counter] == 2){
            tilemap::tileCollection[bb] = tiles[1];
            counter++;
        }
        else if(tilemapGrid[counter] == 3){
            tilemap::tileCollection[bb] = tiles[2];
            counter++;
        }
        else if(tilemapGrid[counter] == 0){
            counter++;
        }
    }
    return tilemapGrid[counter];
}
void tilemap::drawTilemap(sf::View view){
    int counter = 0;
    for(int aa = 0; aa < height; aa++){
        for(int ab = 0; ab < width; ab++){
            tilemap::tileCollection[counter].drawToGrid(ab,aa,view);
            counter++;
        }
    }
}
void tile::isValidMovement(sf::View view){
    if(tile::isOccupied == false && tile::passable == true){
        tileSelectorValid.drawToGrid(tile::position.x, tile::position.y,view);
    }
    else if(tile::isOccupied == true || tile::passable == false){
        tileSelectorInvalid.drawToGrid(tile::position.x, tile::position.y,view);
    }
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
    sf::View view1(sf::Vector2f(400, 300), sf::Vector2f(800, 600));
    view1.setCenter(400,300);
    window.setView(view1);
    window.setFramerateLimit(60);

 tilemap testmap;
    testmap.mapSize = 400;
    tileBeingUsed=testmap.generateTileCollection(view1);
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
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 30)){
                    viewCounterX+=32;
                    view1.setCenter(viewCounterX,viewCounterY);
                    window.setView(view1);
                }}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 30)){
                    viewCounterX-=32;
                    view1.setCenter(viewCounterX,viewCounterY);
                    window.setView(view1);

                }}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 30)){
                        viewCounterY-=32;
                        view1.setCenter(viewCounterX,viewCounterY);
                        window.setView(view1);
                }}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 30)){
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
        testmap.drawTilemap(view1);
        if(checkingValidity){
            for(int aa = 0; aa < testmap.tileCollection.size(); aa++){
                testmap.tileCollection[aa].isValidMovement(view1);
            }
        }
        window.draw(screenText);
        window.display();
    }
    return 0;
}
