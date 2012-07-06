#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 19;

int n, m, a, b, e[MAXN][MAXN];
long long ans, dp[1 << MAXN][MAXN];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(e, 0, sizeof(e));
		memset(dp, 0, sizeof(dp));
		for (int ei = 0; ei < m; ++ei) {
			scanf("%d%d", &a, &b);
			--a, --b;
			e[a][b] = e[b][a] = 1;
			dp[(1 << a) | (1 << b)][max(a, b)] = 1;
		}
		ans = 0;
		for (int mask = 0; mask < (1 << n); ++mask) {
			int s = __builtin_ctz(mask);
			for (int t = s + 1; t < n; ++t) {
				if (dp[mask][t] == 0) {
					continue;
				}
				if (e[t][s]) {
					ans += dp[mask][t];
				}
				for (int i = s + 1; i < n; ++i) {
					if (e[t][i] && (mask & (1 << i)) == 0) {
						dp[mask | (1 << i)][i] += dp[mask][t];
					}
				}
			}
		}
		cout << (ans - m) / 2 << endl;
	}
	return 0;
}
