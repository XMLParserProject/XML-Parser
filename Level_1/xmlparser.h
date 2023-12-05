#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QString>
//#include "stack.h"
#include <QXmlStreamReader>
#include "globals.h"
#include <QDebug>
#include <QStack>

class XMLParser {
public:
    XMLParser();
    void setXMLContent(const QString& content);
    bool checkConsistency();

private:
    QString xmlContent;
    QStack<QString> tagStack;

    bool isOpeningTag(const QString& tag);
    bool isClosingTag(const QString& tag);
};

#endif // XMLPARSER_H
