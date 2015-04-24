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
    tile rangecheck(vector< vector <bool> > passableTile,sf::RenderWindow& window, int x, int y);
};

class weapon{
public:
    vector<int>stats;

};



tile hero::rangecheck(vector< vector <bool> > passableTile,sf::RenderWindow& window,int x,int y)
{
    range=5;
    tile validtile;
    sf::Vector2i traversableTile;
    if(passableTile[Position.x+x][Position.y+y]==true)
    {
        traversableTile=(sf::Vector2i(Position.x-x,Position.y+y));
    }
    validtile=(tiles[7]);
    validtile=tiles[7];
    validtile.tileSprite.setPosition((Position.x+x)*32,(Position.y+y)*32);
    return validtile;
}



void hero::assignhero(){
    if(!texture.loadFromFile("resources/images/TestChar.png")){
        //error...
    }
    sprite.setTexture(texture);
}
void hero::placehero(sf::RenderWindow& window, int characterx, int charactery){
    sprite.setPosition(charactery,characterx);
    Position.x=(sprite.getPosition().x)/32;
    Position.y=(sprite.getPosition().y)/32;
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
