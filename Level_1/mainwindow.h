#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QXmlStreamReader>
#include <QTextStream>
#include <QLabel>
#include <QInputDialog>
#include <xmlparser.h>
#include <QTextEdit>
#include <QTextDocument>
#include <QTextCursor>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QVector>
#include <QPair>
#include <QMessageBox>
#include <globals.h>
#include <QTextBrowser>
#include <QDomDocument>
#include <prettify.h>
#include"Compression.h"
#include "XMLToJson.h"
#include "correcterrors.h"



extern  HuffmanTree root;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_label_linkActivated(const QString &link);

    void on_loadFileButton_clicked();

    void on_enterXmlButton_clicked();

    void on_correctErrorsButton_clicked();

    void on_PrettifyingButton_clicked();

    void on_ConvertToJsonButton_clicked();

    void on_MinifyingButton_clicked();

    void on_compressButton_clicked();

    void on_DecompressButton_clicked();

    void on_SocialNetworkAnalysis_clicked();

    void on_mutualUsers_clicked();

    void on_showSuggestions_clicked();

    void on_postSearch_clicked();

private:
    Ui::MainWindow *ui;
    void displayXmlContent(const QString& xmlContent);
    void displayXmlWithMistakes(const QString& xmlContent);
    void highlightMistake(QTextDocument* document, const QString& tagName, const QString& errorToken);
    void highlightXmlMistakes(QTextBrowser* xmlBrowser, const QString& xmlContent);
    void highlightTagError(QTextCursor& cursor, const QString& xmlContent, int errorStart, int errorEnd);
    void moveToNextError(const QString& xmlContent, int& errorEnd, int& errorStart);



};
#endif // MAINWINDOW_H
