#include "graph.h"

Graph::Graph()
{

}

void Graph::setQWidget(QCustomPlot *plot)
{
    this->graph = plot;
    graph->setInteraction(QCP::iRangeDrag, true);
    graph->setInteraction(QCP::iRangeZoom, true);
    graph->xAxis->setLabel("delta L");
    graph->yAxis->setLabel("Kraft");
    graph->addGraph();
}

void Graph::printPlot(QVector<double> DeltaL, QVector<double> Kraft)
{
    graph->graph(0)->setData(DeltaL, Kraft);
    graph->rescaleAxes();
    graph->replot();
    graph->update();
}
