
// Tree.h
#pragma once

#include <string>
#include <fstream>

using namespace std;

class Helpers {
private:

public:
    string removeUnwantedSpaces(string XMLText);
    void saveFile(string text,string path);
};
