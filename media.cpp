#include <cstdio>

using namespace std;

int main()
{
	int N;
	double x, acc;
	acc = 0;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%lf", &x);
		acc += x;
	}
	printf("%g\n", acc/N);
	return 0;
}