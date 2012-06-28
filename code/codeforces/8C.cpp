#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 24;
const int INFF = 1000000000;

int n, x0, y0, x[MAXN + 1], y[MAXN + 1], d[MAXN + 1][MAXN + 1], s[1 << MAXN], dp[1 << MAXN];

inline int sqr(int x) {
	return x * x;
}

inline int dis(int x1, int y1, int x2, int y2) {
	return sqr(x1 - x2) + sqr(y1 - y2);
}

int main() {
	while (scanf("%d%d", &x0, &y0) != EOF) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			scanf("%d%d", &x[i], &y[i]);
		x[n] = x0, y[n] = y0;
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= n; ++j)
				d[i][j] = dis(x[i], y[i], x[j], y[j]);
		s[0] = dp[0] = 0;
		for (int mask = 1; mask < (1 << n); ++mask) {
			int nmask;
			dp[mask] = INFF;
			for (int i = 0; i < n; ++i) {
				if (mask & (1 << i)) {
					nmask = mask ^ (1 << i);
					if (dp[mask] > dp[nmask] + d[n][i] + d[i][n]) {
						s[mask] = nmask;
						dp[mask] = dp[nmask] + d[n][i] + d[i][n];
					}
					for (int j = i + 1; j < n; ++j) {
						if (mask & (1 << j)) {
							nmask = mask ^ (1 << i) ^ (1 << j);
							if (dp[mask] > dp[nmask] + d[n][i] + d[i][j] + d[j][n]) {
								s[mask] = nmask;
								dp[mask] = dp[nmask] + d[n][i] + d[i][j] + d[j][n];
							}
						}
					}
					break;	// Orz...
				}
			}
		}
		printf("%d\n", dp[(1 << n) - 1]);
		printf("0");
		for (int mask = (1 << n) - 1; mask > 0; mask = s[mask]) {
			for (int i = 0; i < n; ++i) {
				if ((mask ^ s[mask]) & (1 << i))
					printf(" %d", i + 1);
			}
			printf(" 0");
		}
		puts("");
	}

	return 0;
}
