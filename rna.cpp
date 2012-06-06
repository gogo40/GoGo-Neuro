/**
1.a Tarefa de Inteligência Computacional

Equipe [gogo40]:
1.) Péricles Lopes Machado
2.) João Augusto Palmitesta Neto
3.) Paulo Ribeiro de Almeida Neto

Arquivo: misc.cpp

Descrição: Implementação de funções e metodos relacionadas a rede neural.

*/

#include "rna.h"

#define INF 9999999

void RNA::g(vector<double>& in){
	
	for(unsigned int i=0;i<=nNeu;i++) G[i]=0;
	for(unsigned int i=0;i<in.size();i++) G[nNeu+1+i]=in[i];
	G[0]=1;
	
	for(int i=0;i<NC;i++)
		for(unsigned int j=0;j<cam[i].size();j++)
			G[cam[i][j]]=rede[cam[i][j]].g(G,W);
}

void RNA::gd(vector<double>& in){
	
	for(unsigned int i=0;i<=nNeu;i++) Gd[i]=0;
	for(unsigned int i=0;i<in.size();i++) Gd[nNeu+1+i]=in[i];
	Gd[0]=1;
	
	for(int i=0;i<NC;i++)
		for(unsigned int j=0;j<cam[i].size();j++)
			Gd[cam[i][j]]=rede[cam[i][j]].gd(Gd,W);
}


//Algoritmo usado: backpropagation
void RNA::treina(const char* fn, const char* fout, bool isBatch, bool isNature)
{
	FILE* f=fopen(fn,"r");
	FILE* flog=fopen("treino.log","w+");

	if(!f){
		fprintf(stderr,"Falha ao abrir %s!\n",fn);
		exit(3);
	}
	
	int N;
	fscanf(f,"%d",&N);
	
	vector<vector<double> >  Xin(N);
	vector<vector<double> >  d(N);//Saida desejada
	
	printf("Carregando banco de treinamento...\n");
	for(int i=0;i<N;i++){
		Xin[i].resize(nIn); d[i].resize(nOut); 
		for(int j=0;j<nIn;j++) fscanf(f,"%lf",&Xin[i][j]);
		for(int j=0;j<nOut;j++) fscanf(f,"%lf",&d[i][j]);
	}
	
	int NI;
	printf("Executando treinamento...\n");
	fscanf(f,"%d",&NI);
	fclose(f);
	
	vector<double> e(nNeu+1);
	vector<double> delta(nNeu+1);
	vector<vector<double> > dW;
 	vector<double> err_ant(nOut);

	vector<vector<double> > wt1, wt;

	if(isBatch||isNature){
		dW.resize(W.size());
		wt1.resize(W.size());
		wt.resize(W.size());

		for(int i=0;i<W.size();i++){
			dW[i].resize(W[i].size());
			wt1[i].resize(W[i].size());
			wt[i].resize(W[i].size());
		}

		//for(int i=0;i<W.size();i++)
			//for(int j=0;j<W[i].size();j++)
				//W[i][j] += rand(-1, 1);
	} else {
		wt1.resize(W.size());
		wt.resize(W.size());

		for(int i=0;i<W.size();i++){
			wt1[i].resize(W[i].size());
			wt[i].resize(W[i].size());
			for (int j=0;j<W[i].size();j++)
				wt[i][j]=wt1[i][j]=0;
		}
	}

	bool isf = true;
	double TA0 = TA;
	for(int kp=0;kp<NI;kp++){
		printf("passo %d\n",kp);

		double err_acc = 0;
		double alpha = rand(0, 1) * 0.01 * TA0;

		TA = rand(0.8, 1.2) * TA0;

		if (isBatch){
			for(int i=0;i<W.size();i++)
				for(int j=0;j<W[i].size();j++)
					dW[i][j]=0;
		}

		if (isNature){
			double e0, e1;

			e0 = 0;

			for(int k=0;k<N;k++){
				g(Xin[k]);
				gd(Xin[k]);
		
				//Atualizando neuronio na ultima camada
				for(int j=0;j<nOut;j++) {
					e[cam[NC-1][j]]=d[k][j]-G[cam[NC-1][j]];
					e0 += e[cam[NC-1][j]] * e[cam[NC-1][j]];
					err_acc+= e[cam[NC-1][j]] * e[cam[NC-1][j]];
				}
			}

			e0=e0/(2);

			for(int i=1;i<W.size();i++)
				for(int j=1;j<W[i].size();j++){
					dW[i][j]=TA*rand(-10,10);
					W[i][j]+=dW[i][j];
				}

			
			e1 = 0;
			for(int k=0;k<N;k++){
				g(Xin[k]);
				gd(Xin[k]);

				//Atualizando neuronio na ultima camada
				for(int j=0;j<nOut;j++) {
					e[cam[NC-1][j]]=d[k][j]-G[cam[NC-1][j]];
					e1 += e[cam[NC-1][j]] * e[cam[NC-1][j]];
				}
			}

			e1=e1/(2);
			if(e1>e0){
				for(int i=1;i<W.size();i++)
					for(int j=1;j<W[i].size();j++){
						W[i][j]-=dW[i][j];
					}
			}

		}else{

			//Apresentando a rede a todas amostras
			for(int k=0;k<N;k++){
				g(Xin[k]);
				gd(Xin[k]);
		
				//Atualizando neuronio na ultima camada
				for(int j=0;j<nOut;j++) {
					e[cam[NC-1][j]]=d[k][j]-G[cam[NC-1][j]];
					err_acc += e[cam[NC-1][j]] * e[cam[NC-1][j]];
				}

				for(int j=0;j<nOut;j++){
					int yj, i;

					yj=cam[NC-1][j];

					delta[yj]=e[yj]*Gd[yj];//Gd[yj];

					for(int m=0;m<rede[yj].conn.size();m++){
						i=rede[yj].conn[m];
						double dw = TA*delta[yj]*G[i];
						double dwt = 0;

						if (isf) {
							alpha = 0;
							wt[i][yj] = W[i][yj];
						} else {
							wt1[i][yj] = wt[i][yj];
							wt[i][yj] = W[i][yj];
							dwt = wt[i][yj] - wt1[i][yj];
						}

						if(isBatch)dW[i][yj]+= dw;
						else W[i][yj]+= dw + alpha * dwt;
					}
				}
		
				//Atualizando neuronios nas camadas ocultas
				for(int l=NC-2;l>-1;l--){
		
					for(int j=0;j<cam[l].size();j++){
						int yj, k; 
						double w;
				
						yj=cam[l][j];

						delta[yj]=0;
						for(int m=0;m<rede[yj].dest.size();m++){
							k=rede[yj].dest[m];
							w=W[yj][k];
							delta[yj]+=delta[k]*w;
						}
						delta[yj]*=Gd[yj];//Gd[yj]

						for(int m=0;m<rede[yj].conn.size();m++){
							int i=rede[yj].conn[m];

							double dw = TA*delta[yj]*G[i];
							double dwt = 0;

							if (isf) {
								alpha = 0;
								wt[i][yj] = W[i][yj];
							} else {
								wt1[i][yj] = wt[i][yj];
								wt[i][yj] = W[i][yj];
								dwt = wt[i][yj] - wt1[i][yj];
							}

							if(isBatch)dW[i][yj]+= dw;
							else W[i][yj]+= dw + alpha * dwt;
						}
					}
				}

				if(isBatch){
					for(int i=0;i<W.size();i++)
						for(int j=0;j<W[i].size();j++)
							W[i][j]+=dW[i][j];
				}

			}
		}

		fprintf(flog, "%d %e\n", kp,err_acc*0.5);
		printf("err=%e\n", err_acc*0.5);
		isf = false;
	}
	printf("Treino efetuado!\n");
	fclose(flog);
	//Salva a rede
	save(fout);
}

