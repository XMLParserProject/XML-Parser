#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include "stack.h"
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
#include <stack.h>


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



private:
    Ui::MainWindow *ui;
    void displayXmlContent(const QString& xmlContent);
    void displayXmlWithMistakes(const QString& xmlContent);
    void highlightMistake(QTextDocument* document, const QString& tagName, const QString& errorToken);

};
#endif // MAINWINDOW_H
