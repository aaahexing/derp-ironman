#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 50010;
const int MAXK = 510;

int n, k, a, b; 
vector<int> adj[MAXN];
long long ans, dp[MAXN][MAXK];

void gao(int i, int src) {
	dp[i][0] = 1;
	for (int j = 0; j < (int)adj[i].size(); ++j) {
		int ii = adj[i][j];
		if (ii != src) {
			gao(ii, i);
			for (int d = 1; d <= k; ++d) {
				if (k >= d + 1)
					ans += (long long)dp[i][d] * (long long)dp[ii][k - d - 1];
				dp[i][d] += dp[ii][d - 1];
			}
		}
	}
	ans += dp[i][k];
}

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		ans = 0;
		for (int i = 0; i < n; ++i)
			adj[i].clear();
		for (int i = 0; i < n - 1; ++i) {
			scanf("%d%d", &a, &b);
			--a, --b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		memset(dp, 0, sizeof(dp));
		gao(0, 0);
		cout << ans << endl;
	}
	return 0;
}
