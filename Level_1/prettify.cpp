#include "prettify.h"

Prettify::Prettify() {
    prettifiedXml = "";
    isOpening_tag = true;
    indentationLevel = 0;
}

QString Prettify::prettifyXml(const QString& xmlContent){
    QString filtered_xmlContent = filterConsecutiveNewlines(xmlContent.trimmed());
    int index = 0;
    QString currentLine = "";
    int length = filtered_xmlContent.length();


    while (index < length) {

        //check if closing or opening tag:
        if (filtered_xmlContent[index] == '<'){

            if (filtered_xmlContent[index+1] == '/'){
                //closing
                isOpening_tag = false;

                currentLine += filtered_xmlContent[index];

            }
            else{
                //opening

                currentLine += filtered_xmlContent[index];
                }

        }
        // check for closing casess
        else if (filtered_xmlContent[index] == '>'){
            currentLine += filtered_xmlContent[index];
                       
            //last line case
            if (index+2 > length && !isOpening_tag){
                printLine(currentLine);
                currentLine = "";
            }
            
            //closing then closing tag
            else if (filtered_xmlContent[index+2] == '<' && filtered_xmlContent[index+3] == '/' && !isOpening_tag){
                indentationLevel--;
            }
            //opening then opening
            else if (filtered_xmlContent[index+2] == '<' && filtered_xmlContent[index+3] != '/' && isOpening_tag){
                indentationLevel++;
            }
            //any other case
            else{
                index++;
                continue;
            }
        }

        else if (filtered_xmlContent[index] == '\n'){
            currentLine += filtered_xmlContent[index];
            printLine(currentLine);
            currentLine = "";
            isOpening_tag = true;

        }

        else {
            currentLine += filtered_xmlContent[index];
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

QString Prettify::filterConsecutiveNewlines(QString content) {
    return content.replace(QRegularExpression("\\n+"), "\n");
}

