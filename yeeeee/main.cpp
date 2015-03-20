#include "main.h"
#include "resources/TMXParser.h"
sf::RenderWindow window(sf::VideoMode(800,640), "Cool");


void declareTiles(){
    int tilex=0,tiley=0;
    for (int i=0;i<9;i++)
    {
        tiles[i].tileID=i+1;
        tiles[i].tileTexture.loadFromFile("tilesets/tileset.png");
        tiles[i].tileSprite.setTexture(tiles[i].tileTexture);
        tiles[i].tileSprite.setTextureRect(sf::IntRect(tilex,tiley,32,32));
        if (tiles[i].tileID==3)
        {
            tiles[i].passable=false;
        }
        else
        {
            tiles[i].passable=true;
        }
        tilex+=32;
        if (tilex==96)
        {
            tilex=0;
            tiley+=32;
        }
    }

}
void tile::drawToGrid(int orderX, int orderY,sf::View view){  //orderX is for the x coordinate; orderY for y co. each tile is 1 value.
    view=window.getView();
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
int tilemap::generateTileCollection(){ //finds tile collection using tmx
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
void tilemap::drawTilemap(int tileBeingUsed){
    int counter = 0;
    for(int aa = 0; aa < height; aa++){
        for(int ab = 0; ab < width; ab++){
            tilemap::tileCollection[counter].drawToGrid(ab,aa,window.getView());
            counter++;
        }
    }
}
void tile::isValidMovement(){
    if(tile::isOccupied == false && tile::passable == true){
        tiles[7].drawToGrid(tile::position.x, tile::position.y,window.getView());
    }
    else{
        tiles[6].drawToGrid(tile::position.x, tile::position.y,window.getView());
    }
}
void selectTile(sf::Vector2i screenPos){
    tileSelectorInvalid.drawToGrid(screenPos.x/32 + .5, screenPos.y/32 + .5,window.getView());
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
    int viewCounterX = -64;
    int viewCounterY = -0;
    int framerateCounter = 0;
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(800, 640));
    view1.setCenter(16,0);
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
                    viewCounterX+=32;
                    window.setView(view1);
                }}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 30)){
                    view1.move(-32,0);
                    viewCounterX-=32;
                    window.setView(view1);

                }}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 30)){
                        view1.move(0,-32);
                        viewCounterY-=32;
                        window.setView(view1);
                }}
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                buttonPressed = true;
                framerateCounter++;
                if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 30)){
                    view1.move(0,32);
                    viewCounterY+=32;
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
        tiles[8].position.x = screenPos.x/32+.5;
        tiles[8].position.y = screenPos.y/32+.5;
        if (event.type == sf::Event::MouseButtonPressed){
            if (event.mouseButton.button == sf::Mouse::Left){
                screenText.setString("Mouse pressed");
                mousePressed = true;
            }
        }else mousePressed = false;
        //Mouse tile stuff
        testmap.drawTilemap(tileBeingUsed);
        if(checkingValidity){
            for(int aa = 0; aa < testmap.tileCollection.size(); aa++){
                testmap.tileCollection[aa].isValidMovement();
            }}
        if(mousePressed) selectTile(screenPos);
        tiles[8].drawToGrid(tiles[8].position.x, tiles[8].position.y,window.getView());
        window.draw(screenText);
        window.display();
        window.clear();
    }
    return 0;
}
