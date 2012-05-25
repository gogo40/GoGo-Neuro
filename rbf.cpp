#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include <cmath>
#include "utils.h"

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

	matrixD W(n_neu, n_out), b(n_neu, n_out), g(n_neu, n_neu);

	matrixD X(n_neu, n_in);

	if (istrain) {
		map<int, bool> mark;

		for (int i = 0; i < n_neu; ++i) {
			int q = rand() % N;

			while (mark[q]) q = rand() % N;

			mark[q] = true;

			for (int k = 0; k < n_in; ++k) X[i][k] = input[q][k];
			for (int k = 0; k < n_out; ++k) b[i][k] = output[q][k];
		}

		for (int i = 0; i < n_neu; ++i)
			for (int j = 0; j < n_neu; ++j) {
				g[i][j] = exp(-beta * dist(X[i], X[j]));
			}
	} else {
	}

	return 0;
}

