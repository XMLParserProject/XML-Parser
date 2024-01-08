#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QString>
#include <QXmlStreamReader>
#include "globals.h"
#include <QDebug>
#include <QStack>
#include "Helpers.h"

class XMLParser {
public:
    XMLParser();
    void setXMLContent(const QString& content);
    bool checkConsistency();
    QString getxmlcontent();

private:
    QString xmlContent;
    QStack<QString> tagStack;

    bool isOpeningTag(const QString& tag);
    bool isClosingTag(const QString& tag);
};

#endif // XMLPARSER_H
