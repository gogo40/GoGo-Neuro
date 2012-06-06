#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include <cmath>
#include <cstring>
#include "utils.h"

using namespace std;
using namespace GOGONEURO;

#include "rbf.h"

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

double dist(const vectorD& x, const vectorD& y) {
	double d = 0;
	for (int i = 0; i < x.size(); ++i) d+= (x[i] - y[i]) * (x[i] - y[i]);
	return d;
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void saveRBF(const char* net_name, int& n_neu, int& n_in, int& n_out, matrixD& W, matrixD& X, vector<double>& beta) {
	FILE* fout = fopen(net_name, "w+");

	fprintf(fout, "%d %d\n", W.size(), W[0].size());

	for (int i = 0; i < W.size(); ++i) {
		for (int j = 0; j < W[i].size(); ++j) {
			fprintf(fout, "%e ", W[i][j]);
		}
		fprintf(fout, "\n");
	}
	for (int i = 0; i < n_neu; ++i) {
		for (int j = 0; j < n_in; ++j)
			fprintf(fout, "%e ", X[i][j]);
		fprintf(fout,"\n");
	}

	for (int i = 0; i < n_neu; ++i) fprintf(fout, "%e ", beta[i]);
	fprintf(fout,"\n");

	fclose(fout);
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

bool loadRBF(const char* net_name, int& n_neu, int& n_in, int& n_out, matrixD& W, matrixD& C, vector<double>& beta) {
	FILE* frna = fopen(net_name, "r");

	if (!frna) return false;

	fscanf(frna, "%d%d", &n_neu, &n_out);
	
	for (int i = 0; i < n_neu; ++i) {
		for (int j = 0; j < n_out; ++j) {
			fscanf(frna, "%lf", &W[i][j]);
		}
	}

	for (int i = 0; i < n_neu; ++i) {
		for (int j = 0; j < n_in; ++j){
			fscanf(frna, "%lf", &C[i][j]);
		}
	}

	for (int i = 0; i < n_neu; ++i) fscanf(frna, "%lf",&beta[i]);
	
	fclose(frna);

	return true;
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

bool trainRBF(
int n_neu, int n_in, int n_out, int N,
vector<double>& beta, 
matrixD& input, matrixD& output,
matrixD& X, matrixD& W) {

	matrixD b(N, n_out), g(N, n_neu), gt(n_neu, N);

	matrixD ggt(n_neu,n_neu), ggtinv(n_neu, n_neu), C(n_neu, n_in), bgt(n_neu, n_out);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < n_neu; ++j) {
			g[i][j] = exp(-beta[j] * dist(input[i], X[j]));
		}
		for (int k = 0; k < n_out; ++k) b[i][k] = output[i][k];
	}


	gt = trans(g);
	ggt = gt * g;
	bgt = gt * b;


	bool st;

	ggtinv = inv(ggt, st);

	if (!st) return false;

	W = ggtinv * bgt;

	return st;
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

double runRBF(
int N, int n_out, int n_neu,
matrixD& W, matrixD& input, 
matrixD& output, matrixD& C,
vector<double>& beta) {
	char buffer[100];
	double errT = 0;
	for (int i = 0; i < n_out; ++i) {
		double err = 0;

		for (int k = 0; k < N; ++k) {
			double out = 0;
			for (int j = 0; j < n_neu; ++j) {
				out += W[j][i] * exp (-beta[j] * dist(input[k],C[j]));
			}
			err += (out - output[k][i]) * (out - output[k][i]);
		}

		errT += 0.5 * err / N;
	}
	return errT / n_out;
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void runSaveRBF(
int N, int n_out, int n_neu,
matrixD& W, matrixD& input, 
matrixD& output, matrixD& C,
vector<double>& beta) {
	char buffer[100];


	for (int i = 0; i < n_out; ++i) {
		sprintf(buffer, "f_%d.rna.out", i);
		FILE* f = fopen(buffer, "w+");

		sprintf(buffer, "f_%d.rna.sol", i);
		FILE* fs = fopen(buffer, "w+");

		double err = 0;

		for (int k = 0; k < N; ++k) {
			double out = 0;
			for (int j = 0; j < n_neu; ++j) {
				out += W[j][i] * exp (-beta[j] * dist(input[k],C[j]));
			}
			fprintf(f, "%e\n", out);
			fprintf(fs,"%e\n", output[k][i]);
			err += fabs(out - output[k][i]) * fabs(out - output[k][i]);
		}

		printf("err = %e\n", 0.5 * err / N);

		fclose(f);
		fclose(fs);
	}
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void loadData(
const char* input_name,
const char* output_name,
const char* center_name,
matrixD& input, matrixD& output, 
matrixD& center, int& N, int& Ncenter,
int& n_in, int& n_out) {

	FILE* fin = fopen(input_name, "r");
	
	fscanf(fin, "%d", &N);

	input = matrixD(N, n_in);
	output = matrixD(N, n_out);

	for (int i = 0; i < N; ++i) {
		for (int k = 0; k < n_in; ++k) {
			double x;
			fscanf(fin, "%lf", &x);
			input[i][k] = x;
		}

		for (int k = 0; k < n_out; ++k) {
			double x;
			fscanf(fin, "%lf", &x);
			output[i][k] = x;
		}
	}

	fclose(fin);

	FILE* fcin = fopen(center_name, "r");
	
	fscanf(fcin, "%d", &Ncenter);

	center = matrixD(Ncenter, n_in);

	for (int i = 0; i < Ncenter; ++i) {
		for (int k = 0; k < n_in; ++k) {
			double x;
			fscanf(fcin, "%lf", &x);
			center[i][k] = x;		
		}
	}

	fclose(fcin);
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

