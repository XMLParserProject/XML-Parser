#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"
#include <QDebug>



XMLParser xmlParser;

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
               // qDebug() << "Queue front:" << check.front();
              // QApplication::exit();//used for debugging
            }
        } else {
            qDebug() << "Error opening XML file";
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
           // qDebug() << "Queue front:" << check.front();
            displayXmlWithMistakes(xmlContent);
          //QApplication::exit();//used for debugging
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

void MainWindow::displayXmlWithMistakes(const QString& xmlContent) {
    // Create a new QTextBrowser to display the XML content with mistakes highlighted
    QTextBrowser *xmlBrowser = new QTextBrowser(this);

    // Set the XML content to the QTextBrowser
    xmlBrowser->setPlainText(xmlContent);

    // Process the XML content and highlight mistakes
    QTextCursor cursor(xmlBrowser->document());

    // Identify the missing closing tag
    int errorStart = xmlContent.indexOf('<');
    int errorEnd = xmlContent.indexOf('>', errorStart + 1);

    while (errorStart != -1 && errorEnd != -1) {
        if (xmlContent[errorStart + 1] != '/') {
            // Check if the tag is an opening tag
            QString tagName = xmlContent.mid(errorStart + 1, errorEnd - errorStart - 1).trimmed();

            if (!check.isEmpty() && tagName == check.front()) {
                // Change the color of the matching tag to red
                QTextCharFormat format;
                format.setForeground(QColor(Qt::red));

                // Calculate the start and end positions of the current tag
                int tagStart = errorStart;
                int tagEnd = errorEnd;

                // Apply formatting only to the current tag
                cursor.setPosition(tagStart);
                cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, tagEnd - tagStart + 1);
                cursor.mergeCharFormat(format);
                // Dequeue the front of the queue
                check.dequeue();
            }
        }

        // Move to the next potential error
        errorStart = xmlContent.indexOf('<', errorEnd);
        errorEnd = xmlContent.indexOf('>', errorStart + 1);
    }

    // Add the new QTextBrowser to the layout
    ui->verticalLayout->addWidget(xmlBrowser);
}

void MainWindow::on_label_linkActivated(const QString &link)
{
     qDebug() << "Link Activated:" << link;
}








