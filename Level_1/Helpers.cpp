#include "Helpers.h"


// if you use this method in any incorrect xml text it will output error

string Helpers::removeUnwantedSpaces(string XMLText) {
    string output = "";
    int startOfXML = XMLText.find('<');
    output += XMLText[startOfXML];
    char previousCharacter = output[0];

    for (int i = startOfXML + 1; i < XMLText.length(); i++) {

        if (XMLText[i] == ' ' || XMLText[i] == '\n') {
            if (previousCharacter == ' ' || previousCharacter == '<' || previousCharacter == '>') {
                continue;
            }
            output += ' ';
        }else if(XMLText[i] == '<' || XMLText[i] == '>' || (XMLText[i] == '?' && i<XMLText.length()-1 && XMLText[i+1]== '>')  || (XMLText[i] == '?' && i>0 && XMLText[i-1]== '<')) {
            if (previousCharacter == ' ') {
                output = output.substr(0, output.length() - 1);
                output += XMLText[i];
            } else {
                output += XMLText[i];
            }

        } else {
            output += XMLText[i];
        }
        previousCharacter = output[output.length() - 1];
    }

    return output;
}

void Helpers::saveFile(string text,string path){
    ofstream outfile (path);
    outfile << text << endl;
    outfile.close();
}
