#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QStack>
#include <QList>
#include <QVector>

// Класс графа
class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(QObject *parent = nullptr);

    void setVertexCount(int vcount);
    int getVertexCount() const;
    void generate(int eprocent = 70);
    QVector<QVector<bool>> getM() const;
    void setM(QVector<QVector<bool>> m);

    // для Эйлерова пути
    void clearPath(bool update = true);
    int nextStep(bool update = true);
    void previosStep();
    QList<QStringList> getDescr() const;
    QList<int> getPath() const;
    int getStep();
    int showResult();

private:
    int V = -1; // количество вершин
    QVector<QVector<bool>> M; // матрица смежности графа

    // для Эйлерова пути
    int step = -1;  // текущий шаг алгоритма
    QList<int> path; // текущий путь
    QList<QStringList> descr; // текстовое описание шагов
    QStack<int> stack;
    QVector<QVector<bool>> Mp; // матрица смежности графа

    bool isEulerPathExists();
    int nextStepP();

signals:
    void updated();

    friend class GraphWidget;
};

#endif // GRAPH_H
