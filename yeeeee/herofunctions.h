#ifndef HEROFUNCTIONS_H_INCLUDED
#define HEROFUNCTIONS_H_INCLUDED
#include "abilities.h"
class hero{
public:
    int range;
    sf::Texture texture;
    sf::Sprite sprite;
    heroClass job;
    vector<int>stats;
    int currentHealth;
    vector<ability>heroAbilities;
    void useAbility(ability abilityUsed, hero target, hero user);
    int team;
    sf::Vector2i Position;
    void placehero(sf::RenderWindow& window, int characterx, int charactery, bool initialPlacement, sf::Vector2f tileTo);
    void assignhero();
    tile rangecheck(vector< vector <bool> > passableTile,sf::RenderWindow& window, int x, int y);
};

tile hero::rangecheck(vector< vector <bool> > passableTile,sf::RenderWindow& window,int x,int y)
{
    range=5;
    tile validtile;
    sf::Vector2i traversableTile;
    validtile=(tiles[7]);
    validtile=tiles[7];
    if(passableTile[Position.x-x][Position.y+y]==false)
    {
        //traversableTile=(sf::Vector2i(Position.x-x,Position.y+y));
        validtile.tileSprite.setPosition((Position.x-x)*32,(Position.y+y)*32);
    }
    return validtile;
}



void hero::assignhero(){
    if(!texture.loadFromFile("resources/images/TestChar.png")){
        //error...
    }
    sprite.setTexture(texture);
}
void hero::placehero(sf::RenderWindow& window, int characterx, int charactery, bool initialPlacement, sf::Vector2f tileTo)
{
    if (initialPlacement==false)
    {
        sprite.move(characterx, charactery);
    }
    else
    {
        sprite.setPosition(charactery, characterx);
    }
    Position.x=(sprite.getPosition().x)/32;
    Position.y=(sprite.getPosition().y)/32;
}
void hero::useAbility(ability abilityUsed, hero target, hero user){
    if(abilityUsed.isAttack) abilityUsed.abilityAttack(user , target);
    else{
        return;
        cout << "whelp";
    }
    if(abilityUsed.isHeal) abilityUsed.abilityHeal(user, target); else return;
    if(abilityUsed.isBuff) abilityUsed.abilityBuff(user, target);else return;
}
void ability::abilityAttack(hero user, hero target){
    target.currentHealth -= ability::abilityPotency * ability::abilityModifier;
}
void ability::abilityHeal(hero user, hero target){
    if(user.team == target.team) target.currentHealth += ability::abilityPotency * ability::abilityModifier;
}
void ability::abilityBuff(hero user, hero target){
    target.stats[ability::statAffected]+= ability::abilityPotency * ability::abilityModifier;
}

#endif // HEROFUNCTIONS_H_INCLUDED
