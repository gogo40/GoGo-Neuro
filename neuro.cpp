/**
1.a Tarefa de Inteligência Computacional

Equipe [gogo40]:
1.) Péricles Lopes Machado
2.) João Augusto Palmitesta Neto
3.) Paulo Ribeiro de Almeida Neto

Arquivo: neuro.cpp

Descrição: Implementação de metodo relacionados ao neuronio.

*/

#include "rna.h"

#define dx 1e-6

/*Lista de funcoes de ativação*/

//0-arco_tangente =  p*atan(x)
double atan(double x,double p)//0
{ return atan(p*x); }
double datan(double x, double p)
{ return p*(1.0/(1.0+x*x)); }

double linear(double x, double p)//1
{ return p*x; }
double dlinear(double x, double p)
{ return p; }

double sigmoide(double x, double p)//2
{ return 1/(1+exp(-p*x));}
double dsigmoide(double x, double p)
{ double a=exp(-p*x), b; b=1+a; return p*a/(b*b);}

double tanh(double x, double p)//3
{ return tanh(p*x); }
double dtanh(double x, double p)
{ double sech; sech=2.0/(exp(p*x)+exp(-p*x)); return sech*sech*p; }


double Neuronio::g(vector<double>& X, vector<vector<double> >& W){
	double out=0;
	
	for(unsigned int i=0;i<conn.size();i++){
		out+= X[conn[i]]*W[conn[i]][id];
	}
	
	return fa[id_fa](out,p);
}

double Neuronio::gd(vector<double>& X, vector<vector<double> >& W){
	double out=0;

	for(unsigned int i=0;i<conn.size();i++){
		out+= X[conn[i]]*W[conn[i]][id];
	}
	
	return dfa[id_fa](out,p);
}

