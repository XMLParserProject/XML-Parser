#include "Helpers.h"



string Helpers::removeUnwantedSpaces(string XMLText) {
    string output = "";
    int startOfXML = XMLText.find('<');
    output += XMLText[startOfXML];
    char previousCharacter = output[0];

    for (int i = startOfXML + 1; i < XMLText.length(); i++) {

        if (XMLText[i] == ' ' || XMLText[i] == '\n') {
            if (previousCharacter == ' ' || previousCharacter == '<' || previousCharacter == '>' || previousCharacter == '/' || previousCharacter == '?') {
                continue;
            }
            output += ' ';
        }else if(XMLText[i] == '<' || XMLText[i] == '>' || (XMLText[i] == '?' && i<XMLText.length()-1 && XMLText[i+1]== '>') || (XMLText[i] == '/' && i<XMLText.length()-1 && XMLText[i+1]== '>')) {
            if (previousCharacter == ' ') {
                output[output.length() - 1] = XMLText[i];
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
        return output;
    }
vector<string> Helpers::convertXMLToVector(string XMLText){
    vector<string> xmlVector;
    int firstPointer=0;
    int secondPointer=0;
    string lastvalue="";
    char currentCharacter;
    bool betweenBrackets=false;
    stack<string> openedtages;

        while(secondPointer < XMLText.length()){
        currentCharacter = XMLText[secondPointer];
        if(currentCharacter == '<'){
            secondPointer++;
            firstPointer=secondPointer;
            betweenBrackets=true;
        }else if(currentCharacter == '>' && betweenBrackets){
            if(XMLText[firstPointer] == '/'){
                string closedtag = XMLText.substr(firstPointer+1,secondPointer - firstPointer - 1);
                if(closedtag == openedtages.top()){
                    if(lastvalue.length()>0){
                        xmlVector.push_back(";<?>"+lastvalue);
                        lastvalue="";
                    }
                    else
                        xmlVector.push_back("/"+closedtag);
                }
                openedtages.pop();
            }else{
                string openedtag=XMLText.substr(firstPointer,secondPointer - firstPointer);
                if(XMLText[secondPointer-1] != '/'){
                if(openedtag.find(' '))
                    openedtag = openedtag.substr(0,openedtag.find(' '));

                if(openedtag != "xml" && openedtag != "?xml"){                      
                    xmlVector.push_back(openedtag);
                openedtages.push(openedtag);
                } 
                }
            }
            betweenBrackets=false;
            firstPointer=secondPointer+1;
        }else{
            if(!betweenBrackets && XMLText[secondPointer+1] == '<')
                lastvalue = XMLText.substr(firstPointer,secondPointer - firstPointer + 1);
        }
        secondPointer++;
    }

    return xmlVector;

}
string Helpers::addQuotes(string element){
    return "\"" + element + "\"";
}


void Helpers::saveFile(string text,string path){
    ofstream outfile (path);
    outfile << text << endl;
    outfile.close();
}
