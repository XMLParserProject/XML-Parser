#include "mainwindow.h"
#include "ui_mainwindow.h"



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
                //displayXmlWithMistakes(xmlContent);
               QApplication::exit();//used for debugging
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
           // displayXmlWithMistakes(xmlContent);
           QApplication::exit();//used for debugging
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
    // Create a new QTextEdit to display the XML content with mistakes underlined
    QTextEdit *xmlTextEdit = new QTextEdit(this);

    // Use QTextDocument for more control over formatting
    QTextDocument *document = new QTextDocument();
    xmlTextEdit->setDocument(document);

    // Set the XML content to the QTextEdit
    xmlTextEdit->setPlainText(xmlContent);

    // Identify the missing closing tag
    int errorStart = xmlContent.indexOf('<');
    int errorEnd = xmlContent.indexOf('>', errorStart + 1);

    while (errorStart != -1 && errorEnd != -1) {
        // Check if the tag is incomplete (missing closing tag)
        QString tag = xmlContent.mid(errorStart, errorEnd - errorStart + 1);
        if (tag.contains('<') || tag.contains('/')) {
            QTextCursor cursor(xmlTextEdit->document());
            cursor.setPosition(errorStart);
            cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, errorEnd - errorStart + 1);
            QTextCharFormat format;
            format.setUnderlineStyle(QTextCharFormat::WaveUnderline);
            cursor.mergeCharFormat(format);
        }

        // Move to the next potential error
        errorStart = xmlContent.indexOf('<', errorEnd);
        errorEnd = xmlContent.indexOf('>', errorStart + 1);
    }

    // Set the QTextEdit as the widget of the new QScrollArea
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(xmlTextEdit);
    scrollArea->setWidgetResizable(true);

    // Add the new QScrollArea to the layout
    ui->verticalLayout->addWidget(scrollArea);
}



void MainWindow::on_label_linkActivated(const QString &link)
{
     qDebug() << "Link Activated:" << link;
}




