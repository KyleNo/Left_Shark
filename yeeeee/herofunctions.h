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
    vector<ability>jobAbilities;
    void useAbility(ability abilityUsed, hero target, hero user);
    int team;
    sf::Vector2i Position;
    void placehero(sf::RenderWindow& window,int characterx, int charactery);
    void assignhero();
    void rangecheck(vector< vector <bool> > passableTile,sf::RenderWindow& window);
};

class weapon{
public:
    vector<int>stats;

};

void hero::rangecheck(vector< vector <bool> > passableTile,sf::RenderWindow& window)
{
    range=5;
    int counter=0;
    vector<sf::Vector2i> traversableTiles;
    for (int i=-range;i<range;i++)
    {
        for (int j=-(range-abs(i));j<range-abs(i);j++)
        {
            if(passableTile[Position.x+j][Position.y+i]==true)
            {
                traversableTiles.push_back(sf::Vector2i(Position.x-j,Position.y+i));
                cout << "Not nice\n";
                cout << traversableTiles[0].x << traversableTiles[0].y << endl;
            }
            counter++;
        }
    }
    cout << counter << endl;
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
void hero::useAbility(ability abilityUsed, hero target, hero user){
    if(abilityUsed.isAttack) abilityUsed.abilityAttack(hero , target);
    if(abilityUsed.isHeal) abilityUsed.abilityHeal(hero, target);
    if(abilityUsed.isBuff) abilityUsed.abilityBuff(hero, target);
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
