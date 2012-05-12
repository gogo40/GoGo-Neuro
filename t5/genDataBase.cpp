#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

double r(double xo, double x1) {
	double v = double(rand()) / RAND_MAX;
	double l = x1 - xo;
	return xo + v * l;;
}

int main() {
	srand(time(NULL));

	double yk, yk1, yk2;

	yk = yk1 = yk2 = 0;

	int N;
	FILE* f = fopen("t5.dat","w+");
	FILE* fp = fopen("plot.dat","w+");
	printf("N=");

	scanf("%d", &N);

	fprintf(f,"%d 2 1\n", N);

	double s = 0, v = 0;
	double L;

	printf("L=");
	scanf("%lf", &L);

	for (int i = 0; i < N; ++i) {

		yk = yk1 * yk1 + yk1 - 0.5 * yk2;

		//if (fabs(yk) > L) {
		//	v = (-yk) * (1+r(0, 0.1));
		//} else 
		v = 0.01 * r(-1, 1);

		yk += v;


		fprintf(f, "%lf %lf\n%lf\n", yk2, yk1, yk);
		
		yk2 = yk1;
		yk1 = yk;
		s += v;
		fprintf(fp,"%lf\n", yk);
	}

	//printf("%e\n", s/N);

	fclose(f);
	fclose(fp);

	return 0;
}



