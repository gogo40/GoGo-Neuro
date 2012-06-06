/*
g++ -O2 -o testANN testANN.cpp -lfann
*/

#include <vector>
#include <stdio.h>
#include <math.h>
#include "floatfann.h"

int main()
{
	fann_type *calc_out;
	fann_type input[2];

	struct fann *ann = fann_create_from_file("t5.net");

	int N;
	double err_acc = 0;
	double err_med = 0;

	scanf("%d%*d%*d",&N);
	FILE* f1, *f2;
	f1 = fopen("out.dat", "w+");
	f2 = fopen("sol.dat", "w+");
	double m_f = 0;
	std::vector<double> vf;

	for (int i = 0; i < N; ++i) {
		float esp;

		scanf("%f%f%f", &input[0], &input[1], &esp);
		calc_out = fann_run(ann, input);

		printf("(%f,%f) -> %f [%f]\n", input[0], input[1], calc_out[0], esp);
		fprintf(f1, "%d %f\n", i, calc_out[0]);
		fprintf(f2, "%d %f\n", i, esp);
		err_acc += fabs(esp - calc_out[0])/(1+fabs(esp));

		vf.push_back(esp);
		m_f += esp;
	}

	m_f /= N;

	for (int i = 0; i < N; ++i) {
		err_med += fabs(vf[i] - m_f)/(1+fabs(vf[i]));
	}

	printf("err = %lf\n", 100*(err_acc / N));
	printf("errM = %lf %lf\n", 100*(err_med / N), m_f);
	fann_destroy(ann);

	fclose(f1);
	fclose(f2);
	return 0;
}

