#include <iostream>
#include "equation.cpp"
#include "calculator.cpp"

int main()
{
    std::cout << "Hello World!\n";
    Matrix A(5);
    A.di = {1,2,3,4,5};
    A.ggl = { 0,1,2,3,4 };
    A.ggu = { 0,1,2,3,4 };
    vector<double>b = { 1,2,3,4,5 };
    Solver S(A, b);
    S.A.Print();
    S.LU();
    S.A.Print();
}


