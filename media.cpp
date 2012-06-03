#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
	int N;
	double x, med;
	vector<double> v;
	med = 0;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%lf", &x);
		med += x;
		v.push_back(x);
	}
	
	double var = 0;
	med /= N;
	for (int i = 0; i < N; ++i) {
		var += (v[i] - med) * (v[i] - med);
	}
	var /= N;
	
	printf("media = %g\n", med);
	printf("var = %g\n", var);
	printf("desvio = %g\n", sqrt(var));
	return 0;
}