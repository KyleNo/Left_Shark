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
    //this is a node, which is a data point on a larger network
    //This gives us a point to refer to within the xml;

    for(int i=0; i<4; i++){
        tinyxml2::XMLElement* nameElement = herose->FirstChildElement(names[i])->FirstChildElement("name");
        //The node <heroes> contains 4 child elements referred to in line 10
        //"->" means that we are using the node on the left of the arrow to locate another node/element;
        //In this case, we use the herose node which points to the <heroes> node
        //  and check for a child element with the name represented by the const char pointer array
        //  the first time that it goes through the for loop it searches for a child element "David"
        //  and the first child element of <David> that is named "name"


        tinyxml2::XMLElement* agilityElement = nameElement->NextSiblingElement("agility");
        //From the element we just made, we can find the next sibling with the name "agility"

        tinyxml2::XMLElement* rangeElement = herose->FirstChildElement(names[i])->FirstChildElement("range");
        //Alternatively, we can just go straight from the herose node

        name = nameElement->GetText();
        //The elements are just pointers, we need to access the text part

        stringstream convert[2];
        convert[0] << rangeElement->GetText();
        convert[0] >> range;
        convert[1] << agilityElement->GetText();
        convert[1] >> agility;
        //Just use this to make numbers usable in calculation

        cout << name << "\t"<<range << "\t" << agility << "\t" << range * agility << endl;
    }
}
