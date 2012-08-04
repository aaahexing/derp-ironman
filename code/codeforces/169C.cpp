#include <cstdio>
#include <cstring>

const int MAXN = 5010;
const int MODD = 1000000007;

char s[MAXN], t[MAXN];
int n, m, ans, dp[MAXN][MAXN];

int main() {
	while (scanf("%s%s", s, t) != EOF) {
		n = strlen(s);
		m = strlen(t);
		for (int i = 0; i <= n; ++i)
			memset(dp[i], 0, sizeof(int) * (m + 1));
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				dp[i][j] = dp[i][j - 1];
				if (s[i - 1] == t[j - 1]) {
					dp[i][j] = (dp[i][j] + dp[i - 1][j - 1] + 1) % MODD;
				}
			}
		}
		ans = 0;
		for (int i = 1; i <= n; ++i)
			ans = (ans + dp[i][m]) % MODD;
		printf("%d\n", ans);
	}
	return 0;
}
