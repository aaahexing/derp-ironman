#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1024;

int n, ans, h[MAXN], dp[MAXN][2];

int main() {
	while (scanf("%d", &n) != EOF) {
		h[0] = h[n + 1] = 0;
		for (int i = 1; i <= n; ++i)
			scanf("%d", &h[i]);
		dp[0][0] = 0;
		for (int i = 1; i <= n; ++i)
			dp[i][0] = 1 + (h[i] >= h[i - 1]) * dp[i - 1][0];
		dp[n + 1][1] = 0;
		for (int i = n; i >= 1; --i)
			dp[i][1] = 1 + (h[i] >= h[i + 1]) * dp[i + 1][1];
		ans = 0;
		for (int i = 1; i <= n; ++i)
			ans = max(ans, dp[i][0] + dp[i][1] - 1);
		printf("%d\n", ans);
	}
	return 0;
}
