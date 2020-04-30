
#include <iostream>
#include <vector>
using namespace std;

class Matrix {
public:
	vector<double> ggl;//нижняя диагональ
	vector<double> ggu;//верхняя диагональ
	vector<double> di;//диагональная диагональ
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
	vector<double> q;

	double f(double x, double t) {
		return 3;
	}

	double u(double x, double t) {
		return 2;
	}


	double lambda(double du, double x) {
		return 1;
	}

	Equation(Net net) {

	}

public:
	Matrix A;
	void eq(int z) {
		
	}

	vector<vector<double>> BuildLocal(int i, int j, int tn) {
		vector<vector<double>> G;
		vector<vector<double>> M;
		G = BuildG(i, j, net.tNodes[tn]);
		M = BuildM(net.tNodes[tn] - net.tNodes[tn - 1], i, j);
		vector<vector<double>>localA(2);
		for (size_t i = 0; i < 2; i++)
		{
			localA[i].push_back(G[i][0] + M[i][0]);
			localA[i].push_back(G[i][1] + M[i][1]);
		}
		return localA;
	}

private:
	vector<double> b;
	
	vector<vector<double>> BuildG(int i, int j,double t) {
		double x1 = net.xNodes[i];
		double x2 = net.xNodes[j];
		double h = x2 - x1;
		double multix = (lambda(-q[i] / h, t) + lambda(q[i] / h, t)) / 2 / h;
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