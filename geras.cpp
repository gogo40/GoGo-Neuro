#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

double random(double a, double b) {
	double r = rand() / double(RAND_MAX);
	return a + r * (b - a);
}

double dist(const vector<double>& x, const vector<double>& y, int M) {
	double r = 0;
	for (int i = 0; i < M; ++i) r += (x[i] - y[i]) * (x[i] - y[i]);
	return sqrt(r);
}

int main(int argc, char** argv)
{
	if (argc == 1) {
		fprintf(stderr,"Uso\n"
			"%s <Input number> <Recorr number> [recorr param] lmb\n",
			argv[0]);
		return 0;
	}

	srand(time(NULL));
	
	int N = 5000, M;
	
	
	int s = 27;
	
	double c = 10;
	double b = 0.1;
	double a = 0.2;
	
	double rm = 0;
	
	sscanf(argv[1], "%d", &N);
	sscanf(argv[2], "%d", &M);
	
	vector<vector<double> > x(N);
	vector<int> p(M);
	
	int mp = 0;
	
	for (int i = 0; i < M; ++i) {
		int k;
		sscanf(argv[3+i], "%d", &k);
		p[i] = k;
		
		if (k > mp) mp = k;
	}
	
	double lmb, L;
	sscanf(argv[3+M], "%lf", &lmb);
	
	if(0)for (int i = mp; i < N; ++i) {
		x[i][0] = x[i-1][0] + (a * x[i-s][0] / (1 + pow(x[i-s][0],c))) - b * x[i-1][0] + 0.1 * random(0, 0.1);
	}
	else{
		scanf("%d", &N);
		for (int i = 0; i < N; ++i) x[i].resize(4);
		for (int i = 0; i < N; ++i) {
			for (int k = 0; k < 0; ++k) {			
				double va;
				scanf("%lf", &va);
			}
			for (int k = 0; k < 1; ++k) {			
				double va;
				scanf("%lf", &va);
				x[i][k] = va;
			}
		}

		for (int k = 0; k < 1; ++k) {
			double xmin = 0;
			double xmax = 0;
			for (int i = 0; i < N; ++i) {
				if (i == 0 || xmax < x[i][k]) {
					xmax = x[i][k];				
				}
				if (i == 0 || xmin > x[i][k]) {
					xmin = x[i][k];				
				}			
			}

			for (int i = 0; i < N; ++i) {
				x[i][k] = (x[i][k] - xmin) / (xmax - xmin);
			}		
		}
	}
	//return 0;
	vector<vector<double> > v(N - mp);
	vector<vector<double> > w;
	
	FILE* fdb = fopen("db.dat", "w+");
	fprintf(fdb, "%d\n", N - mp);
	
	for (int i = 0; i < N - mp; ++i) {
		v[i].resize(1*M+1);
		for (int k = 0; k < 1; ++k)
			for (int  n = 0; n < M; ++n) {
				v[i][n * 1+k] = x[i + mp - p[n]][k];
				fprintf(fdb, "%e ", v[i][n * 1+k]);
			}
		v[i][1*M] = x[i + mp][0];
		fprintf(fdb, "%e\n", v[i][1*M]);
	}
	
	fclose(fdb);
	
	L = rm = 0;
	for (int i = 0; i < v.size(); ++i) {
		for (int j = i+1; j < v.size(); ++j) {
			rm += dist(v[i], v[j], M);
			L++;
		}
	}
	
	rm /= L;
	fprintf(stderr, "r = %e\n", rm);
	rm *= lmb;
	
	fprintf(stderr, "rm = %e\n", rm);
	for (int i = 0; i < v.size(); ++i) {
		bool ok = true;
		vector<double> c(M, 0);
		double nc = 1;

		for (int k = 0; k < M; ++k) {
			c[k] = v[i][k];
		}

		for (int j = 0; j < w.size(); ++j)
			if (dist(v[i], v[j], M) < rm) {
				ok = false;
				for (int k = 0; k < M; ++k) {
					c[k] += v[j][k];				
				}
				nc++;
			}

		if (ok)	{
			for (int k = 0; k < M; ++k) {
				c[k] /= nc;			
			}
			w.push_back(c);
		}
	}
	
	fdb = fopen("centro.dat", "w+");
	fprintf(fdb, "%d\n", w.size());
	for (int i = 0; i < w.size(); ++i) {
		for (int k = 0;k < w[i].size(); ++k) {
			fprintf(fdb, "%e ", w[i][k]);
		}
		fprintf(fdb, "\n");
	}
	fclose(fdb);
	
	
	return 0;
}

