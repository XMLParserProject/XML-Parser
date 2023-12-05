#include "xmlparser.h"


XMLParser::XMLParser() {
    // Initialization if needed
}

void XMLParser::setXMLContent(const QString& content) {
    xmlContent = content;
}

bool XMLParser::checkConsistency() {
    QStack tagStack = QStack<QString>();
    check.clear();  // Clear the queue before processing

    int index = 0;
    int length = xmlContent.length();

    while (index < length) {
        if (xmlContent[index] == '<') {
            // Check if it's a start or end tag
            bool isStartTag = true;
            if (index + 1 < length && xmlContent[index + 1] == '/') {
                isStartTag = false;
            }

            // Extract the tag name
            int startTagName = index + (isStartTag ? 1 : 2);  // Adjust index for start/end tags
            int endTagName = xmlContent.indexOf('>', startTagName);
            QString tagName = xmlContent.mid(startTagName, endTagName - startTagName).trimmed();

            if (isStartTag) {
                tagStack.push(tagName);
            } else {
                if (tagStack.isEmpty() || tagStack.top() != tagName) {
                    check.enqueue(tagStack.top());
                } else {
                    tagStack.pop();
                }
            }

            index = endTagName + 1;  // Move index to the character after '>'
        } else {
            index++;
        }
    }

    // Check for any remaining tags in the stack
    while (!tagStack.empty()) {
        check.enqueue(tagStack.top());
        tagStack.pop();
    }

    // Return true if the check queue is empty and there are no errors
    return check.isEmpty();
}
