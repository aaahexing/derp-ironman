#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 16;

long long y, dp[MAXN + 1][1 << MAXN];
int n, m, a, b, pos[MAXN], ans[MAXN], larger[MAXN];

// @note: can be optimized into O(n^3 * 2^n) in total
//	(enumerate the last position we added, because if
//	 we know where it is, we can put person n-1 there!)
long long gao() {
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	// people
	for (int i = 0; i < n; ++i) {
		// position-mask
		for (int mask = 0; mask < (1 << n); ++mask) {
			if (dp[i][mask] > 0) {
				// put person i+1 here
				if (pos[i] != -1) {
					dp[i + 1][mask | (1 << pos[i])] += dp[i][mask];					
				} else {
					for (int j = 0; j < n; ++j) {
						if (!(mask & (1 << j)) && !(mask & larger[j]))
							dp[i + 1][mask | (1 << j)] += dp[i][mask];
					}	
				}
			}
		}
	}
	return dp[n][(1 << n) - 1];
}

int main() {
	while (cin >> n >> y >> m) {
		y = y - 2001 + 1;
		memset(pos, -1, sizeof(pos));
		memset(larger, 0, sizeof(larger));
		for (int i = 0; i < m; ++i) {
			cin >> a >> b;
			--a, --b;
			larger[a] |= (1 << b);
		}
		if (gao() < y) {
			puts("The times have changed");
		} else {
			for (int i = 0; i < n; ++i) {
				// position i
				for (int j = 0; j < n; ++j) {
					if (pos[j] != -1)
						continue;
					ans[i] = j;
					pos[j] = i;
					long long res = gao();
					if (res >= y) {
						break;
					} else {
						y -= res;
						pos[j] = -1;
					}
				}
			}
			for (int i = 0; i < n; ++i) {
				if (i) putchar(' ');
				printf("%d", ans[i] + 1);
			}
			puts("");
		}
	}
	return 0;
}
