#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, x, c, dp[110][110];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while (scanf("%d%d", &n, &x) != EOF) {
		memset(dp, 0x7f, sizeof(dp));
		dp[0][0] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &c);
			for (int j = 0; j <= i; ++j) {
				// keep it
				dp[i][j] = dp[i - 1][j];
				if (j > 0)
					dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + c * (n - i + 1));
			}
		}
		for (int j = n; j >= 0; --j) {
			if (dp[n][j] <= x) {
				printf("%d\n", j);
				break;
			}
		}
	}
	return 0;
}
