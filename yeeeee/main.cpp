#include "game.h"
#include "menuDeclare.h"
#include "resources/TMXParser.h"


int main(){
    sf::RenderWindow window(sf::VideoMode(800,600), "Cool");
    window.setFramerateLimit(60);
    startMenu(window);
    {
    tile tiles[9];
    bool mouseHovering=false;
    int selectedHero;
    window.setSize(sf::Vector2u(800,640));
    loading(window);
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
    view1.setCenter(0,0);
    window.setView(view1);
    window.setFramerateLimit(60);
    tilemap testmap;
    testmap.mapSize = 400;
    tileBeingUsed=testmap.generateTileCollection();


    //this is where we designate the heroes.
    hero heroes[testmap.numberOfCharactersPossible];
    for (int i=0;i<testmap.numberOfCharactersPossible;i++)
    {
        heroes[i].assignhero();
    }


    bool buttonPressed = false;
    bool checkingValidity = false;
    bool mousePressed = false;
    sf::Vector2i mousePos;
    view1.move(400,320); //sets view to top left corner
    while (window.isOpen()){

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
        else
        {
            checkingValidity = false;
        }
        //screen movement
        screenText.setString("View movement enabled, use the arrow keys");
        if(sf::Mouse::getPosition(window).x > 672 and view1.getCenter().x < testmap.width*32-400){//right
            framerateCounter++;
            if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 5)){
                view1.move(32,0);
                viewCounterX+=32;
                window.setView(view1);
            }}
        if(sf::Mouse::getPosition(window).x < 128 and view1.getCenter().x>400 ){//left
            framerateCounter++;
            if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 5)){
                view1.move(-32,0);
                viewCounterX-=32;
                window.setView(view1);
            }
        }
        if(sf::Mouse::getPosition(window).y < 128 and view1.getCenter().y > 320){//up
            framerateCounter++;
            if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 5)){
                    view1.move(0,-32);
                    viewCounterY-=32;
                    window.setView(view1);
            }
        }
        if(sf::Mouse::getPosition(window).y > 472 and view1.getCenter().y < testmap.height*32-320){//down
            framerateCounter++;
            if(((buttonPressed == true) && (framerateCounter == 1)) || (framerateCounter >= 5)){
                view1.move(0,32);
                viewCounterY+=32;
                window.setView(view1);
            }
        }
        if((sf::Mouse::getPosition(window).y > 472 and view1.getCenter().y < testmap.height*32-320) or (sf::Mouse::getPosition(window).y < 128 and view1.getCenter().y > 320) or (sf::Mouse::getPosition(window).x < 128 and view1.getCenter().x>400 ) or (sf::Mouse::getPosition(window).x > 672 and view1.getCenter().x < testmap.width*32-400)) {
            buttonPressed = true;
        }
        else{
            buttonPressed = false;
        }

//        else {
//            screenText.setString("null");
//            buttonPressed = false;
//            checkingValidity = false;
//        }
        //Mouse tile stuff
        sf::Vector2i screenPos;
        mousePos = sf::Mouse::getPosition(window);
        screenPos.x = window.mapPixelToCoords(mousePos).x;
        screenPos.y = window.mapPixelToCoords(mousePos).y;
        tiles[8].position.x = screenPos.x/32+.5;
        tiles[8].position.y = screenPos.y/32+.5;
        int mousePositionx=(mousePos.x/32)*32, mousePositiony=(mousePos.y/32)*32;
//        cout << "PlayerPosition: " << heroes[0].sprite.getPosition().x <<"," << heroes[0].sprite.getPosition().y << endl;
//        cout << "Mouse Position: " << tiles[8].tileSprite.getPosition().x << "," << tiles[8].tileSprite.getPosition().y << endl;
        if (event.type == sf::Event::MouseButtonPressed and actionMenu == false){
                sf::Vector2i playerPosition;
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    screenText.setString("Mouse pressed");
                    mousePressed = true;

                    for (int i=0;i<testmap.numberOfCharactersPossible;i++)
                    {
                        if (tiles[8].tileSprite.getPosition().x==(heroes[i].sprite.getPosition().x/32)*32 && tiles[8].tileSprite.getPosition().y==(heroes[i].sprite.getPosition().y/32)*32)
                        {
                            selectedHero=i;
                            mouseHovering=true;
                            break;
                        }
                        else
                        {
                            mouseHovering=false;
                            selectedHero = -1;
                        }
                    }
                    if(selectedHero > -1){
                        actionMenu = true;
                    }
                }
            }
        else mousePressed = false;

        //Mouse tile stuff
        testmap.drawTilemap(tileBeingUsed, window);
        if(checkingValidity){
            for(int aa = 0; aa < testmap.tileCollection.size(); aa++){
                testmap.tileCollection[aa].isValidMovement(window);
            }
        }
    if(!actionMenu)
    {
        cout << "whyyyyyyyyyyy\n";
    }
    if(actionMenu){
        hero user;
        user = heroes[selectedHero];
        View windowView = window.getView();


        Vector2i screenPosition = window.mapCoordsToPixel(windowView.getCenter());
        heroMove.setButton(user.Position.x + 50, user.Position.y, "resources/images/moveButton.png");
        heroAction.setButton(user.Position.x - 125, user.Position.y, "resources/images/attackButton.png");
        menuCancel.setButton(user.Position.x - 35, user.Position.y - 50, "resources/images/whiteCancel.png");

        heroMove.bSize=sf::Vector2i(100,50);
        heroAction.bSize=sf::Vector2i(100,50);
        menuCancel.bSize=sf::Vector2i(100,50);
        //if (event.type == Event::MouseButtonPressed){
            //heroes[selectedHero].rangecheck(testmap.passableTile, window);
            if (event.mouseButton.button == Mouse::Left and (heroMove.hovercheck(mousePos)==true || heroAction.hovercheck(mousePos) == true || menuCancel.hovercheck(mousePos) == true)){
                cout << "Nice";
                if(heroMove.hovercheck(mousePos)){
                    //heroes[selectedHero].rangecheck(testmap.passableTile, window);
                    cout << " WOOP " << endl;
                }
                else if(heroAction.hovercheck(mousePos)){
                    //null
                    cout << "WOP" << endl;
                }
                else if(menuCancel.hovercheck(mousePos)){
                    actionMenu = false;
                    cout << "BYEEEE" << endl;
                }
                else{
                    cout << "BYEEE" << endl;
                    actionMenu = false;
                }
            }
    if(actionMenu){
    hero user;
    user = heroes[selectedHero];
    View windowView = window.getView();
    Vector2i screenPosition = window.mapCoordsToPixel(windowView.getCenter());
    heroMove.setButton((user.Position.x)*32 + 50, (user.Position.y)*32, "resources/images/moveButton.png");
    heroAction.setButton((user.Position.x)*32 - 125, (user.Position.y)*32, "resources/images/attackButton.png");
    menuCancel.setButton((user.Position.x)*32 - 35, (user.Position.y)*32 - 50, "resources/images/whiteCancel.png");
            if (event.type == Event::MouseButtonPressed){
                    //heroes[selectedHero].rangecheck(testmap.passableTile, window);
                if (event.mouseButton.button == Mouse::Left and (heroMove.hover==true || heroAction.hover == true || menuCancel.hover == true)){
                    cout << "Nice";
                    if(heroMove.hover==true){
                        heroes[selectedHero].rangecheck(testmap.passableTile, window);
                        cout << " WOOP " << endl;
                    }
                    else if(heroAction.hover == true){
                        //null
                        cout << "WOP" << endl;
                    }
                    else if(menuCancel.hover == true){
                        actionMenu = false;
                        cout << "BYEEEE" << endl;
                    }
                    else{
                        cout << "BYEEE" << endl;
                        actionMenu = false;
                    }
                }
            }
        }
    //}
    //heroMove.buttonSelection(heroMove.coordinates, mousePos);
    //heroAction.buttonSelection(heroAction.coordinates, mousePos);
    //menuCancel.buttonSelection(menuCancel.coordinates, mousePos);
    heroMove.button.setPosition(heroMove.coordinates.x,heroMove.coordinates.y);
    heroAction.button.setPosition(heroAction.coordinates.x, heroAction.coordinates.y);
    menuCancel.button.setPosition(menuCancel.coordinates.x, menuCancel.coordinates.y);

    if (!actionMenu)selectTile(screenPos, window);
        for (int i=0;i<testmap.numberOfCharactersPossible;i++)
        {
            heroes[i].placehero(window, testmap.characterPositionsX[i]*32,testmap.characterPositionsY[i]*32);
        }
        screenText.setOrigin(-viewCounterX + 310, -viewCounterY + 310);
        tiles[8].drawToGrid(tiles[8].position.x, tiles[8].position.y,window.getView(), window);
        window.draw(screenText);
        if(actionMenu){
            window.draw(heroMove.button);
            window.draw(heroAction.button);
            window.draw(menuCancel.button);
        }
        window.display();
        window.clear();
    }
    }
    return 0;
    }
}
