#ifndef HEROFUNCTIONS_H_INCLUDED
#define HEROFUNCTIONS_H_INCLUDED
#include "abilities.h"
class hero{
public:
    bool moved;
    bool action;
    int team;
    int range;
    int heroId;
    int currentHealth;
    vector<int>stats;
    vector<ability>heroAbilities;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2i Position;
    weapon equippedWeapon;
    heroClass job;
 //   ability jobAbility = job.jobAbility;
//    ability basicAttack = equippedWeapon.weaponAttack;

    hero useAbility(ability abilityUsed, hero target);
    void placehero(sf::RenderWindow& window, int characterx, int charactery, bool initialPlacement, sf::Vector2f tileTo);
    void assignhero();
    vector<sf::Vector2i> rangecheck(vector< vector <bool> > passableTile,sf::RenderWindow& window);
};

sf::Vector2i adjacencyCheck(int orientation,sf::Vector2i tileChecking, vector< vector <bool> > passableTiles, vector<sf::Vector2i> tilesChecked)
{
    sf::Vector2i tileToCheck;
    if (orientation==0 and passableTiles[tileChecking.x][tileChecking.y-1]==false)
    {
        tileToCheck=sf::Vector2i(tileChecking.x,tileChecking.y-1);
    }
    else if (orientation == 1 and passableTiles[tileChecking.x+1][tileChecking.y]==false)
    {
        tileToCheck=sf::Vector2i(tileChecking.x+1,tileChecking.y);
    }
    else if (orientation == 2 and passableTiles[tileChecking.x][tileChecking.y+1]==false)
    {
        tileToCheck=sf::Vector2i(tileChecking.x,tileChecking.y+1);
    }
    else if (orientation== 3 and passableTiles[tileChecking.x-1][tileChecking.y]==false)
    {
        tileToCheck=sf::Vector2i(tileChecking.x-1,tileChecking.y);
    }
    for (int i=0;i<tilesChecked.size();i++)
    {
        if (passableTiles[tileToCheck.x][tileToCheck.y] or tilesChecked[i]==tileToCheck)
        {
            return sf::Vector2i(-1,-1);
        }
    }
    return tileToCheck;
}


vector<sf::Vector2i> hero::rangecheck(vector< vector <bool> > passableTile,sf::RenderWindow& window)
{
    range=5;
    vector<sf::Vector2i> tilesToCheck,tilesChecked,tilesLastChecked;
    sf::Vector2i tileChecking;
    Position.x=sprite.getPosition().x/32;
    Position.y=sprite.getPosition().y/32;
    tilesToCheck.push_back(Position);
    for (int i=0;i<range;i++)
    {
        for (int j=0;j<tilesToCheck.size();j++)
        {
            for (int k=0;k<4;k++)
            {
                tileChecking=adjacencyCheck(k,tilesToCheck[j],passableTile,tilesChecked);
                if (tileChecking.x!=-1)
                {
                    tilesLastChecked.push_back(tileChecking);
                }
            }
        }
        tilesToCheck.clear();
        for (int j=0;j<tilesLastChecked.size();j++)
        {
            tilesToCheck.push_back(tilesLastChecked[j]);
            tilesChecked.push_back(tilesLastChecked[j]);
        }
        tilesLastChecked.clear();
    }
    for (int i=0;i<tilesChecked.size();i++)
    {
        cout << tilesChecked[i].x << "," << tilesChecked[i].y << endl;
    }
    return tilesChecked;
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
        sprite.setPosition(tileTo.x, tileTo.y);
        moved=true;
    }
    else
    {
        sprite.setPosition(charactery, characterx);
    }
    Position.x=(sprite.getPosition().x)/32;
    Position.y=(sprite.getPosition().y)/32;
}
hero hero::useAbility(ability abilityUsed, hero target){
    action = true;
        if(abilityUsed.isAttack){
            target.currentHealth=target.currentHealth - abilityUsed.abilityPotency * abilityUsed.abilityModifier;
        }
        else if(abilityUsed.isHeal){
            if(team == target.team) target.currentHealth += abilityUsed.abilityPotency * abilityUsed.abilityModifier;
        }
        else if(abilityUsed.isBuff){
            target.stats[abilityUsed.statAffected]+= abilityUsed.abilityPotency * abilityUsed.abilityModifier;
        }
        return target;
}

#endif // HEROFUNCTIONS_H_INCLUDED
