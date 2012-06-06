#include <cstdio>
#include <algorithm>
using namespace std;

int n, dp[1024];

int main() {
	while (scanf("%d", &n) != EOF) {
		dp[0] = 1024;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &dp[i]);
			dp[i] = min(dp[i], max(dp[i - 1], i > 2 ? dp[i - 2] : -1));
		}
		printf("%d\n", dp[n]);
	}
	return 0;
}
