#include "GraphViewer.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QRandomGenerator>
using namespace std;

GraphViewer::GraphViewer(const unordered_map<string, vector<string>> &graphData, QWidget *parent)
    : QGraphicsView(parent), graphData(graphData)
{
    setFixedSize(800, 600);

    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);

    for (const auto &entry : graphData)
    {
        addNode(entry.first);
    }

    for (const auto &entry : graphData)
    {
        const string &userID = entry.first;
        const vector<string> &followers = entry.second;

        for (const string &follower : followers)
        {
            addEdge(userID, follower);
        }
    }
}

void GraphViewer::addNode(const string &userID)
{
    int nodeSize = 40;
    int sceneWidth = 400;
    int sceneHeight = 400;

    QGraphicsEllipseItem *node = new QGraphicsEllipseItem(0, 0, nodeSize, nodeSize);
    while (true)
    {
        qreal x = QRandomGenerator::global()->bounded(sceneWidth);
        qreal y = QRandomGenerator::global()->bounded(sceneHeight);

        node->setPos(x, y);

        bool collision = false;
        for (QGraphicsItem *item : scene()->items())
        {
            if (item != node && item->collidesWithItem(node))
            {
                collision = true;
                break;
            }
        }

        if (!collision)
            break;
    }

    node->setBrush(Qt::cyan);
    node->setToolTip(QString::fromStdString(userID));
    scene()->addItem(node);

    QGraphicsTextItem *text = new QGraphicsTextItem(QString::fromStdString(userID), node);
    text->setPos((nodeSize - text->boundingRect().width()) / 2, (nodeSize - text->boundingRect().height()) / 2);
    scene()->setBspTreeDepth(10);
}


void GraphViewer::addEdge(const string &userID1, const string &userID2)
{
    QGraphicsEllipseItem *item1 = nullptr;
    QGraphicsEllipseItem *item2 = nullptr;

    QList<QGraphicsItem *> itemsList = scene()->items();
    for (QGraphicsItem *item : itemsList)
    {
        QGraphicsEllipseItem *ellipseItem = dynamic_cast<QGraphicsEllipseItem *>(item);
        if (ellipseItem)
        {
            if (ellipseItem->toolTip().toStdString() == userID1)
                item1 = ellipseItem;
            else if (ellipseItem->toolTip().toStdString() == userID2)
                item2 = ellipseItem;
        }

        if (item1 && item2)
            break;
    }

    if (item1 && item2)
    {
        QPointF pos1 = item1->scenePos() + QPointF(item1->rect().width() / 2, item1->rect().height() / 2);
        QPointF pos2 = item2->scenePos() + QPointF(item2->rect().width() / 2, item2->rect().height() / 2);

        QPointF direction = pos2 - pos1;
        direction /= sqrt(direction.x() * direction.x() + direction.y() * direction.y());

        QPointF startPoint1 = pos1 + direction * (item1->rect().width() / 2);
        QPointF endPoint2 = pos2 - direction * (item2->rect().width() / 2);
        QGraphicsLineItem *edge = new QGraphicsLineItem(startPoint1.x(), startPoint1.y(), endPoint2.x(), endPoint2.y());
        edge->setPen(QPen(Qt::black, 2));
        scene()->addItem(edge);

        const qreal arrowScale = 0.8;

        QPointF arrowP1 = endPoint2 - direction * 10 * arrowScale + QPointF(-direction.y(), direction.x()) * 5 * arrowScale;
        QPointF arrowP2 = endPoint2 - direction * 10 * arrowScale - QPointF(-direction.y(), direction.x()) * 5 * arrowScale;

        QPolygonF arrowhead;
        arrowhead << endPoint2 << arrowP1 << arrowP2;

        QGraphicsPolygonItem *arrow = new QGraphicsPolygonItem(arrowhead);
        arrow->setBrush(Qt::black);
        scene()->addItem(arrow);
    }
    else
    {
        qWarning() << "Failed to find QGraphicsEllipseItem for one or both users.";
    }
}
