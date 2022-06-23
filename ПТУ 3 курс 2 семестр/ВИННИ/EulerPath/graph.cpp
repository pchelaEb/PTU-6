#include "graph.h"

#include <QDebug>
#include <QTime>
#include <QStack>

Graph::Graph(QObject *parent) : QObject(parent)
{

}

void Graph::setVertexCount(int vcount)
{
    V = vcount;
    M.resize(V);
    for(int v1 = 0; v1 < V; v1++)
    {
        M[v1].resize(V);
        for(int v2 = 0; v2 < V; v2++)
        {
            M[v1][v2] = false;
        }
    }

    emit updated();
}

int Graph::getVertexCount() const
{
    return V;
}

void Graph::generate(int eprocent)
{
    if(eprocent <= 0 || eprocent > 100)
        eprocent = 70;

    // если был предыдущий граф, то "обнуляем" его матрицу смежности
    for(int i = 0; i < V; i++)
    {
        for(int j = 0; j < V; j++)
            M[i][j] = false;
    }

    // максимальное количество ребер
    int maxE = V * (V - 1) / 2;

    qsrand(QTime::currentTime().msec());
    int totalE = 0; // количество сгенерированных ребер

    // генерируем ребра (заполненность eprocent)
    while(totalE < maxE * eprocent/100.)
    {
        int v1 = qrand() % V;
        int v2 = qrand() % V;

        if(v1 == v2 || M[v1][v2])
            continue;

        M[v1][v2] = M[v2][v1] = true;
        totalE++;
    }

    clearPath();

    emit updated();
}

QVector<QVector<bool>> Graph::getM() const
{
    return M;
}

void Graph::setM(QVector<QVector<bool> > m)
{
    if(m.size() != V)
        return;

    for(int i = 0; i < V; i++)
    {
        for(int j = 0; j < V; j++)
        {
            M[i][j] = m[i][j];
        }
    }

    clearPath();
}

// вернуться в начало (для перезапуска алгоритма)
void Graph::clearPath(bool update)
{
    // очищаем все данные
    step = -1;
    path.clear();
    descr.clear();
    stack.clear();
    Mp.resize(V);
    for(int v1 = 0; v1 < V; v1++)
    {
        Mp[v1].resize(V);
        for(int v2 = 0; v2 < V; v2++)
            Mp[v1][v2] = M[v1][v2];
    }

    if(update)    emit updated();
}

// следующий шаг в алгоритме поиска Эйлерова пути
// возвращает -1, если в данном графе нет эйлерова пути
// возвращает 1, если путь найден, т.е. это был последний шаг алгоритма
// возвращает 0 в противном случае (промежуточный шаг алгоритма)
int Graph::nextStep(bool update)
{
    if(V <= 0)
        return -1;

    int result = nextStepP();

    if(update)
        emit updated();

    return result;
}

void Graph::previosStep()
{
    int toStep = step - 1;
    clearPath(false);
    for(int s = 0; s <= toStep; s++)
        nextStepP();
    emit updated();
}

QList<QStringList> Graph::getDescr() const
{
    return descr;
}

QList<int> Graph::getPath() const
{
    return path;
}

int Graph::getStep()
{
    return step;
}

int Graph::showResult()
{
    int result = 0;
    while(result == 0)
    {
        result = nextStep(false);
    }

    emit updated();

    return result;
}

// проверяет существовавание Эйлерова пути в графе
bool Graph::isEulerPathExists()
{
    // Эйлеров путь в графе существует тогда и только тогда, когда количество вершин с нечетными степенями равно 2
    // или 0, если это Эйлеров цикл
    int t = 0, total = 0;
    for(int v1 = 0; v1 < V; v1++)
    {
        int count = 0;
        for(int v2 = 0; v2 < V; v2++)
            if(M[v1][v2])
                count++;

        if(count % 2 == 1)
            t++;
        total += count;
    }

    if(total > 0 && (t == 0 || t == 2))
        return true;

    return false;
}

int Graph::nextStepP()
{
    // текущий шаг
    step++;

    if(descr.size() >= (step + 1))
        descr[step].clear();
    else
        descr.append(QStringList());
    if(step == 0)
    {
        // на первом шаге проверяем существование пути
        bool exists = isEulerPathExists();
        if(!exists)
        {
            descr[step].append("В данном графе Эйлеров путь не существует!");
            step = -1;
            return -1;
        }

        // добавляем стартовую вершину в стек
        int v = 0;
        QVector<int> cv;
        while(v < V)
        {
            int count = 0;
            for(int v2 = 0; v2 < V; v2++)
                if(v2 != v && M[v][v2])
                    count++;
            cv.append(count);
            v++;
        }

        // в качестве стартовой вершины берет первую из вершин с нечетной степенью
        // если таких вершин нет, то первую из вершин, из которой идут ребра
        int first = -1;
        for(int i = 0; i < cv.size(); i++)
        {
            if(cv.at(i) > 0)
            {
                if(cv.at(i) % 2 == 1)
                {
                    first = i;
                    break;
                }

                if(first == -1)
                    first = i;
            }
        }

        stack.push(first);
        descr[step].append(QString("Добавляем стартовую вершину №%1 в стек!").arg(first));
        return 0;
    }

    // если стек не пуск
    bool insertInPath = false;
    if(!stack.empty())
    {
        // берем вершину с вершины стека
        int v1 = stack.top();
        descr[step].append(QString("Берем вершину c вершины стека (вершина №%1). Проверяем, есть ли еще не рассмотренные ребра из этой вершины.").arg(v1));

        // поиск ребер, выходящих из этой вершины
        for(int v2 = 0; v2 < V; v2++)
        {
            // если ребро найдено
            if(Mp[v1][v2])
            {
                stack.push(v2); // добавляем смежную вершину в стек
                Mp[v1][v2] = Mp[v2][v1] = false; // удаляем ребро из графа
                descr[step].append(QString("Найдено ребро (%1, %2). Добавляем вершину %2 в стек.").arg(v1).arg(v2));
                return 0;
            }
        }

        // если ребер не найдено
        stack.pop(); // удаляем вершину с вершины стека
        path.append(v1); // добавляем вершину в путь
        descr[step].append(QString("Не рассмотренных ребер из вершины %1 не найдено. Удаляем вершину %1 из стека и добавляем ее в Эйлеров путь.").arg(v1));
        insertInPath = true;
    }

    // если стек пуск, значит путь найден
    if(stack.empty())
    {
        if(!insertInPath)
        {
            descr.removeAt(step);
            step--;
            return 1;
        }

        QString result;
        for(int p = 0; p < path.size(); p++)
        {
            if(p != 0)
                result += "-";
            result += QString::number(path.at(p));
        }
        descr[step].append(QString("Стек пуст. Эйлеров путь найден: %1.").arg(result));
        return 1;
    }

    return 0;
}
