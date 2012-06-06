/**
1.a Tarefa de Inteligência Computacional

Equipe [gogo40]:
1.) Péricles Lopes Machado
2.) João Augusto Palmitesta Neto
3.) Paulo Ribeiro de Almeida Neto

Arquivo: rna.h

Descrição: Definição das classes e funções fundamentais para implementar uma Rede Neural.
Pretendemos manter essa biblioteca mais genérica possivel.

*/

#ifndef ___RNA_H
#define ___RNA_H

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include <map>

using namespace std;


/*Ponteiro de funções do tipo f(x,p), p pode não ser usado*/
typedef double (*fd)(double,double);

/*Lista de funcoes de ativação*/

//0-arco_tangente =  p*atan(x)
double atan(double x,double p);//0
double datan(double x, double p);

double linear(double x, double p);//1
double dlinear(double x, double p);

double sigmoide(double x, double p);//2
double dsigmoide(double x, double p);

double tanh(double x, double p);//3
double dtanh(double x, double p);

/**
Vetor de funções de ativação
*/
static const fd fa[]={atan,linear,sigmoide,tanh};
static const fd dfa[]={datan,dlinear,dsigmoide,dtanh};

/**
Definição de uma conexão
*/

/**
Definição de um neuronio
*/
struct Neuronio{

		int id;//Id do neuronio, id 0 é reservado para o bias!!!
		int id_fa;//Id da função de ativação
		double p;//Fatores p  para a função de ativação
		int c;//camada a que pertence o neuronio
		
		vector<int> conn;//Conexões que entram, conexão 0 é o bias
		vector<int> dest;//Conexões que saem
		
		Neuronio(int id=0, int id_fa=0, double p=0, int c=0)
		:id(id),id_fa(id_fa),p(p),c(c){ }
		
		//Calcula saida do neuronio com base nos estimulos passados ( estimulos que tem a forma [neuronio de origem, valor] ) para o neuronio
		//Passa estado atual dos neuronios
		double g(vector<double>& X, vector<vector<double> >& W);
		double gd(vector<double>& X, vector<vector<double> >& W);
		int getId(){ return id; }
		void newConn(int u){
			conn.push_back(u);
		}
		
		void newDest(int v){
			dest.push_back(v);
		}
};

/**
Definição da rede Neural
*/

class RNA{

	private:
	
		vector<Neuronio> rede;//Rede de neuronios
		
		int nIn;//Numero de entradas da rede
		int nOut;//Numero de saidas da rede
		int nNeu;//Numero de neuronios da rede
		double TA;//Taxa de aprendizado
		
	public:
	
		int NC;//Numero de camadas da rede
		vector<double> G;//Saida da rede em cada neuronio para o padrão de entrada
		vector<double> Gd;//Saida da rede em cada neuronio tomando a derivada desse neuronio
		vector< vector<int> > cam;//vetor de camadas, indicando quem está em determinada camada
		vector< vector<double> > W;
		
		//O endereço 0 é reservado para o bias da rede
		//os enderecos [nNeu+1, ... , nNeu+nIn+1] são reservados para as entradas
		RNA(){srand(time(NULL));}

		double rand(double xmin, double xmax){
			double r = double(::rand())/RAND_MAX;
			double L = r * (xmax - xmin);
			
			return xmin + L;
		}
	
		//Calcula saida da rede com base nos estimulos de entrada
		void g(vector<double>& in);
		//Calcula saida da rede com base nos estimulos de entrada tomando a derivada nesse neuronio
		void gd(vector<double>& in);
		
		//Treina rede usando o arquivo de treinamento f e atualiza o arquivo de configuração
		//Algoritmo usado: backpropagation
		void treina(const char* f, const char* fout, bool isBatch, bool isNature);
		
		//Carrega uma rede usando o arquivo de configuração f
		void load(const char* f);
		void save(const char* f);
		
		
		int getNIn(){return nIn;}
		int getNOut(){return nOut;}
};


#endif


