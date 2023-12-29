// Tree.h
#pragma once
#include <string>
#include <fstream>
#include "vector"

using namespace std;

class Helpers {
private:
    string convertXML(const string& input);

public:
    string removeUnwantedSpaces(string XMLText);
    string prepare(string XMLText);
    void saveFile(string text,string path);
};
