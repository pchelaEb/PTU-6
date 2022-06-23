#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QList>
#include <QWidget>
#include <graph.h>

namespace Ui {
class GraphWidget;
}

class GraphWidget : public QWidget
{
    Q_OBJECT

    struct VerticePosition
    {
        int x, y;
        int num;
        VerticePosition(int _x, int _y, int _num) : x(_x), y(_y), num(_num){}
    };

    struct EdgePosition
    {
        int x1, y1;
        int x2, y2;
        bool inpath;
        bool instack;
        EdgePosition(int _x1, int _y1, int _x2, int _y2, bool _inpath, bool _instack): x1(_x1), y1(_y1), x2(_x2), y2(_y2), inpath(_inpath), instack(_instack) {}
    };

public:
    explicit GraphWidget(Graph* gr, QWidget *parent = nullptr);
    ~GraphWidget();

protected:
    void paintEvent(QPaintEvent *) override;

private:
    Ui::GraphWidget *ui;
    Graph * graph;
    QList<VerticePosition> vpos; // координаты вершин графа
    QList<EdgePosition> epos; // координаты ребер графа
    QList<VerticePosition> spos; // координаты стека поиска пути


    const int d = 28;

private slots:
    void graphUpdated();
};

#endif // GRAPHWIDGET_H
