#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

int main()
{

	int N;
	
	scanf("%d", &N);
	
	int smax = 100;// atraso maximo
	
	vector<double>* f = new vector<double>(N);
	vector<double>* fs = new vector<double>(smax + 1);
	
	for (int i = 0; i < N; ++i) {
		double x;
		scanf("%lf", &x);
		f->at(i) = x;
		//printf("%e\n",x);
	}
	
	
	for (int s = 0; s <= smax; ++s) {
		fs->at(s) = 0;
		for (int k = 0; k < N - s; ++k) {
			fs->at(s) = f->at(k) * f->at(k + s);
		}
	}
	
	for(int i = 0; i <= smax; ++i) printf("%e\n", fs->at(i));
	f->clear();
	fs->clear();
	
	delete f;
	delete fs;
	return 0;
}
