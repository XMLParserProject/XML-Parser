#ifndef PRETTIFY_H
#define PRETTIFY_H


#include <QString>


class Prettify
{
    QString prettifiedXml;
    int indentationLevel;
    bool isOpening_tag;



public:
    Prettify();
    void writeIndentation();
    void printLine(const QString& line);
    QString prettifyXml(const QString& xmlContent);


};

#endif // PRETTIFY_H
