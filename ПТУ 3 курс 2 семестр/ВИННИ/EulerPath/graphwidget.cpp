#include "graphwidget.h"
#include "ui_graphwidget.h"

#include <QPainter>
#include <QDebug>

GraphWidget::GraphWidget(Graph *gr, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphWidget)
{
    ui->setupUi(this);

    graph = gr;

    connect(gr, &Graph::updated, this, &GraphWidget::graphUpdated);

}

GraphWidget::~GraphWidget()
{
    delete ui;
}

void GraphWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setFont(QFont("Times", d/2));


    // отрисовка ребер
    for(int e = 0; e < epos.size(); e++)
    {
        if(epos.at(e).inpath)
            p.setPen(QPen(Qt::green, 3 ,Qt::SolidLine));
        else if(epos.at(e).instack)
            p.setPen(QPen(Qt::black, 3 ,Qt::DashLine));
        else
            p.setPen(QPen(Qt::black, 3 ,Qt::SolidLine));
        p.drawLine(epos.at(e).x1, epos.at(e).y1, epos.at(e).x2, epos.at(e).y2);
    }

    // отрисовка вершин
    p.setBrush(QBrush(Qt::white));
    for(int v = 0; v < vpos.size(); v++)
    {
        p.setPen(QPen(Qt::red, 3 ,Qt::SolidLine));
        p.drawEllipse(vpos.at(v).x, vpos.at(v).y, d, d);
        p.setPen(QPen(Qt::black, 3 ,Qt::SolidLine));
        p.drawText(vpos.at(v).x+d/4, vpos.at(v).y+d*2/3, QString::number(vpos.at(v).num));
    }

    // отрисовка стека
    if(!spos.empty())
        p.drawText(d/4, height(), "СТЕК");
    for(int v = 0; v < spos.size(); v++)
    {
        p.setPen(QPen(Qt::red, 3 ,Qt::SolidLine));
        p.drawEllipse(spos.at(v).x, spos.at(v).y, d, d);
        p.setPen(QPen(Qt::black, 3 ,Qt::SolidLine));
        p.drawText(spos.at(v).x+d/4, spos.at(v).y+d*2/3, QString::number(spos.at(v).num));
    }
}

void GraphWidget::graphUpdated()
{
    int v = graph->getVertexCount();
    int rows = 2;
    int cols = 1;

    while(rows * cols < v)
    {
        if(cols < rows)
            cols++;
        else
            rows++;
    }

    int w = width();
    int h = height();
    int currentV = 0;

    // расчет координат вершин
    vpos.clear();
    for(int r = 0; r < rows; r++)
    {
        int totalInRow = (v - currentV) / (rows - r);
        if(totalInRow > cols)
            totalInRow = cols;
        for(int c = 0; c < totalInRow; c++)
        {
            int x = (w/(cols+1))*(c+1);
            int y = (h/(rows+1))*(r+1);
            if(r % 2 == 0)
                x += (w/(cols+1)) * 0.3;
            if(c % 2 == 0)
                y += (h/(rows+1)) * 0.3;
            vpos.append(VerticePosition(x, y, currentV));
            currentV++;
        }
    }

    // расчет координат ребер
    epos.clear();
    QVector<QVector<bool>> M = graph->M;
    QList<int> path = graph->path;
    for(int v1 = 0; v1 < v; v1++)
        for(int v2 = v1; v2 < v; v2++)
            if(M[v1][v2])
            {
                bool inpath = false, instack = true;
                for(int p = 0; p < path.size()-1; p++)
                    if((path.at(p) == v1 && path.at(p+1) == v2) || (path.at(p) == v2 && path.at(p+1) == v1))
                    {
                        inpath = true;
                        break;
                    }
                if(graph->Mp[v1][v2])
                    instack = false;

                epos.append(EdgePosition(vpos.at(v1).x + d/2, vpos.at(v1).y + d/2, vpos.at(v2).x + d/2, vpos.at(v2).y + d/2, inpath, instack));
            }

    // расчет координат для отображения стека
    spos.clear();
    QList<int> st = graph->stack.toList();
    int sh = d;
    if(d*2+d*(st.size()+1) > h)
    {
        sh = (h - d*2) / st.size();
    }
    for(int i = 0; i < st.size(); i++)
    {
        int v = st.at(i);

        int x = d/4;
        int y = h - d*2 - sh*spos.size();

        spos.append(VerticePosition(x, y, v));
    }

    repaint();
}
