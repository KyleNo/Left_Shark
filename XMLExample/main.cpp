#include <iostream>
#include "tinyxml2.h"
// include this header; thats all you need
#include <sstream>
// this is for converting strings or chars into usable numbers
using namespace std;

int main()
{
    const char* names[4] = {"David", "Kyle", "Jordan", "Nathaniel"};
    //just your typical array of constant character pointers.
    //this could be passed into a function instead if you wanted to.

    int range;
    int agility;
    //some integers to mess with

    const char* name;
    //a place to save the text from the name

    tinyxml2::XMLDocument charAtrib;
    // make a new document for xml

    charAtrib.LoadFile("Characters.xml");
    //this loads the actual text info from the xml file

    tinyxml2::XMLNode* herose = charAtrib.FirstChildElement("heroes");
    //this is a node

    for(int i=0; i<4; i++){
        tinyxml2::XMLElement* nameElement = herose->FirstChildElement(names[i])->FirstChildElement("name");
        tinyxml2::XMLElement* agilityElement = nameElement->NextSiblingElement("agility");
        tinyxml2::XMLElement* rangeElement = herose->FirstChildElement(names[i])->FirstChildElement("range");

        name = nameElement->GetText();

        stringstream convert[2];
        convert[0] << rangeElement->GetText();
        convert[0] >> range;
        convert[1] << agilityElement->GetText();
        convert[1] >> agility;

        cout << name << "\t"<<range << "\t" << agility << "\t" << range * agility << endl;
    }
}
