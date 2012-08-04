#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 16;

int n, y, m, a, b;
long long dp[MAXN + 1][1 << MAXN];
int g[MAXN + 1][MAXN + 1], l[MAXN + 1][MAXN + 1];

int main() {
	while (scanf("%d%d%d", &n, &y, &m) != EOF) {
		memset(g, 0, sizeof(g));
		memset(l, 0, sizeof(l));
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &a, &b);
			g[a][b] = l[b][a] = 1;
		}
		dp[0][0] = 1;
		for (int si = 0; si < n; ++si){
			for (int mask = 0; mask < (1 << n); ++mask) {
				if (dp[si][mask] > 0) {
					// try the i+1 seats
					for (int i = 0; i < n; ++i) {
						if (!(mask & (1 << i))) {
						}
						NEXT:;
					}
				}
			}	
		}
	}
	return 0;
}
