#include "correcterrors.h"

CorrectErrors::CorrectErrors() {}




QString CorrectErrors::correct_errors(const QString& xmlcontent){
    QStack<QString> tagStack;
    QStack<QString> unclosedtags;
    XMLParser xml_Parser;
    QString correctedXmlContent;
    int length = xmlcontent.length();
    xml_Parser.setXMLContent(xmlcontent);
    if (xml_Parser.checkConsistency()) {
        correctedXmlContent = "XML has no errors";
    } else {
        bool consistent = true;
        int index = 0;

        while (index < length) {
            if (xmlcontent[index] == '<') {
                bool isStartTag = true;
                if (index + 1 < length && xmlcontent[index + 1] == '/') {
                    isStartTag = false;
                }

                int startTagName = index + (isStartTag ? 1 : 2);
                int endTagName = xmlcontent.indexOf('>', startTagName);

                if (endTagName == -1) {
                    // Handle the case where the closing angle bracket is missing
                    consistent = false;
                    break;
                }

                QString tagName = xmlcontent.mid(startTagName, endTagName - startTagName).trimmed();

                if (isStartTag) {
                    tagStack.push(tagName);
                    correctedXmlContent += "<" + tagName + ">";
                } else {
                    if (tagStack.isEmpty() || tagStack.top() != tagName) {
                        // Handle mismatched closing tag
                        unclosedtags.push(tagStack.top());
                        tagStack.pop();
                        //not missing tag
                        if(tagName!=tagStack.top()){
                            tagStack.push(unclosedtags.top());
                            unclosedtags.pop();
                            consistent = false;
                            correctedXmlContent += "</" + tagStack.top() + ">";
                            tagStack.pop();
                        }else{//missing closing tag
                            correctedXmlContent += "</" + tagStack.top() + ">";
                        }

                    } else {
                        correctedXmlContent += "</" + tagStack.top() + ">";
                        tagStack.pop();
                    }
                }

                index = endTagName + 1;
            } else {
                correctedXmlContent += xmlcontent[index];
                index++;
            }
        }
        if(!unclosedtags.isEmpty()){
            // Loop again on the correctedXmlContent to locate the location of the unclosed tag and add it
            for (const QString& unclosedTag : unclosedtags) {
                int unclosedTagIndex = correctedXmlContent.indexOf("<" + unclosedTag);

                if (unclosedTagIndex != -1) {
                    // Find the position to insert the missing closing tag
                    int insertionIndex = correctedXmlContent.indexOf(">", unclosedTagIndex);

                    if (insertionIndex != -1) {
                        // Find the next opening tag in the file
                        int nextOpeningTagIndex = correctedXmlContent.indexOf("<", unclosedTagIndex + 1);

                        if (nextOpeningTagIndex != -1) {
                            // Compare the tag name with the name in the unclosedtags stack
                            QString tagName = correctedXmlContent.mid(unclosedTagIndex + 1, insertionIndex - unclosedTagIndex - 1).trimmed();

                            if (tagName == unclosedTag) {
                                // Insert the missing closing tag just before the next opening tag
                                correctedXmlContent.insert((nextOpeningTagIndex),"</" + unclosedTag + ">");
                            } else {
                                // Handle the case where the tag name doesn't match
                                qDebug() << "Error: Tag name mismatch for unclosed tag: " << unclosedTag;
                            }
                        } else {
                            // If no next opening tag is found, insert at the end of the content
                            correctedXmlContent += "</" + unclosedTag + ">";
                        }
                    } else {
                        qDebug() << "Error locating insertion index for unclosed tag: " << unclosedTag;
                    }
                } else {
                    qDebug() << "Error locating unclosed tag: " << unclosedTag;
                }
            }
        }
        if (!consistent) {
            // Handle consistency errors if needed
            qDebug() << "XML consistency check failed";
        }
    }
    return correctedXmlContent;
}
