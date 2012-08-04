#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 310;
const int INFF = 1000000000;
const int di[] = { 0, 1 };
const int dj[] = { 1, 0 };

int n, a[MAXN][MAXN], dp[MAXN + MAXN][MAXN][MAXN];

inline bool valid(int i) {
	return i >= 1 && i <= n;
}

inline bool valid(int i, int j) {
	return i >= 1 && i <= n && j >= 1 && j <= n;
}

inline void update(int i, int r0, int r1, int d0, int d1) {
	int c0 = i + 1 - r0;
	int c1 = i + 1 - r1;
	int rr0 = r0 + di[d0];
	int cc0 = c0 + dj[d0];
	int rr1 = r1 + di[d1];
	int cc1 = c1 + dj[d1];
	if (!valid(rr0, cc0) || !valid(rr1, cc1))
		return;
	int score = a[rr0][cc0] + a[rr1][cc1] - (rr0 == rr1 && cc0 == cc1) * a[rr0][cc0];
	dp[i + 1][rr0][rr1] = max(dp[i + 1][rr0][rr1], dp[i][r0][r1] + score);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				scanf("%d", &a[i][j]);
		for (int i = 1; i <= n + n; ++i)
			for (int r0 = 1; r0 <= n; ++r0)
				for (int r1 = 1; r1 <= n; ++r1)
					dp[i][r0][r1] = -INFF;
		dp[1][1][1] = a[1][1];
		for (int i = 1; i <= n + n; ++i) {
			for (int r0 = 1; r0 <= n; ++r0) {
				if (!valid(i + 1 - r0))
					continue;
				for (int r1 = 1; r1 <= n; ++r1) {
					if (!valid(i + 1 - r1))
						continue;
					if (dp[i][r0][r1] < INFF) {
						for (int d0 = 0; d0 < 2; ++d0) {
							for (int d1 = 0; d1 < 2; ++d1) {
								update(i, r0, r1, d0, d1);	
							}
						}	
					}
				}
			}
		}
		printf("%d\n", dp[n + n - 1][n][n]);
	}
	return 0;
}
