#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>

using namespace std;

void clear (double **arr, int n){
    for (int i = 0; i < n; i++)
    {
        delete[] arr[i];
    }
    delete [] arr;

}

double** clone(double **arr, int n){
    double **newArr = new double*[n];
    for (int row = 0; row < n; row++)
    {
        newArr[row] = new double [n];
        for (int col = 0; col < n; col++)
        {
            newArr[row][col]=arr[row][col];
        }

    }
    return newArr;
}

void show (double **matrix, int n){
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            printf("%lf\t", matrix[row][col]);
        }
        printf("\n");

    }
    printf("\n");
}
double** maxtix_multi(double **A, double **B, int n){
    double **result = new double *[n];
    for (int row = 0; row < n; row++)
    {
        result[row]=new double[n];
        for (int col = 0; col < n; col++)
        {
            result[row][col] =  0;
        }

    }
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            for (int j = 0; j < n; j++)
            {
                result[row][col]+=A[row][j]*B[j][col];
            }
        }
        
    }
    return result;
}
void scalar_multi(double **m, int n, double a){
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            m[row][col] *=a;
        }
    }

}
void sum(double **A,double **B, int n){
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            A[row][col]+=B[row][col];
        }
    }
}
double det(double **maxtix, int n){
    double **B = clone(maxtix, n);
    for (int step = 0; step < n; step++)
    {
        for (int row = step+1; row < n; row++)
        {
            double coeff = -B[row][step]/B[step][step];
            for (int col = step; col < n; col++)
            {
                B[row][col]+=B[step][col]*coeff;
            }

        }

    }
    double Det= 1;
    for (int i = 0; i < n; i++)
    {
        Det *= B[i][i];
    }
    clear(B,n);
    return Det;

}
int main()
{
 int n;
 scanf("%d", &n);
 double **A=new double*[n];
 for (int row = 0; row < n; row++)
 {
     A[row] = new double[n];
     for (int col = 0; col < n; col++)
     {
        scanf("%lf", &A[row][col]);
     }

 }
 double N1=0,Ninf=0;
 double **A0=clone(A,n);
 for (size_t row = 0; row < n; row++)
 {
     double colsum=0,rowsum=0;
    for (size_t col = 0; col < n; col++)
    {
        rowsum+=fabs(A0[row][col]);
        colsum+=fabs(A0[col][row]);
    }
    N1 = max(colsum,N1);
    Ninf=max(rowsum,Ninf);
 }
 for(size_t row = 0;row < n -1;row++){
     for(size_t col = row +1;col<n;col++)
        swap(A0[col][row],A0[row][col]);
 }
 scalar_multi(A0,n,(1/(N1*Ninf)));
 double **E2 = new double*[n];
 for(int row = 0;row<n;row++)
 {
     E2[row]=new double[n];
     for (int col = 0; col < n; col++)
     {
         if(row==col)
            E2[row][col]=2;
        else
            E2[row][col]=0;
     }
 }
 double **inv = clone(A0,n);
 double EPS = 0.001;
 if(det(A,n)!=0){
     while (fabs(det(maxtix_multi(A,inv,n),n)-1)>=EPS)
     {
         double **prev = clone(inv,n);
         inv = maxtix_multi(A,prev,n);
         scalar_multi(inv,n,-1);
         sum(inv,E2,n);
         inv=maxtix_multi(prev,inv,n);
         clear(prev,n);
     }
     show(inv,n);
 }
 else{
     printf("inposible\n");
 }
 clear(A,n);
 clear(E2,n);
 return 0;
}
