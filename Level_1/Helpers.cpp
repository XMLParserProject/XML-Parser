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

string Helpers::convertXML(const string& input) {
		int attributePos = input.find(" ");
		if (attributePos == -1) {
			return "Invalid input format";
		}
		string tagName = input.substr(1, attributePos - 1);
		vector<pair<string, string>> attributes;
		while (attributePos != -1) {
			int attributeNameStart = attributePos + 1;
			int attributeNameEnd = input.find("=", attributeNameStart);
			int attributeValueStart = input.find("\"", attributeNameEnd) + 1;
			int attributeValueEnd = input.find("\"", attributeValueStart);
			string attributeName = input.substr(attributeNameStart, attributeNameEnd - attributeNameStart);
			string attributeValue = input.substr(attributeValueStart, attributeValueEnd - attributeValueStart);
			attributes.push_back({attributeName, attributeValue});
			attributePos = input.find(" ", attributeValueEnd);
		}
		string result = "<" + tagName + ">";
		for (const auto& attribute : attributes) {
			result += "<_" + attribute.first + ">" + attribute.second + "</_" + attribute.first + ">";
		}
        if(input[input.length()-2] == '/')
		    result += "</" + tagName + ">";
		return result;
	}
string Helpers::prepare(string XMLText){
    string output="";
    XMLText=this->removeUnwantedSpaces(XMLText);
    int firstPointer=0;
    int secondPointer=0;
    bool betweenBrackets=false;
    while(secondPointer < XMLText.length()){
        if(XMLText[secondPointer] == '<'){
            firstPointer=secondPointer;
            betweenBrackets=true;
        }else if(!betweenBrackets){
            output+=XMLText[secondPointer];
        }else if(XMLText[secondPointer] == '>' && betweenBrackets){
            string tag = XMLText.substr(firstPointer,secondPointer-firstPointer+1);
            if(tag.find(" ") != -1){
                    output += this->convertXML(tag);
            }else{
                output += tag;
            }
        betweenBrackets=false;
        firstPointer=secondPointer+1;
        }
                secondPointer++;
    }
        return output;
    }
