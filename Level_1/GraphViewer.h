#ifndef GRAPHVIEWER_H
#define GRAPHVIEWER_H

#include <QGraphicsView>
using namespace std;

class GraphViewer : public QGraphicsView
{
    Q_OBJECT

public:
    GraphViewer(const unordered_map<string, vector<string>> &graphData, QWidget *parent = nullptr);

private:
    void addNode(const string &userID);
    void addEdge(const string &userID1, const string &userID2);

    const unordered_map<string, vector<string>> &graphData;
};

#endif // GRAPHVIEWER_
