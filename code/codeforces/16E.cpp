#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN =  18;

int n;
double di, a[MAXN][MAXN], dp[1 << MAXN];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				scanf("%lf", &a[i][j]);
		dp[(1 << n) - 1] = 1.0;
		for (int mask = (1 << n) - 1; mask > 0; --mask) {
			int c = 0;
			for (int i = 0; i < n; ++i)
				c += (mask & (1 << i)) > 0;
			if (c >= 2) {
				di = 1.0 / (c * (c - 1) / 2);
				for (int i = 0; i < n; ++i) {
					if (mask & (1 << i)) {
						for (int j = i + 1; j < n; ++j) {
							if (mask & (1 << j)) {
								dp[mask ^ (1 << j)] += di * dp[mask] * a[i][j];
								dp[mask ^ (1 << i)] += di * dp[mask] * a[j][i];
							}
						}
					}
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			if (i) putchar(' ');
			printf("%.6lf", dp[1 << i]);
		}
		puts("");
	}
	return 0;
}
