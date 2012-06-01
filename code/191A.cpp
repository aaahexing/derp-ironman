#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char s[16];
int n, dp[2][26][26];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(dp, -1, sizeof(dp));
		for (int i = 0; i < 26; ++i)
			dp[1][i][i] = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%s", s);
			int cur = i & 1;
			int pre = 1 - cur;
			int l = strlen(s);
			int a = s[0] - 'a', b = s[l - 1] - 'a';
			for (int j = 0; j < 26; ++j)
				for (int k = 0; k < 26; ++k)
					dp[cur][j][k] = dp[pre][j][k];
			for (int j = 0; j < 26; ++j)
				if (dp[pre][j][a] >= 0)
					dp[cur][j][b] = max(dp[cur][j][b], dp[pre][j][a] + l);
		}
		int ans = 0;
		for (int i = 0; i < 26; ++i)
			ans = max(ans, dp[(n - 1) & 1][i][i]);
		printf("%d\n", ans);
	}	
	return 0;
}
