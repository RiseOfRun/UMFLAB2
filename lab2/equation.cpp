#pragma once
#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<double>> Mat2x2;

class Matrix {
public:
	vector<double> ggl;//нижняя диагональ
	vector<double> ggu;//верхняя диагональ
	vector<double> di;//диагональная диагональ

	void Print()
	{
		int n = di.size();
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				if (j==i)
				{
					printf("(%lf) ",di[i]);
					continue;
				}
				if (j==i-1)
				{
					printf("%lf ", ggl[i]);
					continue;
				}

				if (j==i+1)
				{
					printf("%lf ", ggu[j]);
					continue;
				}

				printf("0 ");
			}
			printf("\n");
		}
		printf("\n");
		printf("\n");

	}
	Matrix()
	{
	}
	Matrix(int n) {
		ggl = vector<double>(n);
		ggu = vector<double>(n);
		di = vector<double>(n);
	}


};

class Net {
public:
	vector<double> xNodes; //узлы
	vector<double> tNodes;
	int nx = 0, nt = 0; // количество узлов

	void BuildTnet(double xstart, double xend, int k)
	{
		double h = (xend - xstart) / k;
		nx = k + 1;
		for (int i = 0; i < nx; i++)
			tNodes.push_back(xstart + i * h);
	}

	void BuildXnet(double xstart, double xend, int k)
	{
		double h = (xend - xstart) / k;
		nx = k + 1;
		for (int i = 0; i < nx; i++)
			xNodes.push_back(xstart + i * h);
	}

	Net() //для неравномерной сетки
	{

	}
};

class Equation {

	Net net;
	double sigma = 4; 
	vector<vector<double>> q;

	double f(double x, double t) {
		return 3;
	}

	double u(double x, double t) {
		return 2;
	}


	double lambda(double du, double x) {
		return 1;
	}

	

public:
	Matrix A;

	Equation(Net net) {
		Matrix A(net.xNodes.size());
		this->net = net;
		q = vector<vector<double>>(net.tNodes.size(), vector<double>(net.xNodes.size()));
	}

	void eq(int z) {
		
	}

	void Start()
	{
		if (sigma==0)
		{
			BuildGlobal(0);
			findq(0);
		}
		else
		{
			for (size_t i = 1; i < net.tNodes.size(); i++)
			{
				BuildGlobal(i);
				findq(i);
			}
		}
	}

	void findq(int i)
	{

	}


	Mat2x2 BuildLocal(int i, int j, int tn) {
		Mat2x2 G;
		Mat2x2 M;
		G = BuildG(i, j, net.tNodes[tn]);
		if (sigma !=0)
		{
			M = BuildM(net.tNodes[tn] - net.tNodes[tn - 1], i, j);
		}
		else
		{
			M = {
				{0,0},
				{0,0}
			};
		}
		
		Mat2x2 localA(2);
		for (size_t i = 0; i < 2; i++)
		{
			localA[i].push_back(G[i][0] + M[i][0]);
			localA[i].push_back(G[i][1] + M[i][1]);
		}
		return localA;
	}

	void ToGlobal(Mat2x2 & localA,int i=0,int j=1) {
		A.di[i] += localA[0][0];
		A.di[j] += localA[1][1];
		A.ggu[i] = localA[2][1];
		A.ggl[j] = localA[1][2];


		/*if (A.di.size == 0)
			A.di.push_back(localA[0][0]);
		else 
			A.di[A.di.size - 1] += localA[0][0];
		A.ggl.push_back[localA[1][0]];
		A.ggu.push_back[localA[0][1]];
		A.di.push_back(localA[1][1]);*/
	}

	void BuildGlobal(int tn)
	{
		int n = net.xNodes.size();
		A = Matrix(n);
		b = vector<double>(n);
		double dt = net.tNodes[tn] - net.tNodes[tn - 1];
		double t = net.tNodes[tn];

		for (size_t i = 0; i < net.nx-1; i++)
		{
			Mat2x2 Al = BuildLocal(i, i + 1, tn);
			ToGlobal(Al, i, i + 1);
			BuildB(i, i+1, tn);
		}
	}

	void BuildB(int i, int j, int tn)
	{
		double dt = net.tNodes[tn] - net.tNodes[tn - 1];
		double t = net.tNodes[tn];
		double x1 = net.xNodes[i];
		double x2 = net.xNodes[j];
		double q1 = q[tn - 1][i];
		double q2 = q[tn - 2][j];
		double h = x2-x1;

		b[i] += h / 6 * (2*f(x1, t) + f(x2,t));
		b[j] += h / 6 * (f(x1, t) + 2 * f(x2, t));

		if (sigma!=0)
		{
			b[i] += sigma * h / 6 / dt * (2 * q1 + q2);
			b[j] += sigma * h / 6 / dt * (q1 + 2 * q2);
		}
		
	}

private:
	vector<double> b;
	
	vector<vector<double>> BuildG(int i, int j,int tn) {
		double t = net.tNodes[tn];
		double x1 = net.xNodes[i];
		double x2 = net.xNodes[j];
		double h = x2 - x1;
		double multix = (lambda(-q[tn][i] / h, t) + lambda(q[tn][i] / h, t)) / 2 / h;
		vector<vector<double>> G = {
		{multix,
			-multix},
		{-multix,
			multix}
		};
		return G;
	}

	vector<vector<double>> BuildM(double dt, int i, int j) {
		double x1 = net.xNodes[i];
		double x2 = net.xNodes[j];
		double h = x2 - x1;
		double multix = sigma / dt / 6 * h;
		vector<vector<double>> M = {
			{multix * 2,multix},
			{multix,2 * multix}
		};
	}

};