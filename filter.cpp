#include <vector>
#include <cmath>
#include <cstdio>
#include <map>

using namespace std;

double dist(vector<double>& x, vector<double>& y) {
    double acc = 0;
    for (int i = 0; i < x.size(); ++i) acc += (x[i] - y[i]) * (x[i] - y[i]);
   return sqrt(acc);
}

int main(){
    int N_IN = 5, N;
    scanf("%d", &N);

    vector<vector<double> > in(N);

    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N_IN; ++k){
            double x;
            scanf("%lf",&x);
            in[i].push_back(x);
        }
    }

    map<int, bool> mark;
    double eps = 0.02;

    int M = 0;
    for (int i = 0; i < N; i++)
        if (mark[i] == false) {
            M++;
            for (int j = i+1; j < N; ++j) {
                double d = dist(in[i], in[j]);
                if ( d < eps)
                    mark[j] = true;
            }
        }

    printf("%d\n", M);
    for (int i = 0; i < N; i++)
        if (mark[i] == false) {
            for (int j = 0; j < N_IN; ++j)
                printf("%e ", in[i][j]);
            printf("\n");
        }
    return 0;
}

