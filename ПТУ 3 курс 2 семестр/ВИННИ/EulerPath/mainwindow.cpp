#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QBoxLayout>
#include <QScrollBar>
#include <QThread>
#include <QTimer>
#include <InsertGraphDialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // выделения памяти для хранения графа (сначала он пустой)
    graph = new Graph(this);

    // для рисования графа
    grw = new GraphWidget(graph);
    QHBoxLayout * lay = new QHBoxLayout();
    lay->addWidget(grw);
    ui->frGraphics->setLayout(lay);

    connect(graph, &Graph::updated, this, &MainWindow::updateDescr);
}

MainWindow::~MainWindow()
{
    delete graph;
    delete ui;
}

// генерация графа
void MainWindow::on_btnGenerate_clicked()
{
    graph->setVertexCount(ui->spbVCount->text().toInt());
    graph->generate(ui->spbEProcent->text().toInt());
    ui->frGraphics->repaint();
}


void MainWindow::on_btnReset_clicked()
{
    graph->clearPath();
}

void MainWindow::updateDescr()
{
    ui->textEdit->clear();
    QList<QStringList> descr = graph->getDescr();
    for(int s = 0; s < descr.size(); s++)
    {
        ui->textEdit->insertHtml(QString("<b>Шаг %1</b><br>").arg(s));
        for(int str = 0; str < descr.at(s).size(); str++)
            ui->textEdit->insertHtml(QString("   <span>%1</span><br>").arg(descr.at(s).at(str)));
    }
    ui->textEdit->verticalScrollBar()->setSliderPosition(ui->textEdit->verticalScrollBar()->maximum());

    int step = graph->getStep();
    ui->lblStep->setText(step < 0 ? " " : QString::number(step));
}

void MainWindow::on_btnStepFront_clicked()
{
    graph->nextStep();
}

void MainWindow::on_btnStepBack_clicked()
{
    graph->previosStep();
}

void MainWindow::on_btnStartAuto_clicked()
{
    int delay = ui->spbDelay->text().toUInt();
    ui->btnStartAuto->setEnabled(false);
    int result = 0;
    while(result == 0)
    {
        result = graph->nextStep();
        if(result == 0)
            thread()->sleep(delay);
    }
    ui->btnStartAuto->setEnabled(true);
}


void MainWindow::on_btnShowResult_clicked()
{
    graph->showResult();
}

void MainWindow::on_btnInput_clicked()
{
    int V = ui->spbVCount->text().toInt();
    if(graph->getVertexCount() != V)
        graph->setVertexCount(V);
    InsertGraphDialog dia(V, this);
    dia.setM(graph->getM());
    if(dia.exec() == QDialog::Accepted)
    {
        graph->setM(dia.getM());
    }
}
