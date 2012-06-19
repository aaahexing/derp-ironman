#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const long long INFF = 1000000000LL * 2001;

int n, t, c;
long long dp[2001][4001];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i <= n; ++i)
			for (int j = -n; j <= n; ++j)
				dp[i][j + 2000] = INFF;
		dp[0][2000] = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &t, &c);
			for (int j = -n + 2000; j <= n + 2000; ++j) {
				if (dp[i][j] < INFF) {
					dp[i + 1][j - 1] = min(dp[i + 1][j - 1], dp[i][j]);
					dp[i + 1][min(n + 2000, j + t)] = min(dp[i + 1][min(n + 2000, j + t)], dp[i][j] + c);
				}
			}
		}
		long long ans = INFF;
		for (int j = 0 + 2000; j <= n + 2000; ++j)
			ans = min(ans, dp[n][j]);
		cout << ans << endl;
	}
	return 0;
}

