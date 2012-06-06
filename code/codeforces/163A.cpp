#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 5001;
const int MODD = 1000000007;

char a[MAXN], b[MAXN];
int n, m, dp[MAXN][MAXN];

int main() {
	while (scanf("%s%s", a, b) != EOF) {
		n = strlen(a), m = strlen(b);		
		for (int i = 0; i <= n; ++i)
			memset(dp[i], 0, sizeof(int) * (m + 1));
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				dp[i][j] = dp[i][j - 1];
				if (a[i - 1] == b[j - 1])
					dp[i][j] = (dp[i][j] + dp[i - 1][j - 1] + 1) % MODD;
			}
		}
		int ans = 0;
		for (int i = 1; i <= n; ++i)
			ans = (ans + dp[i][m]) % MODD;
		printf("%d\n", ans);
	}
	return 0;
}
