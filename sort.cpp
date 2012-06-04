#include <set>
#include <utility>
#include <cstdio>

using namespace std;

int main()
{
	int i = 0;
	set<pair<int, int> > S;
	while(!feof(stdin)) {
		int v;
		scanf("%d",&v);
		S.insert(pair<int,int>(-v, i));
		++i;
	}
	
	set<pair<int,int> >::iterator it = S.begin(),
	end = S.end();
	
	for (int k = 0; k < i; ++k) {
		printf("%d %d\n", -it->first, it->second);
		++it;
	}
	
	return 0;
}
