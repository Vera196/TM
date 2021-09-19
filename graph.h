#ifndef GRAPH_H
#define GRAPH_H
#include <qcustomplot.h>
#include <QWidget>

class Graph : public QWidget
{
    Q_OBJECT

    QCustomPlot* graph;

public:
    Graph();
    void setQWidget(QCustomPlot *plot);
    void printPlot(QVector<double>, QVector<double>);

signals:

};

#endif // GRAPH_H
