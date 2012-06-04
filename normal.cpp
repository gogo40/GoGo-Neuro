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
	
	vector<int> picosMax;
	vector<int> picosMin;
	for (int i = 0; i < N; ++i) {
		if (i > 0 and i < N - 1) {
			if ( (v[i] >= v[i-1]) and (v[i] >= v[i+1])) {
				//fprintf(stderr, "%d %e\n", i, v[i]);
				picosMax.push_back(i);
			}
			
			if ((v[i] < v[i-1]) and (v[i] < v[i+1]) ) {
				picosMin.push_back(i);
			}
		}
	}
	
	FILE* fmin, *fmax;
	
	fmin = fopen("freq_min.dat", "r");
	fmax = fopen("freq_max.dat", "r");
	
	vector<int> freqm(N+1, 0);
	vector<int> freqM(N+1, 0);
	
	if (fmin) {
		for (int i = 0; i <= N; ++i) {
			fscanf(fmin, "%d", &freqm[i]);
		}
		
		fclose(fmin);
	}
	
	if (fmax) {
		for (int i = 0; i <= N; ++i) {
			fscanf(fmax, "%d", &freqM[i]);
		}
		
		fclose(fmax);
	}
	
	double acc = 0;
	for (int i = 1; i < picosMax.size(); ++i) {
		acc += picosMax[i] - picosMax[i-1];
		freqM[picosMax[i] - picosMax[i-1]]++;
	}
	
	fprintf(stderr,"%e\n", acc / picosMax.size());
	
	acc = 0;
	for (int i = 1; i < picosMin.size(); ++i) {
		acc += picosMin[i] - picosMin[i-1];
		freqm[picosMin[i] - picosMin[i-1]]++;
	}
	
	fprintf(stderr,"%e\n", acc / picosMin.size());

	fmin = fopen("freq_min.dat", "w+");
	fmax = fopen("freq_max.dat", "w+");
	
	for (int i = 0; i <= N; ++i) {
		fprintf(fmin, "%d\n", freqm[i]);
		fprintf(fmax, "%d\n", freqM[i]);
	}
	
	fclose(fmin);
	fclose(fmax);
	
	return 0;
}

