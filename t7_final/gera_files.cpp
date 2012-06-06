#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <map>

using namespace std;

void print(FILE* out, int& i, const char* fn) {
	FILE* f = fopen(fn, "r");
	
	while (!feof(f)) {
		double x, y;
		fscanf(f,"%lf%lf\n", &x, &y);
		fprintf(out,"%d %e\n", i, y);
		++i;
	}
	
	fclose(f);
	
}

int main()
{
	int i = 1;
	for (int k = 1; k <= 5; ++k) {
		string fname[10];
		
		fname[0]  = "treino.nat.batch.1.";
		fname[0] += char('0' + k);
		
		fname[1]  = "treino.nat.online.1.";
		fname[1] += char('0' + k);
		
		fname[2]  = "treino.std.batch.1.";
		fname[2] += char('0' + k);
		
		fname[3]  = "treino.std.online.1.";
		fname[3] += char('0' + k);
		
		fname[4]  = "treino.nat.batch.2.";
		fname[4] += char('0' + k);
		
		fname[5]  = "treino.nat.online.2.";
		fname[5] += char('0' + k);
		
		fname[8] = "log.";
		fname[8] += char('0'+k);
		fname[8] += ".dat";
		
		FILE* f = fopen(fname[8].c_str(), "w+");
		
		for (int n = 0; n < 6; ++n){
			print(f, i, fname[n].c_str());
			cout<<fname[n]<<"\n";
		}
		
		fclose(f);
	
	}
	
	return 0;
}