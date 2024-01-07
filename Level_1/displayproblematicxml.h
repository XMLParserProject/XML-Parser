#ifndef DISPLAYPROBLEMATICXML_H
#define DISPLAYPROBLEMATICXML_H
#include "string"
#include <vector>
#include "stack"
using namespace std;


struct err_data
{
    string err_type;
    int err_loc;
};


vector <err_data> detectError(vector<string> xmlVectorFile);
string getClosedTag(string t);
string getOpenTag(string t);
bool error_detector(string openTag , string closedTag , stack <string>& tagStack , string& errorType);




#endif // DISPLAYPROBLEMATICXML_H
