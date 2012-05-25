#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

int main(int argc, char** argv) {
    if (argc != 8) {
        fprintf(stderr,"Usage: %s <treino?> <arquivo de treino ou arquivo de teste?> <numero de entradas> <numero de neuronios>"
                "<numero de saidas> <nome da rede> <raio>\n", argv[0]);
        return 0;
    }

    srand(time(NULL));

    int n_in, n_out;
    int n_neu;
    char* filename;
    char* outname;
    int is_train;
    double raio;

    sscanf(argv[1], "%d", &is_train);

    filename = argv[2];

    sscanf(argv[3], "%d", &n_in);
    sscanf(argv[4], "%d", &n_neu);
    sscanf(argv[5], "%d", &n_out);

    outname = argv[6];

    sscanf(argv[7], "%lf", &raio);

    vector<vector<double> > W(n_in);

    for (int i = 0; i < W.size(); ++i)
        W[i].resize(n_neu);

    vector<vector<double> > m(n_neu);

    for (int i = 0; i < m.size(); ++i)
        m[i].resize(n_out);

    map<int, bool> marked;

    FILE* fin = fopen(filename, "r");
    int N;

    fscanf(fin, "%d", &N);

    vector<vector<double> > input(N), output(N);

    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < n_in; ++k) {
            double x;
            fscanf(fin, "%lf", &x);
            input[i].push_back(x);
        }

        for (int k = 0; k < n_out; ++k) {
            double y;
            fscanf(fin, "%lf", &y);
            output[i].push_back(y);
        }
    }

    fclose(fin);

    if (is_train) {


        for (int q = 0; q < n_neu; ++q) {
            int q1;
            while (true) {
                q1 = rand() % N;
                if (!marked[q1]) {
                    marked[q1] = true;
                    break;
                }
            }

            for (int k = 0; k < n_in; ++k) {
                W[k][q] = input[q][k];
            }

            for (int k = 0; k < n_out; ++k) {
                m[q][k] = output[q][k];
            }
        }

        FILE* fout = fopen(outname, "w+");

        for (int q = 0; q < n_neu; ++q){
            for (int k = 0; k < n_in; ++k) {
                fprintf(fout, "%e ", W[k][q]);
            }

            for (int k = 0; k < n_out; ++k) {
                fprintf(fout, "%e ", m[q][k]);
            }

            fprintf(fout, "\n");
        }
        fclose(fout);
    } else {
        FILE* fout = fopen(outname, "r");

        for (int k = 0; k < n_in; ++k) W[k].resize(n_neu);
        for (int k = 0; k < n_neu; ++k) m[k].resize(n_out);

        for (int q = 0; q < n_neu; ++q){
            for (int k = 0; k < n_in; ++k) {
                fscanf(fout, "%lf", &W[k][q]);
            }

            for (int k = 0; k < n_out; ++k) {
                double y;
                fscanf(fout, "%lf", &y);
                m[q][k] = y;
            }
        }
        fclose(fout);

        vector<double> u(n_neu), o(n_out);

        FILE* fdes = fopen("sol.dat", "w+");
        FILE* fnet = fopen("out.dat", "w+");

        double err = 0, errT = 0;
        for (int i = 0; i < N; ++i) {

            for (int k = 0; k < n_neu; ++k) u[k] = 0;

            for (int k = 0; k < n_out; ++k) o[k] = 0;

            for (int k = 0; k < n_in; k++)
                for (int n = 0; n < n_neu; ++n) {
                    u[n] += (input[i][k] - W[k][n]) * (input[i][k] - W[k][n]);
                }
            for (int n = 0; n < n_neu; ++n) {
                u[n] /= 2 * raio * raio;
                u[n] = exp(-u[n]);
            }

            err = 0;
            for (int k = 0; k < n_out; ++k) {
                for (int n = 0; n < n_neu; ++n){
                    o[k] += m[n][k] * u[n];
                }
                err += (o[k] - output[i][k]) * (o[k] - output[i][k]);
                fprintf(fnet, "%e ", o[k]);
                fprintf(fdes, "%e ", output[i][k]);
            }
            fprintf(fnet, "\n");
            fprintf(fdes, "\n");

            errT += err / n_out;
        }

        printf("err = %e\n", 0.5 * errT);

        fclose(fdes);
        fclose(fnet);
    }

    return 0;
}

