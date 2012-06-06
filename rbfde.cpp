#include "rbf.h"


typedef vector<double> vecD;

struct Person {
/*
Um individuo é um vetor 
n_neu X n_in contendo os centros dos neurônios
e um vetor
n_neu contendo os betas
*/
	matrixD X;
	vecD beta;
	int n_in, n_neu;

	Person(int n_in=1, int n_neu=1) 
	: X(n_neu, n_in), beta(n_neu), n_in(n_in), n_neu(n_neu) {}

	void set(const matrixD& vX, const vecD& vbeta, int n_in, int n_neu) {
		X.resize(n_neu);
		beta.resize(n_neu);

		for (int i = 0; i < n_neu; ++i) {
			X[i].resize(n_in);
			for (int j = 0; j < n_in; ++j) X[i][j] = vX[i][j];
			beta[i] = vbeta[i];	
		}
	}
};

double random(double a, double b) {
	double r = double(rand()) / RAND_MAX;

	return a + r * (b - a);
}

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
{
	srand(time(NULL));

	vector<Person> pop(NP), pop2(NP);
	vector<double> custo(NP);

	double best = 1e20;
	int ibest = 0;

	int nT = static_cast<int>(input.size() * pT);
	int nV = static_cast<int>(input.size() * pV);

	matrixD inputT(nT, n_in), outputT(nT, n_out);
	matrixD inputV(nV, n_in), outputV(nV, n_out);


	for (int i = 0; i < nT and i < N; ++i) {
		inputT[i] = input[i];
		outputT[i] = output[i];
	}

	for (int i = nT, k = 0; k < nV and i < N; ++i, ++k) {
		inputV[k] = input[i];
		outputV[k] = input[i];
	}

	vecD lbeta(n_neu);
	matrixD lX(n_neu, n_in);

	for (int i = 0; i < NP; ++i) {

		for (int k = 0; k < n_neu; ++k) {
			lbeta[k] = random(betaini, betafim);		
		}

		for (int k = 0; k < n_neu; ++k) {
			int m = rand()%center.size();
			for (int n = 0; n < n_in; ++n) {			
				lX[k][n] = center[m][n] + random(-0.7, 0.7) * center[m][n];
			}		
		}

		if(!trainRBF(n_neu, n_in, n_out, nT, lbeta, inputT, outputT, lX, W)) custo[i] = 1e20;
		else custo[i] = runRBF(nV, n_out, n_neu, W, inputV, outputV, lX, beta);
		
		if (custo[i] < best) {
			best = custo[i];
			ibest = i;		
		}
		pop[i].set(lX, lbeta, n_in, n_neu);
		pop2[i].set(lX, lbeta, n_in, n_neu);
	}
	
	fprintf(stderr, "best error = %e id best = %d\n", best, ibest);
	int D = n_neu + n_neu * n_in;
	Person trial(n_in, n_neu);
		
	for (int count = 1; count < gen_max; ++count) {
		for (int i = 0; i < NP; ++i) {
			int a, b, c;

			do a = rand() % NP; while (a == i);
			do b = rand() % NP; while (b == i || b == a);
			do c = rand() % NP; while (c == i || c == a || c == b);

			int j = rand() % D;
			for (int k = 1; k <= D; ++k) {
				if (random(0,1) < CR || k == D) {
					if (j < n_neu) {
						trial.beta[j] = pop[c].beta[j] + F * (pop[a].beta[j] - pop[b].beta[j]);
					} else {
						int n = j - n_neu;
						int nneu = n / n_in;
						int nin = n % n_in;
						
						trial.X[nneu][nin] = pop[c].X[nneu][nin] +
						F * (pop[a].X[nneu][nin] - pop[b].X[nneu][nin]);
					}
				} else {
					if (j < n_neu) {
						trial.beta[j] = pop[i].beta[j];
					} else {
						int n = j - n_neu;
						int nneu = n / n_in;
						int nin = n % n_in;

						trial.X[nneu][nin] = pop[i].X[nneu][nin];
						
					}
				}
				j = (j + 1) % D;
			}

			double score;
			if(!trainRBF(n_neu, n_in, n_out, nT, trial.beta, inputT, outputT, trial.X, W)) score = 1e20;
			else score = 0.5 * (runRBF(nV, n_out, n_neu, W, inputV, outputV, trial.X, trial.beta) +
			runRBF(nT, n_out, n_neu, W, inputT, outputT, trial.X, trial.beta));

			if (score <= best) {
				best = score;
				ibest = i;
			}

			if (score <= custo[i]) {
				pop2[i] = trial;
				custo[i] = score;
			} else {
				pop2[i] = pop[i];
			}
		}

		for (int i = 0; i < NP; ++i) {
			pop[i] = pop2[i];
		}

		fprintf(stderr, " %d best error = %e id best = %d\n", count, best, ibest);

	}

	X = pop[ibest].X;
	beta = pop[ibest].beta;

	trainRBF(n_neu, n_in, n_out, nT, beta, inputT, outputT, pop[ibest].X, W);

	fprintf(stderr, "err T = %e\n", runRBF(nT, n_out, n_neu, W, inputT, outputT, X, beta));
	fprintf(stderr, "err V = %e\n", runRBF(nV, n_out, n_neu, W, inputV, outputV, X, beta));
	runSaveRBF(nV, n_out, n_neu, W, inputV, outputV, X, beta);

	return true;

}


