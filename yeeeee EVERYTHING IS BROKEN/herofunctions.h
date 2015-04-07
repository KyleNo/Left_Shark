#ifndef HEROFUNCTIONS_H_INCLUDED
#define HEROFUNCTIONS_H_INCLUDED

class ability{
public:

};

class heroClass{
public:
    vector<ability> jobAbilities;
};

class hero{
public:
    vector<int> traversibletilesx, traversibletilesy;
    int range;
    sf::Texture texture;
    sf::Sprite sprite;
    heroClass job;
    vector<int>stats;
    vector<ability>jobAbilities;
    sf::Vector2i Position;
    void placehero(sf::RenderWindow& window,int characterx, int charactery);
    void assignhero();
    void rangecheck(vector < vector<int> > passableTiles,sf::RenderWindow& window);
};

class weapon{
public:
    vector<int>stats;

};

void hero::rangecheck(vector < vector<int> > passableTiles,sf::RenderWindow& window)
{
    sf::Vector2i positioncheck,positionalter;//this isn't necessary yet.
    int range=5;//this is the range.
    int invalidCounter = 0;
    cout << "test1\n";
    for (int j=-range;j<=range;j++)//this is the initialization of a for loop
    {
        cout << "test2\n";
        for (int i=0;i<=range-abs(j);i++)//this is the initialization of a for loop
        {
            cout << "test3\n";
            Position.x=sprite.getPosition().x,Position.y=sprite.getPosition().y;
            if (passableTiles[Position.y-abs(j)][Position.x-i]==1)//this is an if statement to check if the spot at Y,-X is cool
            {
                cout << "Yes\n";
            }
            if (passableTiles[Position.y-abs(j)][Position.x+i]==1)//this is an if statement to check if the spot at Y, X is cool
            {
                cout << "Yes\n";
            }
            else invalidCounter++;
        }
    }
    cout << invalidCounter << endl;
    tile validTiles[traversibletilesx.size()];//an array of "Sure, you may step here" tiles the size of the amount of tiles you can step on.
    for (int i=0;i<traversibletilesx.size();i++)//this is the initialization of a for loop
    {
        validTiles[i]=tiles[6];//the "Sure, you may step here" tiles have the same properties as a valid tile.
        validTiles[i].tileSprite.setPosition(traversibletilesx[i]*32,traversibletilesy[i]*32);//This is where we tell it where to go.
        window.draw(validTiles[i].tileSprite);//put the pencil to the paper
    }
}
void hero::assignhero(){
    if(!texture.loadFromFile("resources/images/TestChar.png")){
        //error...
    }
    sprite.setTexture(texture);
}
void hero::placehero(sf::RenderWindow& window, int characterx, int charactery){
    sprite.setPosition(characterx,charactery);
    Position.x=sprite.getPosition().x;
    Position.y=sprite.getPosition().y;
    window.draw(sprite);
}
#endif // HEROFUNCTIONS_H_INCLUDED
