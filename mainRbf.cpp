#include "rbf.h"

int main(int argc, char** argv) {

	if (argc != 9) {
		fprintf(stderr, "%s <treino ou execucao?> <input_data> <n_in>"
			" <n_out> <n_neu> <beta> <output data> <center data>\n", argv[0]);
		return 0;
	}

	srand(time(NULL));

	int istrain, n_in, n_out, n_neu;
	double mbeta;
	char *input_name, *output_name, *center_name;

	sscanf(argv[1], "%d", &istrain);
	input_name = argv[2];
	sscanf(argv[3], "%d", &n_in);
	sscanf(argv[4], "%d", &n_out);
	sscanf(argv[5], "%d", &n_neu);
	sscanf(argv[6], "%lf", &mbeta);
	output_name = argv[7];
	center_name = argv[8];

	matrixD input, output, center;
	int Ncenter, N;

	loadData(input_name, output_name, center_name,
	input, output, center, N, Ncenter, n_in, n_out);

	matrixD W(n_neu, n_out);
	vector<double> beta(n_neu, mbeta);
	matrixD X(n_neu, n_in), C(n_neu, n_in);

	if (istrain) {
		map<int, bool> mark;

		for (int i = 0; i < n_neu; ++i) {
			int q = rand() % (Ncenter);

			while (mark[q]) q = (q+1)% (Ncenter);
			//q = i;

			mark[q] = true;

			for (int k = 0; k < n_in; ++k) X[i][k] = center[q][k];
		}

		//if (!trainRBF(n_neu, n_in, n_out, N, beta, input, output, X, W)) {
		//	fprintf(stderr, "Falha ao inverter matriz W!!!\n");
	//		return 0;		
	// 		}


/*
bool deRBF(
double pT,
double pV,
double betaini,
double betafim,
double CR,
int gen_max,
int NP,
double F,
int n_neu, int n_in, int n_out, int N,
vector<double>& beta,
matrixD& center,
matrixD& input, matrixD& output,
matrixD& X, matrixD& W)
*/

		deRBF(0.9, 0.1, 0.0001, 100.0, 0.9, 
		10000, 20, 0.5, n_neu, n_in, n_out, N, beta,
		center, input, output, X, W);		

		saveRBF(output_name, n_neu, n_in, n_out, W, X, beta);

	} else {
		if (!loadRBF(output_name, n_neu, n_in, n_out, W, C, beta)) {
			fprintf(stderr, "Falha na leitura do arquivo %s\n", output_name);
			return 0;		
		}

		printf("err = %e\n", runRBF(N, n_out, n_neu, W, input, output, C, beta));
		runSaveRBF(N, n_out, n_neu, W, input, output, C, beta);

	}

	return 0;
}

