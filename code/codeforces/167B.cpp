#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 201;
const int offset = 201;

int n, l, k, a[MAXN];
double p[MAXN], dp[MAXN][MAXN][MAXN + MAXN];

int main() {
	while (scanf("%d%d%d", &n, &l, &k) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%lf", &p[i]);
			p[i] /= 100.0;
		}
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		memset(dp, 0, sizeof(dp));
		dp[0][0][min(k, n) + offset] = 1.0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j <= i; ++j) {
				for (int c = -200; c <= 200; ++c) {
					// lose
					dp[i + 1][j][c + offset] += (1.0 - p[i + 1]) * dp[i][j][c + offset];
					// win
					if (a[i + 1] >= 1) {
						dp[i + 1][j + 1][min(n, c + a[i + 1]) + offset] += p[i + 1] * dp[i][j][c + offset];
					} else {
						dp[i + 1][j + 1][c - 1 + offset] += p[i + 1] * dp[i][j][c + offset];
					}
				}
			}
		}
		double ans = 0.0;
		for (int j = l; j <= n; ++j)
			for (int c = 0; c <= n; ++c)
				ans += dp[n][j][c + offset];
		printf("%.9lf\n", ans);
	}
	return 0;
}
