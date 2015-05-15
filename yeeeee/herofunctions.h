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

vector<sf::Vector2i> tilesyougottacheck(sf::Vector2i tile)
{
    vector<sf::Vector2i> tiles;
    tiles.push_back(sf::Vector2i(tile.x+1,tile.y));
    tiles.push_back(sf::Vector2i(tile.x-1,tile.y));
    tiles.push_back(sf::Vector2i(tile.x,tile.y+1));
    tiles.push_back(sf::Vector2i(tile.x,tile.y-1));
    return tiles;
}

sf::Vector2i adjacencyCheck(int orientation,sf::Vector2i tileChecking, vector< vector <bool> > passableTiles, vector<sf::Vector2i> tilesChecked)
{
    switch (orientation)
    {
    case 0://check up
        if (passableTiles[tileChecking.x][tileChecking.y-1]==0)
        {
            for (int i=0;i<tilesChecked.size();i++)
            {
                if (tilesChecked[i]!=sf::Vector2i(tileChecking.x,tileChecking.y-1))
                {
                    cout << "adjacency check\n";
                    return sf::Vector2i(tileChecking.x,tileChecking.y-1);
                }
            }
        }
        else
        {
            return sf::Vector2i(-1,-1);
        }
    case 1://check right
        if (passableTiles[tileChecking.x+1][tileChecking.y]==0)
        {
            for (int i=0;i<tilesChecked.size();i++)
            {
                if (tilesChecked[i]!=sf::Vector2i(tileChecking.x+1,tileChecking.y))
                {
                    cout << "adjacency check\n";
                    return sf::Vector2i(tileChecking.x+1,tileChecking.y);
                }
            }
        }
        else
        {
            return sf::Vector2i(-1,-1);
        }
    case 2://check down
        if (passableTiles[tileChecking.x][tileChecking.y+1]==0)
        {
            for (int i=0;i<tilesChecked.size();i++)
            {
                if (tilesChecked[i]!=sf::Vector2i(tileChecking.x,tileChecking.y+1))
                {
                    cout << "adjacency check\n";
                    return sf::Vector2i(tileChecking.x,tileChecking.y+1);
                }
            }
        }
        else
        {
            return sf::Vector2i(-1,-1);
        }
    case 3://check left
        if (passableTiles[tileChecking.x-32][tileChecking.y]==0)
        {
            for (int i=0;i<tilesChecked.size();i++)
            {
                if (tilesChecked[i]!=sf::Vector2i(tileChecking.x-32,tileChecking.y))
                {
                    cout << "adjacency check\n";
                    return sf::Vector2i(tileChecking.x-32,tileChecking.y);
                }
            }
        }
        else
        {
            return sf::Vector2i(-1,-1);
        }
    }
}

vector<sf::Vector2i> hero::rangecheck(vector< vector <bool> > passableTile,sf::RenderWindow& window)
{
    range=5;
    sf::Vector2i tileChecking;
    vector<sf::Vector2i> tilesToCheck, tilesCheckedLast,tilesChecked;
    vector<sf::Vector2i> goodTiles;
    tilesToCheck.push_back(Position);
    for (int z=0;z<range;z++)
    {
        cout << "Zloop\n";
        for (int i=0;i<tilesToCheck.size();i++)
        {
            cout << "Iloop\n";
            tilesCheckedLast=tilesToCheck;
            tilesToCheck.resize(tilesCheckedLast.size());
            tilesToCheck=tilesyougottacheck(tilesCheckedLast[i]);
            for (int j=0;j<4;j++)
            {
                cout << "Jloop\n";
                if (adjacencyCheck(j,tilesToCheck[i],passableTile,tilesChecked).x!=-1);
                {
                    cout << "tile To Check: ";
                    cout << tilesToCheck[i].x << "," << tilesToCheck[i].y << endl;
                    tileChecking=adjacencyCheck(j,tilesToCheck[i],passableTile,tilesChecked);
                    goodTiles.push_back(tileChecking);
                }
            }
            for (int j=0;j<tilesCheckedLast.size();j++)
            {
                tilesChecked.push_back(tilesCheckedLast[i]);
                cout << "Tileschecking loop\n";
            }
            cout << "endofIloop\n";
        }
        cout << "endofZloop\n";
    }
    tilesToCheck.clear();
    return goodTiles;
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
