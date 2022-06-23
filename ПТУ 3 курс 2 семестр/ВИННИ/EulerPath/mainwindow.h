#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graph.h"
#include "graphwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_btnGenerate_clicked();
    void on_btnReset_clicked();
    void updateDescr();
    void on_btnStepFront_clicked();
    void on_btnStepBack_clicked();
    void on_btnStartAuto_clicked();
    void on_btnShowResult_clicked();
    void on_btnInput_clicked();

private:
    Ui::MainWindow *ui;

    Graph * graph;
    GraphWidget * grw;
};
#endif // MAINWINDOW_H
