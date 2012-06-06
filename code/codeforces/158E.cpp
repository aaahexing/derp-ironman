#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 4010;
const int INFF = 1000000000;

int n, k, dp[MAXN][MAXN];
pair<int, int> calls[MAXN];

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &calls[i].first, &calls[i].second);
			--calls[i].first;
		}
		int ans = 0;
		dp[0][0] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= i && j <= k; ++j) {
				dp[i][j] = INFF;
				// Ignore this
				if (j > 0)
					dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
				// Answer this
				dp[i][j] = min(dp[i][j], max(dp[i - 1][j], calls[i].first) + calls[i].second);
				int next = (i == n ? 86400 : calls[i + 1].first);
				ans = max(ans, next - dp[i][j]);
			}
		}
		if (n == 0) {
			ans = 86400;
		}
		printf("%d\n", ans);
	}
	return 0;
}
