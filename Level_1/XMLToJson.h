#ifndef XMLTOJSON_H
#define XMLTOJSON_H

#include <iostream>
#include <string>
#include "Helpers.h"

using namespace std;

class XMLToJson {
private:
    Helpers helper;
    string XMLText = "";
    string jsonText = "";

    // Helper function for indentation
    string HandleIndentation(int level);

    // Convert XML to JSON
    string convertToJson();

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
