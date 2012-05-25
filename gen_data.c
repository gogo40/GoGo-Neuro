#include <stdio.h>
#include <vector>

using namespace std;

int main()
{
    int N_IN = 4, N;
    scanf("%d", &N);
    int M = N / (1 + N_IN);
    vector<double> x(N);

    for (int i = 0; i < N; ++i) scanf("%lf", &x[i]);

    printf ("%d\n", M);

    int k = 0;

    for (int i = 0; i < M; ++i){
        for (int j = 0; j < N_IN; ++j) {
            printf("%e ", x[k]);
            ++k;
        }
        printf("%e\n", x[k]);
        ++k;
    }
    return 0;
}
