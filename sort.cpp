#include <set>
#include <utility>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int i = 0;
	vector<pair<int, int> > S;
	while(!feof(stdin)) {
		int v;
		scanf("%d",&v);
		S.push_back(pair<int,int>(-v, i));
		++i;
	}

	sort(S.begin(), S.end());

	vector<pair<int,int> >::iterator it = S.begin(),
	end = S.end();
	
	while (it != end) {
		printf("%d %d\n", -it->first, it->second);
		++it;
	}
	
	return 0;
}
