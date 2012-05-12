/**
1.a Tarefa de Inteligência Computacional

Equipe [gogo40]:
1.) Péricles Lopes Machado
2.) João Augusto Palmitesta Neto
3.) Paulo Ribeiro de Almeida Neto

Arquivo: misc.cpp

Descrição: Implementação de funções genéricas do código.

*/

#include "rna.h"

void RNA::save(const char* fn)
{
	FILE* f=fopen(fn,"w");
	if(!f){
		fprintf(stderr,"Falha ao abrir %s!\n",fn);
		exit(3);
	}
	
	fprintf(f,"%d %d %d %d %lf\n",NC,nIn,nOut,nNeu,TA);
	for(int i=1;i<=nNeu;i++){
		fprintf(f,"%d %d %d %lf",rede[i].id,rede[i].id_fa,rede[i].c,W[0][i]);
		fprintf(f," %lf\n",rede[i].p); 
	}
	
	
	//Imprime sinapses
	for(int i=0;i<NC;i++){
		for(int m=0;m<cam[i].size();m++){
			int k=cam[i][m], u;
			double w;
			for(int n=1;n<rede[k].conn.size();n++){
				u=rede[k].conn[n];
				w=W[u][k];
				fprintf(f,"%d %d %lf\n",u,k,w);
			}
		}
	}
	
	fprintf(f,"0 0 0\n");
	fclose(f);
}

void RNA::load(const char* fn)//Carrega uma rede usando o arquivo de configuração f
{
	FILE* f=fopen(fn,"r");
	if(!f){
		fprintf(stderr,"Falha ao abrir %s!\n",fn);
		exit(3);
	}
	
	//FORMATO DO ARQUIVO
	//int NC;//Numero de camadas da rede
	//int nIn;//Numero de entradas da rede
	//int nOut;//Numero de saidas da rede
	//int nNeu;//Numero de neuronios da rede
	//double TA;//Taxa de aprendizado
	fscanf(f,"%d%d%d%d%lf",&NC,&nIn,&nOut,&nNeu,&TA);
	
	W.clear(); W.resize(nIn+nNeu+2);
	cam.clear(); cam.resize(NC);
	rede.clear(); rede.resize(nNeu+1);
	G.clear(); G.resize(nIn+nNeu+2);
	Gd.clear(); Gd.resize(nIn+nNeu+2);
		
	for(int i=0;i<nIn+nNeu+2;i++) W[i].resize(nIn+nNeu+2);
	
	//A seguir leem-se nNeu linhas descrevendo os neuronios
	
	for(int i=0;i<nNeu;i++){
		//Um neuronio tem o formato
		//id_neuronio  id_funcao_de_ativacao camada_neuronio bias p 
		int id, ida, c;
		double p, bias;
		
		fscanf(f,"%d%d%d%lf",&id,&ida,&c,&bias);
		fscanf(f,"%lf",&p); 
		
		rede[id].conn.clear();
		rede[id].dest.clear();
		rede[id]=Neuronio(id,ida,p,c);
		rede[id].conn.push_back(0);
		
		W[0][id]=bias;
		cam[c].push_back(id);
	}
	
	int u, v;
	double w;
	
	//Agora leêm-se as sinapses
	//A sinapse 0 0 0 indica fim de arquivo
	
	
	for(;;){
		//Formato u-->v com peso w
		fscanf(f,"%d%d%lf",&u,&v,&w);
		if(!u) break;
		if(v<=nNeu) rede[v].newConn(u);
		if(u<=nNeu) rede[u].newDest(v);
		W[u][v]=w;
	}
	
	fclose(f);
}



