#include <set>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 5010;

bool dp[MAXN];
int n, a, b, cc[MAXN];
vector<short> adj[MAXN];
set< pair<int, int> > S;

int gao(int i, int src) {
	cc[i] = 1;
	for (int j = 0; j < adj[i].size(); ++j) {
		if (adj[i][j] != src)
			cc[i] += gao(adj[i][j], i);
	}
	// empty i
	memset(dp, false, sizeof(dp));
	dp[0] = true;
	for (int j = 0; j < adj[i].size(); ++j) {
		int ii = adj[i][j];
		int cnt = (ii == src ? n - cc[i] : cc[ii]);
		for (int k = n; k >= 0; --k) {
			if (dp[k])
				dp[k + cnt] = true;
		}
	}
	for (int j = 1; j <= n - 2; ++j) {
		if (dp[j]) {
			S.insert(make_pair(j, n - 1 - j));
			S.insert(make_pair(n - 1 - j, j));
		}
	}
	return cc[i];
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i)
			adj[i].clear();
		S.clear();
		memset(cc, 0, sizeof(cc));
		for (int i = 1; i <= n - 1; ++i) {
			scanf("%d%d", &a, &b);
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		gao(1, -1);
		printf("%d\n", (int)S.size());
		for (set< pair<int, int> > :: iterator it = S.begin(); it != S.end(); ++it)
			printf("%d %d\n", it->first, it->second);
	}
	return 0;
}
