#include <cstdio>
#include <vector>

using namespace std;

int main()
{
	double xmin = 0, xmax = 0;
	int N;
	double x;
	
	scanf("%d", &N);
	
	vector<double> v(N);
	
	for (int i = 0; i < N; ++i) {
		scanf("%lf", &x);
		v[i] = x;
	}
	
	xmin = xmax = v[0];
	for (int i = 1; i < N; ++i) {
		x = v[i];
		if (x < xmin) xmin = x;
		if (x > xmax) xmax = x;
		
	}
	
	
	printf("%d\n", N);
	
	for (int i = 0; i < N; ++i) {
		v[i]=(v[i]-xmin)/(xmax-xmin);
		printf("%e\n", v[i]);
	}
	
	vector<int> picos;
	for (int i = 0; i < N; ++i) {
		if (i > 0 and i < N - 1) {
			if ( (v[i] >= v[i-1]) and (v[i] >= v[i+1])) {
				//fprintf(stderr, "%d %e\n", i, v[i]);
				picos.push_back(i);
			}
		}
	}
	
	double acc = 0;
	for (int i = 1; i < picos.size(); ++i) {
		acc += picos[i] - picos[i-1];
	}
	
	fprintf(stderr,"%e\n", acc / picos.size());
	

	
	return 0;
}

