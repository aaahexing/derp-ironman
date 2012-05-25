#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int MAXM = 10001;

int n, m, nn;
int v[MAXN], d[MAXN][MAXN], s[MAXN][MAXN], dp[MAXN][MAXM];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(s, 0, sizeof(s));
		for (int i = 0; i <= n; ++i)
			memset(dp[i], 0, sizeof(int) * (m + 1));
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &nn);
			for (int j = 0; j <= nn; ++j)
				memset(d[j], 0, sizeof(int) * (nn + 1));
			memset(v, 0, sizeof(v));
			for (int j = 1; j <= nn; ++j) {
				scanf("%d", &v[j]);
				s[i][nn] += v[j];
			}
			for (int len = nn - 1; len >= 1; --len) {
				for (int l = 1; l + len - 1 <= nn; ++l) {
					int r = l + len - 1;
					if (l > 1)
						d[l][r] = max(d[l][r], d[l - 1][r] + v[l - 1]);
					if (r < nn)
						d[l][r] = max(d[l][r], d[l][r + 1] + v[r + 1]);
				}
			}
			for (int l = 1; l <= nn; ++l)
				for (int r = l; r <= nn; ++r)
					s[i][nn - r + l - 1] = max(s[i][nn - r + l - 1], d[l][r]);
			for (int j = 0; j <= m; ++j) {
				for (int l = 0; l <= j && l <= nn; ++l)
					dp[i][j] = max(dp[i][j], dp[i - 1][j - l] + s[i][l]);
			}
		}
		printf("%d\n", dp[n][m]);
	}
	return 0;
}
