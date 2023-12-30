#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <stack>


using namespace std;

class Helpers {
private:
    string convertXML(const string& input);

public:
    // Convert XML to a Vector of elements
    vector<string> convertXMLToVector(string XMLText);
    // if you use this method in any incorrect xml text it will output error
    string removeUnwantedSpaces(string XMLText);

    string prepare(string XMLText);

    string addQuotes(string element);

    void saveFile(string text, string path);
};

