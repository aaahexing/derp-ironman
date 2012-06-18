#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char s[16];
int n, l, dp[26][26];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < n; ++i) {
			scanf("%s", s);
			l = strlen(s);
			int a = s[0] - 'a';
			int b = s[l - 1] - 'a';
			for (int j = 0; j < 26; ++j) {
				if (dp[j][a] > 0) {
					dp[j][b] = max(dp[j][b], dp[j][a] + l);
				}
			}
			dp[a][b] = max(dp[a][b], l);
		}
		int ans = 0;
		for (int i = 0; i < 26; ++i)
			ans = max(ans, dp[i][i]);
		printf("%d\n", ans);
	}
	return 0;
}
