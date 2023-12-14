#include "prettify.h"

Prettify::Prettify() {
    prettifiedXml = "";
    isOpening_tag = true;
    indentationLevel = 0;
}

QString Prettify::prettifyXml(const QString& xmlContent){
    QString filteredContent = xmlContent.simplified();
    int index = 0;
    QString currentLine = "";
    int length = filteredContent.length();


    while (index < length) {

        //check if closing or opening tag:
        if (xmlContent[index] == '<'){

            if (xmlContent[index+1] == '/'){
                //closing
                isOpening_tag = false;

                currentLine += xmlContent[index];

            }
            else{
                //opening

                currentLine += xmlContent[index];
                }

        }
        // check for closing casess
        else if (xmlContent[index] == '>'){
            currentLine += xmlContent[index];
            //closing then closing tag
            if (xmlContent[index+2] == '<' && xmlContent[index+3] == '/' && !isOpening_tag){
                indentationLevel--;
            }
            //opening then opening
            else if (xmlContent[index+2] == '<' && xmlContent[index+3] != '/' && isOpening_tag){
                indentationLevel++;
            }
            //last line case
            else if (index+2 > length && !isOpening_tag){
                printLine(currentLine);
                currentLine = "";
            }
            //any other case
            else{
                index++;
                continue;
            }
        }

        else if (xmlContent[index] == '\n'){
            currentLine += xmlContent[index];
            printLine(currentLine);
            currentLine = "";
            isOpening_tag = true;

        }

        else {
            currentLine += xmlContent[index];
        }

        index++;
    }
    return prettifiedXml;
}

void Prettify::printLine(const QString& line) {
    if (!line.isEmpty()) {
        prettifiedXml += line;
        writeIndentation();
    }
}

void Prettify::writeIndentation() {
    for (int i = 0; i < indentationLevel; ++i) {
        prettifiedXml += "         ";
    }
}

