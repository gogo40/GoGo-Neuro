
/**
@file utils.cpp
@brief Neste arquivo são implementadas as funções definidas no arquivo utils.h

UFPA - Universidade Federal do Pará
Laboratório de Análises Numéricas em Eletromagnetismo (LANE) 

Implementação do RPIM - Radial Point Interpolation Method

Esta implementação faz parte do TCC de Engenharia da Computaçã de Péricles Lopes Machado (0608000101)

Baseado na implementação  do PROF. DR. RODRIGO M.S. DE OLIVEIRA
*/

#include <stdio.h>
#include <math.h>

#include "utils.h"

GOGONEURO::matrixD GOGONEURO::mat(const vectorD& x){
	int n=x.size();
	matrixD C(1,n,0.0);
	
	for(int i=0;i<n;i++) C[0][i]=x[i];
	
	return C;
}

GOGONEURO::matrixD GOGONEURO::trans(matrixD A){
	int nA=A.size(), mA=A[0].size();
	matrixD C(mA,nA,0.0);
	
	for(int i=0;i<nA;i++)
		for(int j=0;j<mA;j++)
			C[j][i]=A[i][j];
			
	return C;
}

GOGONEURO::matrixD GOGONEURO::inv(matrixD A, bool& st){
	int n=A.size(); 
	matrixD I(n,n,0.0), Ai(n,n,0.0);
	
	for(int i=0;i<n;i++) I[i][i]=1.0;
	
	gauss(n,A,Ai,I,st);
	
	return Ai;
}

GOGONEURO::matrixD GOGONEURO::operator*(const matrixD& A, const matrixD& B){
	int nA=A.size(), mA=A[0].size();
	int nB=B.size(), mB=B[0].size();
	matrixD C(nA,mB,0.0);
	
	for(int i=0;i<nA;i++)
		for(int j=0;j<mB;j++)
			for(int k=0;k<mA;k++)
				C[i][j]+=A[i][k]*B[k][j];
				
	return C;
}

GOGONEURO::matrixD GOGONEURO::operator*(const double& A, const matrixD& B){
	matrixD C(B.size(),B[0].size());
	C=B;
	for(int i=0;i<C.size();i++)for(int j=0;j<C.size();j++)C[i][j]*=A;
	return C;
}


GOGONEURO::matrixD GOGONEURO::operator*(const matrixD& B, const double& A){
	matrixD C(B.size(),B[0].size());
	C=B;
	for(int i=0;i<C.size();i++)for(int j=0;j<C.size();j++)C[i][j]*=A;
	return C;
}

GOGONEURO::matrixD GOGONEURO::operator+(const matrixD& A, const matrixD& B){
	int nA=A.size(), mA=A[0].size();
	int nB=B.size(), mB=B[0].size();
	matrixD C(nA,mB,0.0);
	
	for(int i=0;i<nA;i++)
		for(int j=0;j<mA;j++)
			C[i][j]=A[i][j]+B[i][j];
	
	return C;
}

GOGONEURO::matrixD GOGONEURO::operator-(const matrixD& A, const matrixD& B){
	int nA=A.size(), mA=A[0].size();
	int nB=B.size(), mB=B[0].size();
	matrixD C(nA,mB,0.0);
	
	for(int i=0;i<nA;i++)
		for(int j=0;j<mA;j++)
			C[i][j]=A[i][j]-B[i][j];
	
	return C;
}

void GOGONEURO::gauss(int n, matrixD& A, matrixD& X, matrixD& B, bool& st){
	std::vector<int> p(n); matrixD c(n,n), y(n,n);
	double pv, t, soma; int r, h;

	st=true;
	for(int i=0;i<n;i++) p[i]=i;

	for(int k=0;k<n-1;k++){

		pv=fabs(A[k][k]);
		r=k;

		for(int i=k+1;i<n;i++)
			if(cmpD(fabs(A[i][k]),pv)>0){
				pv=fabs(A[i][k]);
				r=i;
			}


		if(cmpD(pv,0.0)==0){
			st=false;
			fprintf(stderr,"Matriz inversa nao existe! Saindo...\n");
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++) X[i][j]=0.1;
			return;
		}


		if(r!=k){
			h=p[k]; p[k]=p[r]; p[r]=h;
			for(int j=0;j<n;j++){
				t=A[k][j]; A[k][j]=A[r][j]; A[r][j]=t;
			}
		}

		for(int i=k+1;i<n;i++){
			t=A[i][k]/A[k][k];
			A[i][k]=t;
			for(int j=k+1;j<n;j++) A[i][j]-=t*A[k][j];
		}
	}

	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			r=p[i];
			c[i][k]=B[r][k];
		}

		for(int i=0;i<n;i++){
			soma=0;
			for(int j=0;j<i;j++) soma+=A[i][j]*y[j][k];
			y[i][k]=c[i][k]-soma;
		}

		for(int i=n-1;i>-1;i--){
			soma=0;
			for(int j=i+1;j<n;j++) soma+=A[i][j]*X[j][k];
			X[i][k]=(y[i][k]-soma)/A[i][i];
		}
	}

}

double GOGONEURO::dot(const matrixD& A, const matrixD& B){
	double ans=0; int N=A.size();
	for(int i=0;i<N;i++) for(int j=0;j<N;j++) ans+=A[i][j]*B[i][j];
	return ans;
}

double GOGONEURO::max_eigenvalue(const matrixD& B, double eps, unsigned int k){
	double ans=-1, diff;
	int N=B.size();
	matrixD A(N,N);
	matrixD v(N,1),w(N,1);
	
	A=B;
	diff=0;
	for(int i=0;i<N;i++) diff+=A[i][0]*A[i][0];
	diff=sqrt(diff);
	
	for(int i=0;i<N;i++){
		v[i][0]=A[i][0]/diff;
		if(v[i][0]>ans) ans=fabs(v[i][0]);
	}
	diff=eps+1;
	
	while(diff>eps&&k){
		
		v=(1/ans)*A*v;
		diff=ans;
		
		ans=-1;
		
		for(int i=0;i<N;i++) if(fabs(v[i][0])>ans) ans=fabs(v[i][0]);
		
		diff=fabs(ans-diff);
		k--;
	}

	return ans;
}









