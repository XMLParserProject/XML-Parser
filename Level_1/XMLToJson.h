#ifndef XMLTOJSON_H
#define XMLTOJSON_H

#include <iostream>
#include <string>
#include <stack>
#include "Helpers.h"
#include "Tree.h"

// Using the std namespace
using namespace std;

class XMLToJson {
private:
    string XMLText = "";
    string jsonText = "";

    // Helper function for indentation
    string HandleIndentation(int level);

    // Convert XML to JSON
    string convertToJson();

    // Convert XML to a tree structure
    Tree convertToTree();

    // Convert the tree structure to a vector of elements
    vector<string> ToVector(string XMLTree);

    // Add double quotes to an element
    string addQuotes(string element);

public:
    // Constructor
    XMLToJson(string xmlText);

    // Set XML text
    void setXMLText(string xmlText);

    // Get JSON text
    string getJSONText();

    // Destructor
    ~XMLToJson();
};

#endif  // XMLTOJSON_H
