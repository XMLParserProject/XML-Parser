#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"
#include"Helpers.h"
#include <QDebug>


HuffmanTree root;
XMLParser xmlParser;
Prettify prettify;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadFileButton_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Choose an XML file", QString(), "XML Files (*.xml)");

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString xmlContent = QTextStream(&file).readAll();
            file.close();

            // Set the XML content in the parser
            xmlParser.setXMLContent(xmlContent);

            // Check consistency and handle the result
            if (xmlParser.checkConsistency()) {
                // XML is consistent, show in a new scroll area
                displayXmlContent(xmlContent);
            } else {
                // XML has inconsistencies, show with mistakes underlined
               displayXmlWithMistakes(xmlContent);
            }
        } else {
            // Handle error opening the file
            qDebug() << "Error opening XML file" << file.errorString();
        }
    }
}

void MainWindow::on_enterXmlButton_clicked() {
    bool ok;
    QString xmlContent = QInputDialog::getText(this, "Enter XML Content", "XML Content:", QLineEdit::Normal, "", &ok);

    if (ok && !xmlContent.isEmpty()) {
        // Set the XML content in the parser
        xmlParser.setXMLContent(xmlContent);

        // Check consistency and handle the result
        if (xmlParser.checkConsistency()) {
            // XML is consistent, show in a new scroll area
            displayXmlContent(xmlContent);
        } else {
            // XML has inconsistencies, show with mistakes underlined
            displayXmlWithMistakes(xmlContent);
        }
    }
}

void MainWindow::displayXmlContent(const QString& xmlContent)
{
    // Create a new QLabel to display the XML content
    QLabel *xmlLabel = new QLabel(this);
    xmlLabel->setText(xmlContent);
    xmlLabel->setWordWrap(false);

    // Set the QLabel as the widget of the new QScrollArea
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(xmlLabel);
    scrollArea->setWidgetResizable(true);

    // Add the new QScrollArea to the layout
    ui->verticalLayout->addWidget(scrollArea);

}

/*
________________________________________________________________
*/

void MainWindow::displayXmlWithMistakes(const QString& xmlContent) {
    // Create a new QTextBrowser to display the XML content with mistakes highlighted
    QTextBrowser *xmlBrowser = new QTextBrowser(this);

    // Set the XML content to the QTextBrowser
    xmlBrowser->setPlainText(xmlContent);

    // Process the XML content and highlight mistakes
    highlightXmlMistakes(xmlBrowser, xmlContent);

    // Add the new QTextBrowser to the layout
    ui->verticalLayout->addWidget(xmlBrowser);
    
}

void MainWindow::highlightXmlMistakes(QTextBrowser* xmlBrowser, const QString& xmlContent) {
    QTextCursor cursor(xmlBrowser->document());

    int errorStart = xmlContent.indexOf('<');
    int errorEnd = xmlContent.indexOf('>', errorStart + 1);

    while (errorStart != -1 && errorEnd != -1) {
        highlightTagError(cursor, xmlContent, errorStart, errorEnd);
        moveToNextError(xmlContent, errorEnd, errorStart);
    }
}

void MainWindow::highlightTagError(QTextCursor& cursor, const QString& xmlContent, int errorStart, int errorEnd) {
    if (xmlContent[errorStart + 1] != '/') {
        QString tagName = xmlContent.mid(errorStart + 1, errorEnd - errorStart - 1).trimmed();

        if (!check.isEmpty() && tagName == check.front()) {
            // Change the color of the matching tag to red
            QTextCharFormat format;
            format.setForeground(QColor(Qt::red));

            // Apply formatting only to the current tag
            cursor.setPosition(errorStart);
            cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, errorEnd - errorStart + 1);
            cursor.mergeCharFormat(format);

            // Dequeue the front of the queue
            check.dequeue();
        }
    }
}

void MainWindow::moveToNextError(const QString& xmlContent, int& errorEnd, int& errorStart) {
    // Move to the next potential error
    errorStart = xmlContent.indexOf('<', errorEnd);
    errorEnd = xmlContent.indexOf('>', errorStart + 1);
}

/*
________________________________________________________________
*/

void MainWindow::on_label_linkActivated(const QString &link)
{
     qDebug() << "Link Activated:" << link;
}



void MainWindow::on_correctErrorsButton_clicked()
{
    QString xmlcontent = xmlParser.getxmlcontent();








    QLabel *correctErrors = new QLabel(this);
    correctErrors->setText(xmlcontent);
    correctErrors->setWordWrap(true);

    ui->scrollArea_2->setWidget(correctErrors);
    ui->scrollArea_2->setWidgetResizable(true);
}

void MainWindow::on_PrettifyingButton_clicked()
{
    QString xmlcontent = xmlParser.getxmlcontent();
    QString prettifiedXml = prettify.prettifyXml(xmlcontent);
    xmlParser.setXMLContent(prettifiedXml);
    QLabel *PrettifyingLabel = new QLabel(this);
    PrettifyingLabel->setText(prettifiedXml);
    PrettifyingLabel->setWordWrap(true);

    ui->scrollArea_2->setWidget(PrettifyingLabel);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_ConvertToJsonButton_clicked()
{
    QString xmlcontent = xmlParser.getxmlcontent();
    // 
    XMLToJson json(xmlcontent);
    QString jsonText=json.getJSONText();
    // 
    QLabel *ConvertToJsonLabel = new QLabel(this);
    ConvertToJsonLabel->setText(jsonText);
    ConvertToJsonLabel->setWordWrap(true);

    ui->scrollArea_2->setWidget(ConvertToJsonLabel);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_MinifyingButton_clicked()
{
    QString xmlcontent = xmlParser.getxmlcontent();
    // 
    Helpers helper;
    QString minifiedString = helper.removeUnwantedSpaces(xmlcontent);
    // 

    QLabel *MinifyingLabel = new QLabel(this);
    MinifyingLabel->setText(minifiedString);
    MinifyingLabel->setWordWrap(true);

    ui->scrollArea_2->setWidget(MinifyingLabel);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_compressButton_clicked()
{
    QString xmlcontent = xmlParser.getxmlcontent();
    Helpers o1;
    string unSpaceXML = o1.removeUnwantedSpaces(xmlcontent.toStdString());

    string compress_data=root.compress(unSpaceXML);


    QLabel *compressLabel = new QLabel(this);
    compressLabel->setText(QString::fromStdString(compress_data));
    compressLabel->setWordWrap(true);

    ui->scrollArea_2->setWidget(compressLabel);
    ui->scrollArea_2->setWidgetResizable(true);

    QString filePath = QFileDialog::getSaveFileName(this, tr("Save XML File"), QDir::homePath(), tr("XML Files (*.xml)"));

    // Save compressed data to the chosen file
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << QString::fromStdString(compress_data);
            file.close();
        } else {
            // Handle error opening the file
            qDebug() << "Error opening file for writing:" << file.errorString();
        }
    }

}


void MainWindow::on_DecompressButton_clicked()
{
    string encodedData=root.getxmlcompressedfile();
    string binarydata=root.charToBinaryString(encodedData);
    HuffmanNode* TreeRoot =root.getTreeRoot();
    string decodedData=root.decodeData(binarydata,TreeRoot);

    QLabel *DecompressLabel  = new QLabel(this);
    DecompressLabel->setText(QString::fromStdString(decodedData));
    DecompressLabel->setWordWrap(true);

    ui->scrollArea_2->setWidget(DecompressLabel);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_SavejasonButton_clicked()
{

}

