#include "XMLToJson.h"


using namespace std;

XMLToJson::XMLToJson(string xmlText){
    Helpers helper;
    setXMLText(helper.removeUnwantedSpaces(xmlText));
}


string XMLToJson::HandleIndentation(int level){ // where level starts from 0
    string indentation = "";
    for(int i=0;i<level;i++){
        indentation+="     ";
    }
    return indentation;
}

void XMLToJson::setXMLText(string xmlText){
    this->XMLText = xmlText;
    this->jsonText = convertToJson();
}
string XMLToJson::getJSONText(){
     return this->jsonText;
}

string XMLToJson::convertToJson(){
    string output = "{";
    int level=0;
    vector<string> elements = ToVector(convertToTree().preOrder());
    stack<char> openedBrackets;
    int mark=0;

    for(int i=0;i<elements.size();i++){
        if(elements[i].empty())
            continue;
        if((elements[i].length()>3) && (elements[i].substr(0,4) == ";<?>")){
            level--;
            output+= addQuotes(elements[i].substr(4,elements[i].length()-4)) ;
            output[mark]= '\0';
            if(i < (elements.size()-1) && elements[i+1].length() > 0 && (elements[i+1][0] != '/')){
                output+=',';
            }
        }else if(elements[i].length() > 0 && (elements[i][0] == '/')){
            output +=  "\n" + HandleIndentation(level) + '}';
            level--;
            openedBrackets.pop();
            if(i < (elements.size()-1) && elements[i+1].length() > 0 && (elements[i+1][0] != '/')){
                output+=',';
            }
        }else{
            if(output[output.length()-1] == ',')
                level++;
            if(i>0 && ((elements[i-1].length()>3) && (elements[i-1].substr(0,4) == ";<?>") || elements[i-1][0] == '/')){
                output[mark]= '\0';
                level--;
            }
            level++;
            output+= "\n" + HandleIndentation(level) + addQuotes(elements[i]) + ": {";
            mark=output.length()-1;
            openedBrackets.push('{');
        }
    }
    output+= "\n}";

    return output;
}

Tree XMLToJson::convertToTree(){
    Tree xmlTree;
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
        }else if(currentCharacter == '>'){
            if(XMLText[firstPointer] == '/'){
                string closedtag = XMLText.substr(firstPointer+1,secondPointer - firstPointer - 1);
                if(closedtag == openedtages.top()){
                    if(lastvalue.length()>0){
                        xmlTree.insert(";<?>"+lastvalue,openedtages.top());
                        lastvalue="";
                    }
                    else
                        xmlTree.insert("/"+closedtag,openedtages.top());
                }
                openedtages.pop();
            }else{
                string openedtag=XMLText.substr(firstPointer,secondPointer - firstPointer);
                if(XMLText[secondPointer-1] != '/'){
                if(openedtag.find(' '))
                    openedtag = openedtag.substr(0,openedtag.find(' '));

                if(openedtag != "xml" && openedtag != "?xml"){                      
                if(openedtages.empty())
                    xmlTree.insert(openedtag,openedtag);
                else
                    xmlTree.insert(openedtag,openedtages.top());
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


    return xmlTree;

}
string XMLToJson::addQuotes(string element){
    return "\"" + element + "\"";
}
vector<string> XMLToJson::ToVector(string elements){
    vector<string> output;
    string element;
    int firstPointer=0;
    int secondPointer=0;
    while(secondPointer < elements.length()-2){
        secondPointer = elements.find("<>", firstPointer);
        element = elements.substr(firstPointer,secondPointer-firstPointer);
        if(element.find(' ') && element[0] != ';'){
            int i = 0;
            while(element[i] == ' ')
                i++;
            element = element.substr(i,element.length() - i);
            element = element.substr(0,element.find(' '));
        }
        output.push_back(element);
        firstPointer = secondPointer + 2;
    }   
    return output;
}


XMLToJson::~XMLToJson()
{
}

