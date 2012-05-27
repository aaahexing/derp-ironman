#include <cstdio>
#include <cstring>

int n, a[1000010], dp[1<<22];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(dp, -1, sizeof(dp));
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			dp[a[i]] = a[i];
		}
		for (int mask = 0; mask < (1<<22); ++mask) {
			for (int i = 0; i < 22; ++i) {
				if ((mask & (1 << i)) && dp[mask ^ (1 << i)] != -1) {
					dp[mask] = dp[mask ^ (1 << i)];
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			if (i) putchar(' ');
			printf("%d", dp[(~a[i]) & ((1 << 22) - 1)]);
		}
		puts("");
	}
	return 0;
}
