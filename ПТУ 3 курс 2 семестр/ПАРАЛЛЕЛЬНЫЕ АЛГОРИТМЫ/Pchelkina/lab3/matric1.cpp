#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int row1, row2, col1, col2;
    double** a, ** b, ** c;
    system("chcp 1251");
    system("cls");
    cout << "Введите количество строк первой матрицы: ";
    cin >> row1;
    cout << "Введите количество столбцов первой матрицы: ";
    cin >> col1;
    cout << "Введите количество строк второй матрицы: ";
    cin >> row2;
    cout << "Введите количество столбцов второй матрицы: ";
    cin >> col2;
    if(col1 != row2)
    {
        cout << "Умножение невозможно!";
        cin.get(); cin.get();
        return 0;
    }

    a = new double* [row1];
    cout << "Введите элементы первой матрицы" << endl;
    for(int i = 0; i <row1; i++)
    {
        a[i] = new double[col1];
        for(int j = 0; j < col1; j++)
        {
            cout << "a[" << i << "][" << j << "]=";
            cin >> a[i][j];
        }
    }

    for(int i = 0; i < row1; i++)
    {
        for(int j = 0; j < col1; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }

    b = new double* [row2];
    cout << "Введите элементы второй матрицы" << endl;
    for(int i = 0; i < row2; i++)
    {
        b[i] = new double[col2];
        for(int j = 0; j < col2; j++)
        {
            cout << "b[" << i << "][" << j << "]=";
            cin >> b[i][j];
        }
    }
    for(int i = 0; i < row2; i++)
    {
        for(int j = 0; j < col2; j++)
        {
            cout << b[i][j] << " ";
        }
        cout << endl;
    }

    c = new double* [row1];
    for(int i = 0; i < row1; i++)
    {
        c[i] = new double[col2];
        for(int j = 0; j < col2; j++)
        {
            c[i][j] = 0;
            for(int k = 0; k < col1; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }

    cout << "Матрица произведения" << endl;
    for(int i = 0; i < row1; i++)
    {
        for(int j = 0; j < col2; j++)
            cout << c[i][j] << " ";
        cout << endl;
    }
    cin.get(); cin.get();
    return 0;
}