#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

double random(double a, double b) {
	double r = rand() / double(RAND_MAX);
	return a + r * (b - a);
}

int main()
{
	srand(time(NULL));
	int N = 5000;
	vector<double> x(N,0);
	int s = 17;
	double c = 10;
	double b = 0.1;
	double a = 0.2;
	
	printf ("%d\n", N-30-1);
	
	for (int i = 30; i < N; ++i) {
		x[i] = x[i-1] + (a * x[i-s] / (1 + pow(x[i-s],c))) - b * x[i-1] + 0.1 * random(-0.1, 0.1);
		printf("%e\n", x[i]);
	}
	
	return 0;
}