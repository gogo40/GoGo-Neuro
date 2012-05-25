
/**
@file utils.h
@brief Neste arquivo são declaradas funções genéricas compartilhadas pelos diversos módulos do programa

UFPA - Universidade Federal do Pará
Laboratório de Análises Numéricas em Eletromagnetismo (LANE) 

Implementação do RPIM - Radial Point Interpolation Method

Esta implementação faz parte do TCC de Engenharia da Computaçã de Péricles Lopes Machado (0608000101)
*/

#ifndef __UTILS__XX__H
#define __UTILS__XX__H


#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

namespace GOGONEURO{

/**
@var  typedef std::vector<double> vectorD
@brief Um vetor de doubles
*/
	typedef std::vector<double> vectorD;

/**
@class matrixD
@brief matrixD é uma classe que define uma matriz de doubles.
*/
	class matrixD:public std::vector<vectorD>{
	public:
	
	/**
	@brief Construtor da classe matrixD.
	@param n é o numero de linhas da matriz, o valor default de n é 1.
	@param m é o numero de colunas da matriz, o valor default de m é 1.
	@param v é o valor que deve ser usado para inicializar a matriz, o valor default de v é 0.
	*/
		matrixD(int n=1, int m=1, double v=0.0):std::vector<vectorD>(n){
			for(int i=0;i<n;i++) (*this)[i]=vectorD(m,v); 
		}

	};

	/**
	@fn matrixD mat(const vectorD& x)
	@brief Função que converte um vetor vectorD em uma matriz matrixD.
	@see matrixD
	@see vectorD
	@param x é vetor  com n elementos que será convertido.
	@return uma matrixD(1,n) contendo o vetor convertido.
	*/
	matrixD mat(const vectorD& x);
	
	/**
	@fn matrixD trans(matrixD A)
	@brief Função que gera a transposta de uma matriz.
	@see matrixD
	@param A é matriz que será transposta.
	@return A matriz transposta de A.
	*/
	matrixD trans(matrixD A);
	
	/**
	@fn matrixD inv(matrixD A)
	@brief Função que gera a inversa de uma matriz
	@see matrixD
	@see gauss
	@param A é matriz a ser invertida.
	@return A matriz inversa de A, ou seja, uma matriz B tal que B*A=A*B=I, onde I é a matriz indentidade.
	
	A matriz A deve ser quadrada e inversível, caso contrário, uma mensagem de erro será gerada e o programa será abortado (a função exit(1) será chamada). Esta função
	utiliza eliminação de Gauss com pivoteamento parcial para calcular a matriz inversa de A.
	*/
	matrixD inv(matrixD A, bool& st);

	/**
	@fn matrixD operator*(const matrixD& A, const matrixD& B)
	@brief Operador que realiza o produto de duas matrizes
	@see matrixD
	@param A é uma matriz matrixD com n linhas e m colunas.
	@param B é uma matriz matrixD com k linhas e p colunas.
	@return Uma matriz matrixD com n linhas e p colunas contendo o produto de A e B, ou seja, C=A*B.
	
	m tem de ser igual a k para que o produto seja realizado, caso contrário, poderá haver erro de tempo de execução.
	*/
	matrixD operator*(const matrixD& A, const matrixD& B);
	
	/**
	@fn matrixD operator*(const double& A, const matrixD& B)
	@brief Operador que realiza o produto de um escalar por uma matriz
	@see matrixD
	@param A é um escalar.
	@param B é uma matriz matrixD com k linhas e p colunas.
	@return Uma matriz matrixD com k linhas e p colunas contendo o produto de A e B, ou seja, C=A*B.
	*/
	matrixD operator*(const double& A, const matrixD& B);

	/**
	@fn matrixD operator*(const matrixD& B, const double& A)
	@brief Operador que realiza o produto de um escalar por uma matriz
	@see matrixD
	@param B é uma matriz matrixD com k linhas e p colunas.
	@param A é um escalar.
	@return Uma matriz matrixD com k linhas e p colunas contendo o produto de A e B, ou seja, C=A*B.
	*/
	matrixD operator*(const matrixD& B, const double& A);
	
	/**
	@fn matrixD operator+(const matrixD& A, const matrixD& B)
	@brief Operador que realiza a soma de duas matrizes
	@see matrixD
	@param A é uma matriz matrixD com n linhas e m colunas.
	@param B é uma matriz matrixD com k linhas e p colunas.
	@return Uma matriz matrixD com n linhas e m colunas contendo a soma de A e B, ou seja, C=A+B.
	
	m tem de ser igual a p e n tem de ser igual a k  para que a soma seja realizada, caso contrário, poderá haver erro de tempo de execução.
	*/
	matrixD operator+(const matrixD& A, const matrixD& B);
	
	/**
	@fn matrixD operator-(const matrixD& A, const matrixD& B)
	@brief Operador que realiza a soma de duas matrizes
	@see matrixD
	@param A é uma matriz matrixD com n linhas e m colunas.
	@param B é uma matriz matrixD com k linhas e p colunas.
	@return Uma matriz matrixD com n linhas e m colunas contendo a subtração de A e B, ou seja, C=A-B.
	
	m tem de ser igual a p e n tem de ser igual a k  para que a subtração seja realizada, caso contrário, poderá haver erro de tempo de execução.
	*/
	matrixD operator-(const matrixD& A, const matrixD& B);

	/**
	@var static double EPS
	@brief Tolerância usada em algumas operações de ponto flutuante.
	*/
	static double EPS=1e-12;

	/**
	@fn inline void setTol(double eps=1e-20)
	@brief Função usada para alterar a tolerância EPS usadas em algumas operações de ponto flutuante.
	*/
	inline void setTol(double eps=1e-12){
		EPS=eps;
	}
	
	/**
	@fn  inline int cmpD(double x, double y, double eps=EPS)
	@brief Função usada para comparar dois doubles com uma tolerância de EPS.
	@see EPS
	@param x é o primeiro valor a ser comparado.
	@param y é o segundo valor a ser comparado.
	@param eps é a tolerância usada na comparação.
	@return 0 caso \f$  \left| x-y \right|  < eps \f$ , 1 caso \f$ x>y+eps \f$ e retorna -1 caso \f$ x<y-eps \f$ . 
	*/
	inline
	int cmpD(double x, double y, double eps=1e-12){
		if(fabs(x-y)<eps) return 0;
		if(x>y+eps) return 1;
		return -1;
	}

	/**
	@fn void gauss(int n, matrixD& A, matrixD& X, matrixD& B)
	@brief Função que resolve a equação matricial linear AX=B, caso exista solução.
	@see matrixD
	@param n é a dimensão do problema, ou seja, o numero de linhas da matriz quadrada a.
	@param A é uma matriz com pelo menos n linhas e pelo menos n colunas, caso a matriz a tenha menos de n linhas e colunas haverá erro de tempo de execução.
	@param X é uma matriz icognita com pelo menos n linhas e pelo menos p colunas, caso a matriz X tenha menos de n linhas e p colunas haverá erro de tempo de execução. Nessa matriz será jogado o resultado da equação AX=B.
	@param B é uma matiz com pelo menos n linhas e p colunas, caso a matriz a tenha menos de n linhas haverá erro de tempo de execução.
	
	Esta função soluciona a equação matricial AX=B, ou seja, retorna \f$ X = A^{-1}B \f$  . Para resolver a equação, esta função implementa a eliminação de Gauss com uma estrátegia de pivoteamento parcial para reduzir erros de arrendondamento.
	*/
	void gauss(int n, matrixD& A, matrixD& X, matrixD& B, bool& st);

	/**
	@fn double max_eigenvalue(const matrixD& B, double eps=1e-6, unsigned int k=1<<10)
	@brief Função para computar o auto-valor com maior valor absoluto de uma dada matriz.
	@see matrixD
	@param B é a matriz para a qual deseja-se computar os auto-valores
	@param eps é a tolerancia
	@param k é o numero de iterações máximo que o algoritmo deve executar
	@return O auto-valor com maior valor absoluto da matriz B
	*/
	double max_eigenvalue(const matrixD& B, double eps=1e-6, unsigned int k=1<<10);
	
	/**
	@fn double dot(const matrixD& A, const matrixD& B)
	@brief Função que computa o produto interno de duas matrizes A e B
	@see matrixD
	@param A é uma matriz quadrada NxN
	@param B é uma matriz quadrada NxN
	@return o produto interno de A e B, ou seja, \f$ \sum_{i=0}^{N} { \sum_{j=0}^{N}{A_{ij} B_{ij}}} \f$, onde N é o tamanho da matriz.
	*/
	double dot(const matrixD& A, const matrixD& B);
};

#endif
