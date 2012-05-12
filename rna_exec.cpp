/**
1.a Tarefa de Inteligência Computacional

Equipe [gogo40]:
1.) Péricles Lopes Machado
2.) João Augusto Palmitesta Neto
3.) Paulo Ribeiro de Almeida Neto

Arquivo: rnat.cpp

Descrição: Programa que processa entrada usando a rede.

Uso: 
<prog_name> arquivo_configuração_da_rede arquivo_com_entradas
*/

#include "rna.h"

int main(int argc, char** argv)
{
	argc--; argv++;
	if(argc!=2){
		printf("Uso:  %s <arquivo_configuracao_da_rede> <arquivo_com_entradas> ",argv[-1]);
		return 0;
	}
	
	RNA r;
	
	r.load(argv[0]);
	
	vector<double> in(r.getNIn());
	vector<double> out(r.getNOut());
	int N;
	
	FILE* f=fopen(argv[1],"r");
	FILE* fsol=fopen("sol.dat","w+");
	FILE* fout=fopen("out.dat","w+");
	if(!f){
		fprintf(stderr,"Falha ao abrir arquivo %s!!!\n",argv[1]);
		return 3;
	}
	
	fscanf(f,"%d",&N);
	double err_acc = 0;

	for(int i=0;i<N;i++){
		for(int k=0;k<in.size();k++) fscanf(f,"%lf",&in[k]);
		r.g(in);
		for(int m=0;m<r.cam[r.NC-1].size();m++){ 
			double x; 
			printf("%.9lf",r.G[r.cam[r.NC-1][m]]); 
			fscanf(f,"%lf",&x);
			printf("(%.9lf) ",x);
			fprintf(fsol,"%d %e\n", i, x);
			fprintf(fout,"%d %e\n", i, r.G[r.cam[r.NC-1][m]]);
			err_acc += fabs(x-r.G[r.cam[r.NC-1][m]])/
			((fabs(x)+1)*r.cam[r.NC-1].size());
		}
		printf("\n");
	}
	printf("err = %lf\n", 100 * err_acc/N);
	fclose(fsol);
	fclose(fout);
	fclose(f);
	
	return 0;
}
