#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <functional>
using namespace std;

const int MAXN = 100010;

int n, a, b, w;
long long dp[MAXN][2];
vector< pair<int, int> > adj[MAXN];

long long gao(int i, int src, int ret) {
	long long &cost = dp[i][ret];
	if (cost != -1)
		return cost;
	cost = 0;
	int cn = (int)adj[i].size();
	long long mini = 2000000000;
	for (int j = 0; j < cn; ++j) {
		int cc = adj[i][j].first;
		int ii = adj[i][j].second;
		if (ii != src) {
			gao(ii, i, 0);
			cost += gao(ii, i, 1) + cc * 2;
			if (ret == 0)
				mini = min(mini, dp[ii][0] - dp[ii][1] - cc);
		}
	}
	cost = min(cost, cost + mini);
	return cost;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; ++i)
			adj[i].clear();
		for (int i = 0; i < n - 1; ++i) {
			scanf("%d%d%d", &a, &b, &w);
			--a, --b;
			adj[a].push_back(make_pair(w, b));
			adj[b].push_back(make_pair(w, a));
		}
		memset(dp, -1, sizeof(dp));
		cout << gao(0, 0, 0) << endl;
	}
	return 0;
}
