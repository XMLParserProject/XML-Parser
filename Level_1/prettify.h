#ifndef PRETTIFY_H
#define PRETTIFY_H


#include <QString>
#include <QRegularExpression>

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
    QString filterConsecutiveNewlines(QString content);

};

#endif // PRETTIFY_H
