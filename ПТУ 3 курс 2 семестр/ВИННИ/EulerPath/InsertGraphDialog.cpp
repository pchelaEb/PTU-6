#include "InsertGraphDialog.h"
#include "ui_InsertGraphDialog.h"

#include <QTableWidget>

InsertGraphDialog::InsertGraphDialog(int v, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertGraphDialog)
{
    ui->setupUi(this);

    V = v;

    if(V <= 1)
        return;

    ui->tblMatrix->setRowCount(V);
    ui->tblMatrix->setColumnCount(V);
    QStringList labels;
    for(int i = 0; i < V; i++)
    {
        labels.append(QString::number(i));
        for(int j = 0; j < V; j++)
        {
            ui->tblMatrix->setItem(i, j, new QTableWidgetItem("0"));
        }
    }

    ui->tblMatrix->setHorizontalHeaderLabels(labels);
    ui->tblMatrix->setVerticalHeaderLabels(labels);

    connect(ui->tblMatrix, &QTableWidget::itemChanged, this, &InsertGraphDialog::itemChanged);
}

InsertGraphDialog::~InsertGraphDialog()
{
    delete ui;
}

QVector<QVector<bool> > InsertGraphDialog::getM()
{
    QVector<QVector<bool> > M;

    M.resize(V);
    for(int r = 0; r < V; r++)
    {
        M[r].resize(V);
        for(int c = 0; c < V; c++)
        {
            M[r][c] = ui->tblMatrix->item(r, c)->text() == "0" ? false : true;
        }
    }

    return M;
}

void InsertGraphDialog::setM(QVector<QVector<bool> > M)
{
    for(int r = 0; r < V; r++)
    {
        for(int c = 0; c < V; c++)
        {
            ui->tblMatrix->item(r, c)->setText(M[r][c] ? "1" : "0");
        }
    }
}

void InsertGraphDialog::itemChanged(QTableWidgetItem *item)
{
    QString text = item->text();
    int row = item->row();
    int col = item->column();

    if(row == col)
    {
        text = "0";
        item->setText(text);
        return;
    }

    if(text != "0" && text != "1")
    {
        text = "0";
        item->setText(text);
    }
    ui->tblMatrix->item(col, row)->setText(text);
}
