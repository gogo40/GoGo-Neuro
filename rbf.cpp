#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include <cmath>
#include <cstring>
#include "utils.h"


#include "utils.cpp"

using namespace std;
using namespace GOGONEURO;

double dist(const vectorD& x, const vectorD& y) {
	double d = 0;
	for (int i = 0; i < x.size(); ++i) d+= (x[i] - y[i]) * (x[i] - y[i]);
	return d;
}

int main(int argc, char** argv) {

	if (argc != 8) {
		fprintf(stderr, "%s <treino ou execucao?> <input_data> <n_in> <n_out> <n_neu> <beta> <output data>\n", argv[0]);
		return 0;
	}

	srand(time(NULL));

	int istrain;
	int n_in;
	int n_out;
	int n_neu;
	double beta;
	char* input_name;
	char* output_name;

	sscanf(argv[1], "%d", &istrain);

	input_name = argv[2];

	sscanf(argv[3], "%d", &n_in);
	sscanf(argv[4], "%d", &n_out);
	sscanf(argv[5], "%d", &n_neu);
	sscanf(argv[6], "%lf", &beta);

	output_name = argv[7];

	FILE* fin = fopen(input_name, "r");

	int N;

	fscanf(fin, "%d", &N);

	matrixD input(N, n_in), output(N, n_out);

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

	if (istrain) N--;

	matrixD W(n_neu, n_out), b(N, n_out), g(N, n_neu), gt(n_neu, N);

	matrixD X(n_neu, n_in), ggt(n_neu,n_neu), ggtinv(n_neu, n_neu), C(n_neu, n_in), bgt(n_neu, n_out);

	if (istrain) {
		map<int, bool> mark;

		for (int i = 0; i < n_neu; ++i) {
			int q = rand() % (N-1);

			//while (mark[q]) q = (q+1)% (N-1);
			q = i;

			mark[q] = true;

			for (int k = 0; k < n_in; ++k) X[i][k] = input[q][k];
		}

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < n_neu; ++j) {
				g[i][j] = exp(-beta * dist(input[i], X[j]));
			}
			for (int k = 0; k < n_out; ++k) b[i][k] = output[i][k];
		}


		gt = trans(g);
		ggt = gt * g;
		bgt = gt * b;


		bool st;
		ggtinv = inv(ggt, st);

		if (!st) cerr << "Falha na inversa!!!" << endl;

		W = ggtinv * bgt;

		FILE* fout = fopen(output_name, "w+");

		fprintf(fout, "%d %d %e\n", W.size(), W[0].size(), beta);

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

		fclose(fout);

	} else {
		FILE* frna = fopen(output_name, "r");

		fscanf(frna, "%d%d%lf", &n_neu, &n_out, &beta);
		for (int i = 0; i < n_neu; ++i) {
			for (int j = 0; j < n_out; ++j) {
				fscanf(frna, "%lf", &W[i][j]);
				printf("%e ", W[i][j]);
			}
			printf("\n");
		}

		printf("\n");
		for (int i = 0; i < n_neu; ++i) {
			for (int j = 0; j < n_in; ++j){
				fscanf(frna, "%lf", &C[i][j]);
				printf("%e ", C[i][j]);
			}
			printf("\n");
		}
		fclose(frna);

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
					out += W[j][i] * exp (-beta * dist(input[k],C[j]));
				}
				fprintf(f, "%e\n", out);
				fprintf(fs,"%e\n", output[k][i]);
				err += fabs(out - output[k][i]);
			}

			fprintf(stderr, "%e\n", err);

			fclose(f);
			fclose(fs);
		}

	}

	return 0;
}

