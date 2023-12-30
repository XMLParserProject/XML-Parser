#ifndef GRAPHDIALOG_H
#define GRAPHDIALOG_H

#include <QDialog>
#include "GraphViewer.h"
using namespace std;

class GraphDialog : public QDialog
{
    Q_OBJECT

public:
    GraphDialog(const unordered_map<string, vector<string>> &graphData, QWidget *parent = nullptr);
};

#endif // GRAPHDIALOG_H
