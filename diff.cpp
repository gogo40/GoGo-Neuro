#include <cstdio>

using namespace std;

int main(int argc, char** argv) {
	FILE* f1 = fopen(argv[1], "r");
	FILE* f2 = fopen(argv[2], "r");
	FILE* fr = fopen(argv[3], "w+");
	int N, M;
	double x, y;
	
	fscanf(f1, "%d", &N);
	fscanf(f2, "%d", &M);
	fprintf(fr, "%d\n", N);
	for (int i = 0; i < N; ++i) {
		fscanf(f1, "%lf", &x);
		fscanf(f2, "%lf", &y);
		
		fprintf(fr, "%e\n", x-y);
	}
	
	fclose(f1); fclose(f2); fclose(fr);
	return 0;
}
