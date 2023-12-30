#include "XMLToJson.h"


using namespace std;

XMLToJson::XMLToJson(string xmlText){
    setXMLText(helper.prepare(xmlText));
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
    vector<string> elements = helper.convertXMLToVector(this->XMLText);
    stack<char> openedBrackets;
    int mark=0;

    for(int i=0;i<elements.size();i++){
        if(elements[i].empty())
            continue;
        if((elements[i].length()>3) && (elements[i].substr(0,4) == ";<?>")){
            level--;
            output+= helper.addQuotes(elements[i].substr(4,elements[i].length()-4)) ;
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
            output+= "\n" + HandleIndentation(level) + helper.addQuotes(elements[i]) + ": {";
            mark=output.length()-1;
            openedBrackets.push('{');
        }
    }
    output+= "\n}";

    return output;
}

XMLToJson::~XMLToJson()
{
}

