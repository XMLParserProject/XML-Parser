#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QString>
#include "stack.h"
#include <QXmlStreamReader>

class XMLParser {
public:
    XMLParser();
    void setXMLContent(const QString& content);
    bool checkConsistency();

private:
    QString xmlContent;
    Stack<QString> tagStack;

    bool isOpeningTag(const QString& tag);
    bool isClosingTag(const QString& tag);
};

#endif // XMLPARSER_H
