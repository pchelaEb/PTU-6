#include<iostream>
#include<omp.h>

using namespace std;

int main(int argc, char **argv)
{
int test = 999;

#pragma omp parallel
{
#pragma omp critical
cout << "test = " << test << endl;
}
return 0;
}

