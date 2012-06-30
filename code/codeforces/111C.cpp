#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m, cc[1 << 6], dp[42][1 << 6][1 << 6];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		if (n > m)
			swap(n, m);
		cc[0] = 0;
		for (int mask = 1; mask < (1 << n); ++mask)
			cc[mask] = cc[mask & (mask - 1)] + 1;
		memset(dp, 0x7f, sizeof(dp));
		for (int b = 0; b < (1 << n); ++b)
			dp[0][0][b] = 0;
		for (int i = 1; i <= m; ++i) {
			for (int a = 0; a < (1 << n); ++a) {
				for (int b = 0; b < (1 << n); ++b) {
					for (int c = 0; c < (1 << n); ++c) {
						int mask = a | b | c;
						for (int j = 0; j < n; ++j) {
							if (b & (1 << j)) {
								if (j + 1 < n)
									mask |= 1 << (j + 1);
								if (j - 1 >= 0)
									mask |= 1 << (j - 1);
							}
						}
						if (mask == (1 << n) - 1) {
							dp[i][b][c] = min(dp[i][b][c], dp[i - 1][a][b] + cc[b]);
						}
					}
				}
			}
		}
		int ans = 0;
		for (int a = 0; a < (1 << n); ++a)
			ans = max(ans, n * m - dp[m][a][0]);
		printf("%d\n", ans);
	}
	return 0;
}
