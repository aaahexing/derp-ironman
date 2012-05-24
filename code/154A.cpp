#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

char f[4], s[MAXN];
int n, k, v[26][26], dp[MAXN][26];

int main() {
	while (scanf("%s%d", s, &k) != EOF) {
		memset(v, 0, sizeof(v));
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < k; ++i) {
			scanf("%s", f);
			v[f[0] - 'a'][f[1] - 'a'] = v[f[1] - 'a'][f[0] - 'a'] = 1;
		}
		n = strlen(s);
		for (int i = 1; i <= n; ++i) {
			// cross out
			for (int j = 0; j < 26; ++j)
				dp[i][j] = dp[i - 1][j] + 1;
			// keep it
			int cj = s[i - 1] - 'a';
			for (int j = 0; j < 26; ++j) {
				if (!v[cj][j]) {
					dp[i][cj] = min(dp[i][cj], dp[i - 1][j]);
				}
			}
		}
		int ans = n + 1;
		for (int j = 0; j < 26; ++j)
			ans = min(ans, dp[n][j]);
		printf("%d\n", ans);
	}
	return 0;
}
