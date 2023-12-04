#include "xmlparser.h"

XMLParser::XMLParser() {
    // Initialization if needed
}

void XMLParser::setXMLContent(const QString& content) {
    xmlContent = content;
}
 //  WORKING
//the tag extraction is implemented using a library for debuging a problem in the code i will modify it later
bool XMLParser::checkConsistency() {
    QXmlStreamReader reader(xmlContent);
    tagStack = Stack<QString>();

    while (!reader.atEnd()) {
        if (reader.isStartElement()) {
            tagStack.push(reader.name().toString());
        } else if (reader.isEndElement()) {
            if (tagStack.empty() || tagStack.top() != reader.name().toString()) {
                return false; // Inconsistency: mismatched tags
            }
            tagStack.pop();
        }

        reader.readNext();
    }

    return tagStack.empty() && !reader.hasError();
}

/*
bool XMLParser::checkConsistency() {
    // Reset the stack
    tagStack = Stack<QString>();

    int i = 0;
    while (i < xmlContent.size()) {
        // Extract the current tag
        QString currentTag;
        while (i < xmlContent.size() && xmlContent[i] != '<' && xmlContent[i] != '>') {
            currentTag += xmlContent[i];
            ++i;
        }

        // Skip empty tags
        if (currentTag.isEmpty()) {
            continue;
        }

        // Check if it's an opening or closing tag
        if (isOpeningTag(currentTag)) {
            tagStack.push(currentTag);
        } else if (isClosingTag(currentTag)) {
            if (tagStack.empty() || tagStack.top() != currentTag) {
                return false; // Inconsistency: mismatched tags
            }
            tagStack.pop();
        }
    }

    // Check if all tags are closed
    return tagStack.empty();
}*/
/*
bool XMLParser::isOpeningTag(const QString& tag) {
    return tag.startsWith('<') && tag.endsWith('>') && !tag.startsWith("</");
}

bool XMLParser::isClosingTag(const QString& tag) {
    return tag.startsWith("</") && tag.endsWith('>');
}

*/
