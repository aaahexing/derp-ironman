#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 52;

int n, m, a[MAXN];
double c[MAXN][MAXN], p0[MAXN][MAXN], p1[MAXN][MAXN], dp[MAXN][MAXN][MAXN];

int main() {
	memset(c, 0, sizeof(c));
	for (int i = 0; i < MAXN; ++i)
		c[i][0] = 1.0;
	for (int i = 1; i < MAXN; ++i) {
		for (int j = 1; j <= i; ++j)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
	for (int i = 0; i < MAXN; ++i) {
		p0[i][0] = p1[i][0] = 1.0;
		for (int j = 1; j < MAXN; ++j) {
			p0[i][j] = p0[i][j - 1] * 1.0 / i;
			p1[i][j] = p1[i][j - 1] * 1.0 * (i - 1) / i;
		}
	}
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= m; ++i)
			scanf("%d", &a[i]);
		memset(dp, 0, sizeof(dp));
		dp[n][m][0] = 1.0;
		for (int i = n; i >= 0; --i) {
			for (int j = m; j >= 1; --j) {
				for (int mm = 0; mm <= 50; ++mm) {
					if (dp[i][j][mm] > 0.0) {
						for (int cc = 0; cc <= i; ++cc) {
							int q = (cc + a[j] - 1) / a[j];
							dp[i - cc][j - 1][max(mm, q)] += dp[i][j][mm] * c[i][cc] * p0[j][cc] * p1[j][i - cc];
						}
					}
				}
			}
		}
		double ans = 0.0;
		for (int mm = 0; mm <= 50; ++mm)
			ans += dp[0][0][mm] * mm;
		printf("%.12lf\n", ans);
	}
	return 0;
}
