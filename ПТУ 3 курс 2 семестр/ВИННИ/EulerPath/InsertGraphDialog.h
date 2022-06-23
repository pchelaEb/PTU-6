#ifndef INSERTGRAPHDIALOG_H
#define INSERTGRAPHDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QVector>

namespace Ui {
class InsertGraphDialog;
}

class InsertGraphDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsertGraphDialog(int v, QWidget *parent = nullptr);
    ~InsertGraphDialog();

    QVector<QVector<bool>> getM();
    void setM(QVector<QVector<bool>> M);

private:
    Ui::InsertGraphDialog *ui;

    int V;

private slots:
    void itemChanged(QTableWidgetItem *item);
};

#endif // INSERTGRAPHDIALOG_H
