/**
1.a Tarefa de Inteligência Computacional

Equipe [gogo40]:
1.) Péricles Lopes Machado
2.) João Augusto Palmitesta Neto
3.) Paulo Ribeiro de Almeida Neto

Arquivo: rnat.cpp

Descrição: Programa que treina a rede.

Uso: 
<prog_name> arquivo_configuração_da_rede  banco_de_treino
*/

#include "rna.h"


int main(int argc, char** argv)
{
	argc--; argv++;
	if(argc!=4){
		printf("Uso:  %s <arquivo_configuracao_da_rede> <banco_de_treino> <tipo_treino 1 batch 0 nao> "
				"<0 padrao 1 natureza>\n",argv[-1]);
		return 0;
	}
	
	RNA r;
	
	int isBatch;
	int isNature;
	sscanf(argv[2], "%d",&isBatch);
	sscanf(argv[3], "%d",&isNature);

	printf("Carregando a rede...\n");
	r.load(argv[0]);
	printf("Carregada...\n");
	r.treina(argv[1],argv[0],(isBatch)? true: false, (isNature)?true:false);
	
	return 0;
}


