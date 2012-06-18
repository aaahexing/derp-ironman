#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MODD = 1000000007;

int n, l, a[101][2], b[101][2], dp[3010][101][2];

inline void update(int i, int j, int r, int val) {
	if (i <= l)
		dp[i][j][r] = (dp[i][j][r] + val) % MODD;
}

int main() {
	while (scanf("%d%d", &n, &l) != EOF) {
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &a[i][0], &b[i][0]);
			a[i][1] = b[i][0], b[i][1] = a[i][0];
		}
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < n; ++i) {
			update(a[i][0], i, 0, 1);
			if (a[i][0] != b[i][0])
				update(b[i][0], i, 1, 1);
		}
		for (int i = 0; i <= l; ++i) {
			for (int j = 0; j < n; ++j) {
				for (int r = 0; r < 2; ++r) {
					if (dp[i][j][r] > 0) {
						for (int k = 0; k < n; ++k) {
							if (k != j) {
								if (b[k][0] == a[j][r]) {
									update(i + a[k][0], k, 0, dp[i][j][r]);
								} else if (a[k][0] == a[j][r]) {
									update(i + b[k][0], k, 1, dp[i][j][r]);
								}
							}
						}
					}
				}
			}
		}
		int ans = 0;
		for (int j = 0; j < n; ++j)
			for (int r = 0; r < 2; ++r)
				ans = (ans + dp[l][j][r]) % MODD;
		printf("%d\n", ans);
	}
	return 0;
}
