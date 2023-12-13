#include <string>
#include "Helpers.h"
using namespace std;

string  Helpers::removeUnwantedSpaces(string XMLText){
    string output="";
    int startOfXML=XMLText.find('<');
    output+=XMLText[startOfXML];
    char previousCharacter=output[0];

    for(int i=startOfXML+1;i<XMLText.length();i++){

        if(XMLText[i] == ' ' || XMLText[i] == '\n'){
            if(previousCharacter == ' ' || previousCharacter == '<' || previousCharacter == '>'){
                continue;
            }
            output+=' ';
        }else if(XMLText[i] == '<' || XMLText[i] == '>'){
            if(previousCharacter == ' '){
                output=output.substr(0,output.length()-1);
                output+=XMLText[i];
            }else{
                output+=XMLText[i];
            }

        }else{
            output+=XMLText[i];
        }
        previousCharacter = output[output.length()-1];
    }

    return output;  
} 
