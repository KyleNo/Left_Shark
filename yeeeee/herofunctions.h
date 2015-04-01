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
    void rangecheck(vector<int>passabletilesx, vector<int>passabletilesy,sf::RenderWindow& window, sf::Vector2i Position);
};

class weapon{
public:
    vector<int>stats;

};

void hero::rangecheck(vector<int> passabletilex, vector<int> passabletiley,sf::RenderWindow& window, sf::Vector2i Position)
{
    sf::Vector2i positioncheck,positionalter;//this isn't necessary yet.
    int range=5;//this is the range.
    positioncheck.x=sprite.getPosition().x;//this is the position of the hero getting his paths found
    positioncheck.y=sprite.getPosition().y;
    for (int j=-5;j<=5;j++)//this is the initialization of a for loop
    {
        for (int i=0;i<range-abs(j);i++)//this is the initialization of a for loop
        {

            if (-passabletilex[i]==1 and passabletiley[j]==1)//this is an if statement to check if the spot at Y,-X is cool
            {
                traversibletilesx.push_back(-passabletilex[i]);//"Yes, you may step on this X coordinate
                traversibletilesy.push_back(passabletiley[j]);//"Yes, you may step on this Y coordinate
            }
            if (passabletilex[i]==1 and passabletiley[j]==1)//this is an if statement to check if the spot at Y, X is cool
            {
                traversibletilesx.push_back(passabletilex[i]);//"Yes, you may step on this X coordinate
                traversibletilesy.push_back(passabletiley[j]);//"Yes, you may step on this Y coordinate
            }
        }
    }

    tile validTiles[traversibletilesx.size()];//an array of "Sure, you may step here" tiles the size of the amount of tiles you can step on.
    for (int i=0;i<traversibletilesx.size();i++)//this is the initialization of a for loop
    {
        validTiles[i]=tiles[7];//the "Sure, you may step here" tiles have the same properties as a valid tile.
        validTiles[i].tileSprite.setPosition(traversibletilesx[i]*32,traversibletilesy[i]*32);//This is where we tell it where to go.
        window.draw(validTiles[i].tileSprite);//put the pencil to the paper
    }
}







void hero::assignhero()
{
    texture.loadFromFile("TestChar.png");
    sprite.setTexture(texture);
}

void hero::placehero(sf::RenderWindow& window, int characterx, int charactery)
{
    sprite.setPosition(characterx,charactery);
    Position.x=sprite.getPosition().x;
    Position.y=sprite.getPosition().y;
    window.draw(sprite);
}
#endif // HEROFUNCTIONS_H_INCLUDED
