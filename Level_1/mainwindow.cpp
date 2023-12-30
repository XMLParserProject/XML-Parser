#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"
#include"Helpers.h"
#include"graph.h"
#include <QDebug>


HuffmanTree root;
XMLParser xmlParser;
Prettify prettify;
QStack<QString> undo;
QStack<QString> redo;


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
            undo.push(xmlContent);
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
        undo.push(xmlContent);
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
    CorrectErrors correct_xml;
    QString xmlcontent = xmlParser.getxmlcontent();
    QString correctedXML=correct_xml.correct_errors(xmlcontent);

    undo.push(correctedXML);
    xmlParser.setXMLContent(correctedXML);

    QLabel *correctErrors = new QLabel(this);
    correctErrors->setText(correctedXML);
    correctErrors->setWordWrap(true);

    ui->scrollArea_2->setWidget(correctErrors);
    ui->scrollArea_2->setWidgetResizable(true);

}

void MainWindow::on_PrettifyingButton_clicked()
{
    QString xmlcontent = xmlParser.getxmlcontent();
    QString prettifiedXml = prettify.prettifyXml(xmlcontent);
    undo.push(prettifiedXml);
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
    XMLToJson json(xmlcontent.toStdString());
    string jsonText=json.getJSONText();
    undo.push(QString::fromStdString(jsonText));
    QLabel *ConvertToJsonLabel = new QLabel(this);
    ConvertToJsonLabel->setText(QString::fromStdString(jsonText));
    ConvertToJsonLabel->setWordWrap(true);

    ui->scrollArea_2->setWidget(ConvertToJsonLabel);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_MinifyingButton_clicked()
{
    QString xmlcontent = xmlParser.getxmlcontent();
    // 
    Helpers helper;
    string minifiedString = helper.removeUnwantedSpaces(xmlcontent.toStdString());
    // 
    undo.push(QString::fromStdString(minifiedString));
    QLabel *MinifyingLabel = new QLabel(this);
    MinifyingLabel->setText(QString::fromStdString(minifiedString));
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

    undo.push(QString::fromStdString(compress_data));
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
    undo.push(QString::fromStdString(decodedData));
    QLabel *DecompressLabel  = new QLabel(this);
    DecompressLabel->setText(QString::fromStdString(decodedData));
    DecompressLabel->setWordWrap(true);

    ui->scrollArea_2->setWidget(DecompressLabel);
    ui->scrollArea_2->setWidgetResizable(true);
}




void MainWindow::on_SocialNetworkAnalysis_clicked()
{
    QString xmlcontent = xmlParser.getxmlcontent();
    Graph graph;
    graph=createGraphOfUsers(xmlcontent.toStdString());
    User user = graph.most_influencer();
    string influencer="Most Influencer:\n\t" + user.getName() + "\n\tID: (" + user.getID() + ")";
    user=graph.most_active();
    string active_user="Most Active:\n\t" + user.getName() + "\n\tID: (" + user.getID() + ")";
    string analysis=influencer+"\n\n"+active_user;


    QDialog *newDialog = new QDialog(this);
    newDialog->setFixedSize(500, 400);
    newDialog->setWindowTitle("Social Network Analysis");
    //
    QScrollArea *scrollArea = new QScrollArea(newDialog);
    QLabel *resultLabel = new QLabel(QString::fromStdString(analysis), scrollArea);
    resultLabel->setWordWrap(true);
    scrollArea->setWidget(resultLabel);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    QVBoxLayout *resultLayout = new QVBoxLayout(newDialog);
    resultLayout->addWidget(scrollArea);

    newDialog->exec();
}


void MainWindow::on_mutualUsers_clicked()
{

    QDialog *inputDialog = new QDialog(this);
    inputDialog->setFixedSize(300, 150);
    inputDialog->setWindowTitle("Mutual users");
    QVBoxLayout *layout = new QVBoxLayout(inputDialog);
    QLabel *labelFirstID = new QLabel("Enter First ID:", inputDialog);
    QLineEdit *lineEditFirstID = new QLineEdit(inputDialog);
    QLabel *labelSecondID = new QLabel("Enter Second ID:", inputDialog);
    QLineEdit *lineEditSecondID = new QLineEdit(inputDialog);
    layout->addWidget(labelFirstID);
    layout->addWidget(lineEditFirstID);
    layout->addWidget(labelSecondID);
    layout->addWidget(lineEditSecondID);
    QPushButton *submitButton = new QPushButton("Submit", inputDialog);
    layout->addWidget(submitButton);
    connect(submitButton, &QPushButton::clicked, [this, inputDialog, lineEditFirstID, lineEditSecondID]() {
        string firstID = lineEditFirstID->text().toStdString();
        string secondID = lineEditSecondID->text().toStdString();

        QString xmlcontent = xmlParser.getxmlcontent();
        Graph graph;
        graph=createGraphOfUsers(xmlcontent.toStdString());
        string mutual_friend=graph.print_mutual_followers(firstID,secondID);

       QString resultString = QString::fromStdString(mutual_friend);



        QDialog *resultDialog = new QDialog(this);
        resultDialog->setFixedSize(500, 400);
        resultDialog->setWindowTitle("Mutual between two users");
        QScrollArea *scrollArea = new QScrollArea(resultDialog);
        QLabel *resultLabel = new QLabel(resultString, scrollArea);
        resultLabel->setWordWrap(true);
        scrollArea->setWidget(resultLabel);
        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        QVBoxLayout *resultLayout = new QVBoxLayout(resultDialog);
        resultLayout->addWidget(scrollArea);
        resultDialog->exec();
        inputDialog->close();
    });
    inputDialog->exec();
}




void MainWindow::on_showSuggestions_clicked()
{
    QDialog *inputDialog = new QDialog(this);
    inputDialog->setFixedSize(300, 150);
    inputDialog->setWindowTitle("Suggestions");
    QVBoxLayout *layout = new QVBoxLayout(inputDialog);
    QLabel *labelFirstID = new QLabel("Enter The user's ID:", inputDialog);
    QLineEdit *lineEditFirstID = new QLineEdit(inputDialog);
    layout->addWidget(labelFirstID);
    layout->addWidget(lineEditFirstID);
    QPushButton *submitButton = new QPushButton("Submit", inputDialog);
    layout->addWidget(submitButton);
    connect(submitButton, &QPushButton::clicked, [this, inputDialog, lineEditFirstID]() {
        string ID = lineEditFirstID->text().toStdString();

        QString xmlcontent = xmlParser.getxmlcontent();
        Graph graph;
        graph=createGraphOfUsers(xmlcontent.toStdString());
        string suggest_friend=graph.print_follow_suggestion(ID);

        QString resultString = QString::fromStdString(suggest_friend) ;



        QDialog *resultDialog = new QDialog(this);
        resultDialog->setFixedSize(500, 400);
        resultDialog->setWindowTitle("Mutual between two users");
        QScrollArea *scrollArea = new QScrollArea(resultDialog);
        QLabel *resultLabel = new QLabel(resultString, scrollArea);
        resultLabel->setWordWrap(true);

        scrollArea->setWidget(resultLabel);
        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        QVBoxLayout *resultLayout = new QVBoxLayout(resultDialog);
        resultLayout->addWidget(scrollArea);
        resultDialog->exec();
        inputDialog->close();
    });
    inputDialog->exec();
}


void MainWindow::on_postSearch_clicked()
{
    QDialog *inputDialog = new QDialog(this);
    inputDialog->setFixedSize(300, 150);
    inputDialog->setWindowTitle("Post search");
    QVBoxLayout *layout = new QVBoxLayout(inputDialog);
    QLabel *post = new QLabel("Enter a post:", inputDialog);
    QLineEdit *postText = new QLineEdit(inputDialog);
    layout->addWidget(post);
    layout->addWidget(postText);
    QPushButton *submitButton = new QPushButton("Submit", inputDialog);
    layout->addWidget(submitButton);
    connect(submitButton, &QPushButton::clicked, [this, inputDialog, postText]() {
        string post = postText->text().toStdString();

        QString xmlcontent = xmlParser.getxmlcontent();
        Graph graph;
        graph=createGraphOfUsers(xmlcontent.toStdString());
        string related_post=graph.print_post_search(post);

        QString resultString = QString::fromStdString(related_post);



        QDialog *resultDialog = new QDialog(this);
        resultDialog->setFixedSize(600, 500);
        resultDialog->setWindowTitle("Post search result");
        QScrollArea *scrollArea = new QScrollArea(resultDialog);
        QLabel *resultLabel = new QLabel(resultString, scrollArea);
        resultLabel->setWordWrap(true);

        scrollArea->setWidget(resultLabel);
        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        QVBoxLayout *resultLayout = new QVBoxLayout(resultDialog);
        resultLayout->addWidget(scrollArea);

        resultDialog->exec();
        inputDialog->close();
    });
    inputDialog->exec();
}


void MainWindow::on_graphVisualization_clicked()
{
    QString xmlcontent = xmlParser.getxmlcontent();
    Graph graph;
    graph=createGraphOfUsers(xmlcontent.toStdString());
    unordered_map<string, vector<string>> dataToVisualize = graph.get_follower_edge();
    GraphDialog *graphDialog = new GraphDialog(dataToVisualize, this);

    graphDialog->setWindowTitle("Graph Visualization");


    graphDialog->exec();
}


void MainWindow::on_undoButton_clicked()
{
    if(!undo.empty()){
        redo.push(undo.top());
        undo.pop();
        QString previousString = undo.top();

        QLabel *UndoLabel = new QLabel(this);
        UndoLabel->setText(previousString);
        UndoLabel->setWordWrap(true);
        ui->scrollArea_2->setWidget(UndoLabel);
        ui->scrollArea_2->setWidgetResizable(true);
    }else{
        qDebug()<<"No operation to be undone";
    }
}


void MainWindow::on_redoButton_clicked()
{
    QString previousString;
    if(!redo.empty()){
        previousString = redo.top();
        undo.push(redo.top());
        redo.pop();
        QLabel *RedoLabel = new QLabel(this);
        RedoLabel->setText(previousString);
        RedoLabel->setWordWrap(true);
        ui->scrollArea_2->setWidget(RedoLabel);
        ui->scrollArea_2->setWidgetResizable(true);

    }else{
    qDebug()<<"No operation to be redone";
}


}


void MainWindow::on_saveButton_clicked()
{
    QString saveFile = undo.top();
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save XML File"), QDir::homePath(), tr("XML Files (*.xml)"));

    // Save compressed data to the chosen file
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            stream <<saveFile;
            file.close();
        } else {
            // Handle error opening the file
            qDebug() << "Error opening file for writing:" << file.errorString();
        }
    }
}

