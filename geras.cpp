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
	srand(time(NULL));
	
	int N = 5000, M;
	
	
	int s = 27;
	
	double c = 10;
	double b = 0.1;
	double a = 0.2;
	
	double rm = 0;
	
	sscanf(argv[1], "%d", &N);
	sscanf(argv[2], "%d", &M);
	
	vector<double> x(N,0);
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
	
	for (int i = mp; i < N; ++i) {
		x[i] = x[i-1] + (a * x[i-s] / (1 + pow(x[i-s],c))) - b * x[i-1] + 0.1 * random(0, 0.1);
	}
	
	vector<vector<double> > v(N - mp);
	vector<vector<double> > w;
	
	FILE* fdb = fopen("db.dat", "w+");
	fprintf(fdb, "%d\n", N - mp);
	
	for (int i = 0; i < N - mp; ++i) {
		v[i].resize(M+1);
		for (int  n = 0; n < M; ++n) {
			v[i][n] = x[i + mp - p[n]];
			fprintf(fdb, "%e ", v[i][n]);
		}
		v[i][M] = x[i + mp];
		fprintf(fdb, "%e\n", v[i][M]);
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
		for (int j = 0; j < w.size(); ++j)
			if (dist(v[i], v[j], M+1) < rm) {
				ok = false;
				break;
			}
		if (ok) w.push_back(v[i]);
	}
	
	fdb = fopen("db.f.dat", "w+");
	fprintf(fdb, "%d\n", w.size());
	for (int i = 0; i < w.size(); ++i) {
		for (int k = 0;k < w[i].size(); ++k) {
			fprintf(fdb, "%e ", w[i][k]);
		}
		fprintf(fdb,"\n");
	}
	fclose(fdb);
	
	
	return 0;
}

