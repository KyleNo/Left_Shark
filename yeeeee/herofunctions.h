#ifndef HEROFUNCTIONS_H_INCLUDED
#define HEROFUNCTIONS_H_INCLUDED
#include "abilities.h"
#include <sstream>
class hero{
public:
    bool moved;
    bool action;

    int team;
    int attackRange;
    int range;
    int heroId;
    int maxhealth;
    int currentHealth;
    int experience;
    int agility;
    int attack;


    string jobname;
    string name;
    vector<ability>heroAbilities;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2i Position;
    weapon equippedWeapon;
    heroClass job;

    hero useAbility(ability abilityUsed, hero target);
    void placehero(sf::RenderWindow& window, int characterx, int charactery, bool initialPlacement, sf::Vector2f tileTo);
    void assignhero(const char* names);
    vector<sf::Vector2i> rangecheck(vector< vector <bool> > passableTile,sf::RenderWindow& window, bool attacking);
};

sf::Vector2i adjacencyCheck(int orientation,sf::Vector2i tileChecking, vector< vector <bool> > passableTiles, vector<sf::Vector2i> tilesChecked, bool attacking)
{
    sf::Vector2i tileToCheck;
    if (tileChecking.x<0 or tileChecking.y<0)
    {
        return sf::Vector2i(-1,-1);
    }
    if (orientation==0 and passableTiles[tileChecking.x][tileChecking.y-1]==false or orientation==0 and attacking)
    {
        tileToCheck=sf::Vector2i(tileChecking.x,tileChecking.y-1);
    }
    else if (orientation == 1 and passableTiles[tileChecking.x+1][tileChecking.y]==false or orientation==1 and attacking)
    {
        tileToCheck=sf::Vector2i(tileChecking.x+1,tileChecking.y);
    }
    else if (orientation == 2 and passableTiles[tileChecking.x][tileChecking.y+1]==false or orientation==2 and attacking)
    {
        tileToCheck=sf::Vector2i(tileChecking.x,tileChecking.y+1);
    }
    else if (orientation== 3 and passableTiles[tileChecking.x-1][tileChecking.y]==false or orientation==3 and attacking)
    {
        tileToCheck=sf::Vector2i(tileChecking.x-1,tileChecking.y);
    }
    if (attacking==false)
    {
        for (int i=0;i<tilesChecked.size();i++)
        {
            if (passableTiles[tileToCheck.x][tileToCheck.y] or tilesChecked[i]==tileToCheck )
            {
                return sf::Vector2i(-1,-1);
            }
        }
    }
    return tileToCheck;
}


vector<sf::Vector2i> hero::rangecheck(vector< vector <bool> > passableTile,sf::RenderWindow& window, bool attacking)
{
    attackRange=2;
    int checkRange;
    if (attacking)
    {
        checkRange=attackRange;
    }
    else
    {
        checkRange=range;
    }
    vector<sf::Vector2i> tilesToCheck,tilesChecked,tilesLastChecked;
    sf::Vector2i tileChecking;
    Position.x=sprite.getPosition().x/32;
    Position.y=sprite.getPosition().y/32;
    tilesToCheck.push_back(Position);
    for (int i=0;i<checkRange;i++)
    {
        for (int j=0;j<tilesToCheck.size();j++)
        {
            for (int k=0;k<4;k++)
            {
                tileChecking=adjacencyCheck(k,tilesToCheck[j],passableTile,tilesChecked, attacking);
                if (tileChecking.x!=-1)
                {
                    tilesLastChecked.push_back(tileChecking);
                    tilesChecked.push_back(tileChecking);
                }
            }
        }
        tilesToCheck.clear();
        for (int j=0;j<tilesLastChecked.size();j++)
        {
            tilesToCheck.push_back(tilesLastChecked[j]);
        }
        tilesLastChecked.clear();
    }
    cout << tilesChecked.size() << endl;
    return tilesChecked;
}

void hero::assignhero(const char* names)
{
    tinyxml2::XMLDocument doc;

    doc.LoadFile("resources/Characters.xml");
    tinyxml2::XMLNode* herose = doc.FirstChildElement("heroes");

    tinyxml2::XMLElement* nameElement = herose->FirstChildElement( names )->FirstChildElement("name");

    tinyxml2::XMLElement* healthElement = nameElement->NextSiblingElement("health");

    tinyxml2::XMLElement* experienceElement = healthElement->NextSiblingElement("experience");
    tinyxml2::XMLElement* attackElement = experienceElement->NextSiblingElement("attack");

    tinyxml2::XMLElement* agilityElement = attackElement->NextSiblingElement("agility");
    tinyxml2::XMLElement* rangeElement = agilityElement->NextSiblingElement("range");
    tinyxml2::XMLElement* texturelocationElement = rangeElement->NextSiblingElement("texturelocation");

    name = nameElement->GetText();

    stringstream convert[5];
    convert[0] << healthElement->GetText();
    convert[0] >> currentHealth;
    convert[1] << experienceElement->GetText();
    convert[1] >> experience;
    convert[2] << attackElement->GetText();
    convert[2] >> attack;
    convert[3] << agilityElement->GetText();
    convert[3] >> agility;
    convert[4] << rangeElement->GetText();
    convert[4] >> range;
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
            //target.stats[abilityUsed.statAffected]+= abilityUsed.abilityPotency * abilityUsed.abilityModifier;
        }
        return target;
}

#endif // HEROFUNCTIONS_H_INCLUDED
