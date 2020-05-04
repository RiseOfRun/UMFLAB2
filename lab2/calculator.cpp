#pragma once
#include <stdio.h>
#include "equation.cpp"

class Solver
{
public:
	vector<double> x;
	Matrix A;
	vector<double>b;

	Solver(Matrix& A, vector<double>& b)
	{
		this->A = A;
		this->b = b;
	}

	~Solver() {}
	void LU()
	{
		int n = b.size();
		for (int i = 0; i < n; i++)
		{
			double sumL;
			double sumU;
			/*for (int j = i - 1, jl = 0; j < i; j++, jl++)
			{*/
			int j = i - 1;
				if (j < 0) continue;
				sumL = 0;
				sumU = 0;
				A.ggl[i] = A.ggl[i] / A.di[i - 1];
				A.di[i] = A.di[i] - A.ggl[i] * A.ggu[i];
				//for (int k = 0, ku = i - j; k < jl; k++, ku++)
				//{

				//	//sumL = L(i, k)*U(k, j);
				//	sumL += A.ggl[i] * A.ggu[j];
				//	//sumU = L(j, k)*U(k, i);
				//	sumU += A.ggl[j] * A.ggu[i];
				//}

				////U(j, i) = A(j, i) - sumU;


				//	//L(i, j) = (A(i, j) - sumL) / U(j, j);
				//if (i != j)
				//{
				//	A.ggu[i] = A.ggu[i] - sumU;
				//	A.ggl[i] = (A.ggl[i] - sumL) / A.di[j];
				//}
			//}

		}

	}
};
