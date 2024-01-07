#ifndef CORRECTERRORS_H
#define CORRECTERRORS_H


#include <QString>
#include <QXmlStreamReader>
#include "globals.h"
#include <QDebug>
#include <QStack>
#include "xmlparser.h"


class CorrectErrors
{
public:
    CorrectErrors();
    QString GetcorrectedXmlContent();

    QString correct_errors(QString& xmlContent);


private:
    QString correctedXmlContent ;
};

#endif // CORRECTERRORS_H
