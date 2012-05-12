/**
1.a Tarefa de Intelig�ncia Computacional

Equipe [gogo40]:
1.) P�ricles Lopes Machado
2.) Jo�o Augusto Palmitesta Neto
3.) Paulo Ribeiro de Almeida Neto

Arquivo: rna.h

Descri��o: Defini��o das classes e fun��es fundamentais para implementar uma Rede Neural.
Pretendemos manter essa biblioteca mais gen�rica possivel.

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


/*Ponteiro de fun��es do tipo f(x,p), p pode n�o ser usado*/
typedef double (*fd)(double,double);

/*Lista de funcoes de ativa��o*/

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
Vetor de fun��es de ativa��o
*/
static const fd fa[]={atan,linear,sigmoide,tanh};
static const fd dfa[]={datan,dlinear,dsigmoide,dtanh};

/**
Defini��o de uma conex�o
*/

/**
Defini��o de um neuronio
*/
struct Neuronio{

		int id;//Id do neuronio, id 0 � reservado para o bias!!!
		int id_fa;//Id da fun��o de ativa��o
		double p;//Fatores p  para a fun��o de ativa��o
		int c;//camada a que pertence o neuronio
		
		vector<int> conn;//Conex�es que entram, conex�o 0 � o bias
		vector<int> dest;//Conex�es que saem
		
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
Defini��o da rede Neural
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
		vector<double> G;//Saida da rede em cada neuronio para o padr�o de entrada
		vector<double> Gd;//Saida da rede em cada neuronio tomando a derivada desse neuronio
		vector< vector<int> > cam;//vetor de camadas, indicando quem est� em determinada camada
		vector< vector<double> > W;
		
		//O endere�o 0 � reservado para o bias da rede
		//os enderecos [nNeu+1, ... , nNeu+nIn+1] s�o reservados para as entradas
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
		
		//Treina rede usando o arquivo de treinamento f e atualiza o arquivo de configura��o
		//Algoritmo usado: backpropagation
		void treina(const char* f, const char* fout, bool isBatch, bool isNature);
		
		//Carrega uma rede usando o arquivo de configura��o f
		void load(const char* f);
		void save(const char* f);
		
		
		int getNIn(){return nIn;}
		int getNOut(){return nOut;}
};


#endif


