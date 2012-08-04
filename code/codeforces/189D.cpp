#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 61;
const int MAXM = 61;
const int MAXK = 1001;
const int INFF = 1000000000;

int n, m, r, s, t, kk;
int d[MAXM][MAXN][MAXN], dp[MAXK][MAXN][MAXN];

int main() {
	while (scanf("%d%d%d", &n, &m, &r) != EOF) {
		for (int k = 0; k <= 1000; ++k)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					dp[k][i][j] = INFF;
		for (int ci = 0; ci < m; ++ci) {
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					scanf("%d", &d[ci][i][j]);
			for (int k = 0; k < n; ++k)
				for (int i = 0; i < n; ++i)
					for (int j = 0; j < n; ++j)
						if (d[ci][i][j] > d[ci][i][k] + d[ci][k][j])
							d[ci][i][j] = d[ci][i][k] + d[ci][k][j];
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					dp[0][i][j] = min(dp[0][i][j], d[ci][i][j]);
		}
		for (int k = 1; k <= 1000; ++k) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					for (int ii = 0; ii < n; ++ii) {
						dp[k][i][j] = min(dp[k][i][j], dp[0][i][ii] + dp[k - 1][ii][j]);
					}
				}
			}
		}
		while (r--) {
			scanf("%d%d%d", &s, &t, &kk);
			printf("%d\n", dp[kk][s - 1][t - 1]);
		}
	}
	return 0;
}

