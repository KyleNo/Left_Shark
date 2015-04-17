#ifndef HEROFUNCTIONS_H_INCLUDED
#define HEROFUNCTIONS_H_INCLUDED
struct hero;
class ability{
public:
     string abilityName;
     bool isAttack;
     bool isHeal;
     bool isBuff;
     int abilityPotency;
     float abilityModifier;
     int range;
     int radius;
     int forTurns;
     int statAffected;
     void useAbility(hero user, hero target);
     void abilityHeal(hero user, hero target);
     void abilityAttack(hero user, hero target);
     void abilityBuff(hero user, hero target);
};
class heroClass{
public:
    vector<ability> jobAbilities;
};

class hero{
public:
    vector<sf::Vector2i> traversableTiles;
    int range;
    sf::Texture texture;
    sf::Sprite sprite;
    heroClass job;
    vector<int>stats;
    int currentHealth;
    vector<ability>jobAbilities;
    int team;
    sf::Vector2i Position;
    void placehero(sf::RenderWindow& window,int characterx, int charactery);
    void assignhero();
    void rangecheck(vector<sf::Vector2i> passableTiles,sf::RenderWindow& window);
};

class weapon{
public:
    vector<int>stats;

};

void hero::rangecheck(vector<sf::Vector2i> passableTile,sf::RenderWindow& window)
{
    sf::Vector2i positioncheck,positionalter;//this isn't necessary yet.
    int range=5;//this is the range.
    int invalidCounter = 0;
    for (int j=-range;j<=range;j++)//this is the initialization of a for loop
    {
        for (int i=0;i<range-abs(j);i++)//this is the initialization of a for loop
        {
            if (-passableTile[Position.x-i].x==1 and passableTile[Position.y+j].y==1)//this is an if statement to check if the spot at Y,-X is cool
            {
                traversableTiles.push_back(sf::Vector2i(Position.x-i,Position.y+j));//"Yes, you may step on this X coordinate
                //traversibletiles.push_back(Position.y+j).y;//"Yes, you may step on this Y coordinate
            }
            if (passableTile[Position.x+i].x==1 and passableTile[Position.y+j].y==1)//this is an if statement to check if the spot at Y, X is cool
            {
                traversableTiles.push_back(sf::Vector2i(Position.x+i,Position.y+j));//"Yes, you may step on this X coordinate
                //traversibletiles.push_back(Position.y+j).y;//"Yes, you may step on this Y coordinate
            }
        }
    }
    cout << traversableTiles.size() << endl;
    tile validTiles[traversableTiles.size()];//an array of "Sure, you may step here" tiles the size of the amount of tiles you can step on.
    for (int i=0;i<traversableTiles.size();i++)//this is the initialization of a for loop
    {
        //cout << traversibletilesx[i] << " , " << traversibletilesy[i] << endl;
        validTiles[i]=tiles[6];//the "Sure, you may step here" tiles have the same properties as a valid tile.
        validTiles[i].tileSprite.setPosition(traversableTiles[i].x*32,traversableTiles[i].y*32);//This is where we tell it where to go.
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
void ability::useAbility(hero user, hero target){
    if(ability::isAttack) ability::abilityAttack(user, target);
    if(ability::isHeal) ability::abilityHeal(user, target);
    if(ability::isBuff) ability::abilityBuff(user, target);
}
void ability::abilityAttack(hero user, hero target){
    if(user.team != target.team) target.currentHealth -= ability::abilityPotency * ability::abilityModifier;
}
void ability::abilityHeal(hero user, hero target){
    if(user.team == target.team) target.currentHealth += ability::abilityPotency * ability::abilityModifier;
}
void ability::abilityBuff(hero user, hero target){
    target.stats[ability::statAffected]+= ability::abilityPotency * ability::abilityModifier;
}
#endif // HEROFUNCTIONS_H_INCLUDED
