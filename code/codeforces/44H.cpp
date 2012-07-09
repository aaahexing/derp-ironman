#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

char s[64];
long long n, ans, dp[64][16];

int main() {
	while (scanf("%s", s) != EOF) {
		n = strlen(s);
		for (int i = 0; i < n; ++i)
			s[i] -= '0';
		memset(dp, 0, sizeof(dp));
		for (int j = 0; j < 10; ++j)
			dp[0][j] = 1;
		for (int i = 0; i < n - 1; ++i) {
			for (int j = 0; j < 10; ++j) {
				if ((j + s[i + 1]) % 2 == 0) {
					dp[i + 1][(j + s[i + 1]) / 2] += dp[i][j];
				} else {
					dp[i + 1][(j + s[i + 1]) / 2] += dp[i][j];
					dp[i + 1][(j + s[i + 1]) / 2 + 1] += dp[i][j];
				}
			}
		}
		ans = 0;
		for (int j = 0; j < 10; ++j)
			ans += dp[n - 1][j];
		int fd = s[0];
		for (int i = 0; i < n; ++i) {
			if (fd != s[i]) {
				break;
			} else if (i == n - 1) {
				--ans;
			} else {
				int ss = fd + s[i + 1];
				fd = (ss % 2 == 0 ? ss / 2 : (ss / 2 == s[i + 1] ? ss / 2 : ss / 2 + 1));			
			}
		}
		cout << ans << endl;
	}
	return 0;
}
