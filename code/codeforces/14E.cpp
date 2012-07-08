#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, t, dp[21][11][11][5][5];

int main() {
	while (scanf("%d%d", &n, &t) != EOF) {
		memset(dp, 0, sizeof(dp));
		dp[0][0][0][0][0] = 1;
		for (int i = 0; i < n; ++i) {
			for (int t0 = 0; t0 <= t; ++t0) {
				for (int t1 = 0; t1 <= t - 1; ++t1) {
					for (int y0 = 0; y0 <= 4; ++y0) {
						for (int y1 = 0; y1 <= 4; ++y1) {
							if (dp[i][t0][t1][y0][y1]) {
								for (int y = 1; y <= 4; ++y) {
									if (y != y1) {
										if (i >= 2 && y0 < y1 && y1 > y) {
											if (t0 < t) {
												dp[i + 1][t0 + 1][t1][y1][y] += dp[i][t0][t1][y0][y1];
											}
										} else if (i >= 2 && y0 > y1 && y1 < y) {
											if (t1 < t - 1) {
												dp[i + 1][t0][t1 + 1][y1][y] += dp[i][t0][t1][y0][y1];
											}
										} else {
											dp[i + 1][t0][t1][y1][y] += dp[i][t0][t1][y0][y1];
										}
									}
								}
							}
						}
					}
				}
			}
		}
		int ans = 0;
		for (int y0 = 0; y0 <= 4; ++y0)
			for (int y1 = 0; y1 <= 4; ++y1)
				ans += dp[n][t][t - 1][y0][y1];
		printf("%d\n", ans);
	}
	return 0;
}
