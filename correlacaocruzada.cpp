#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;

int main(int argc, char** argv)
{
	char fname[200];
	int N, Nt = 1;
	
	int smax = 3000;// atraso maximo
	
	sscanf(argv[1], "%d", &Nt);
	sscanf(argv[2], "%d", &smax);
	
	vector<double>* fs = new vector<double>(smax + 1, 0.0);
	
	for (int t = 1; t <= Nt; ++t) {
		sprintf(fname, "r.%d.dat", t);
		FILE* fin = fopen(fname, "r");
		
		fscanf(fin, "%d", &N);
		
		
		vector<double>* f = new vector<double>(N);
		
		for (int i = 0; i < N; ++i) {
			double x;
			fscanf(fin, "%lf", &x);
			f->at(i) = x;
		}
		
		
		for (int s = 0; s <= smax; ++s) {
			for (int k = 0; k < N - s; ++k) {
				fs->at(s) = f->at(k) * f->at(k + s);
			}
		}
		
		f->clear();
		
		delete f;
		if (t % 20 == 0) fprintf(stderr, "t=%d\n", t);
		fclose(fin);
	}
	
	printf("%d\n", smax+1);
	for(int i = 0; i <= smax; ++i) printf("%e\n", fs->at(i) / Nt);
		
	delete fs;
	
	return 0;
}
