#include "Helpers.h"

// This method removes unwanted spaces and consolidates formatting in an XML string.
// It ensures that spaces are appropriately placed around XML tags and characters.

string Helpers::removeUnwantedSpaces(string XMLText) {
    // Initialize an empty string to store the modified XML text
    string output = "";

    // Check if the input XML text contains the '<' character
    if (XMLText.find('<') != -1) {
        // Find the position of the first '<' character in the input XML text
        int startOfXML = XMLText.find('<');

        // Append the first '<' character to the output string
        output += XMLText[startOfXML];

        // Initialize a variable to keep track of the previous character
        char previousCharacter = output[0];

        // Iterate through the characters in the input XML text starting from the position of the first '<' character
        for (int i = startOfXML + 1; i < XMLText.length(); i++) {
            // Check if the current character is a space or a newline
            if (XMLText[i] == ' ' || XMLText[i] == '\n') {
                // Check if the previous character is a space, '<', '>', '/', or '?'
                if (previousCharacter == ' ' || previousCharacter == '<' || previousCharacter == '>' || previousCharacter == '/' || previousCharacter == '?') {
                    // If true, skip adding the space or newline to the output string
                    continue;
                }
                // If false, add a space to the output string
                output += ' ';
            } else if (XMLText[i] == '<' || XMLText[i] == '>' || (XMLText[i] == '?' && i < XMLText.length() - 1 && XMLText[i + 1] == '>') || (XMLText[i] == '/' && i < XMLText.length() - 1 && XMLText[i + 1] == '>')) {
                // Check if the current character is '<', '>', '?', or '/' and if the previous character is a space
                if (previousCharacter == ' ') {
                    // If true, update the last character in the output string to be the current character
                    output[output.length() - 1] = XMLText[i];
                } else {
                    // If false, add the current character to the output string
                    output += XMLText[i];
                }
            } else {
                // If the current character is not a space or one of the specified characters, add it to the output string
                output += XMLText[i];
            }

            // Update the previous character to be the last character in the output string
            previousCharacter = output[output.length() - 1];
        }
    }

    // Return the modified XML text
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
