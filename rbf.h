#ifndef _RBF_H_
#define _RBF_H_

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include <cmath>
#include <cstring>

#include "utils.h"

using namespace std;
using namespace GOGONEURO;


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

double dist(const vectorD& x, const vectorD& y);
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void saveRBF(const char* net_name, int& n_neu, int& n_in, int& n_out, matrixD& W, matrixD& X, vector<double>& beta);

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

bool loadRBF(const char* net_name, int& n_neu, int& n_in, int& n_out, matrixD& W, matrixD& C, vector<double>& beta);

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

bool trainRBF(
int n_neu, int n_in, int n_out, int N,
vector<double>& beta, 
matrixD& input, matrixD& output,
matrixD& X, matrixD& W);

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

bool deRBF(
double pT,
double pV,
double betaini,
double betafim,
double CR,
int gen_max,
int NP,
double F,
int n_neu, int n_in, int n_out, int N,
vector<double>& beta,
matrixD& center,
matrixD& input, matrixD& output,
matrixD& X, matrixD& W);

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

double runRBF(
int N, int n_out, int n_neu,
matrixD& W, matrixD& input, 
matrixD& output, matrixD& C,
vector<double>& beta);

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void runSaveRBF(
int N, int n_out, int n_neu,
matrixD& W, matrixD& input, 
matrixD& output, matrixD& C,
vector<double>& beta);

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void loadData(
const char* input_name,
const char* output_name,
const char* center_name,
matrixD& input, matrixD& output, 
matrixD& center, int& N, int& Ncenter,
int& n_in, int& n_out);

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

#endif

