#include "GraphDialog.h"

GraphDialog::GraphDialog(const std::unordered_map<std::string, std::vector<std::string>> &graphData, QWidget *parent)
    : QDialog(parent)
{

    GraphViewer *graphViewer = new GraphViewer(graphData, this);
    graphViewer->setWindowTitle("Graph Visualization");
    graphViewer->show();
}
