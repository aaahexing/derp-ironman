#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 512;

int n, m, a[MAXN], b[MAXN], s[MAXN][MAXN], dp[MAXN][MAXN];

int main() {
	while (scanf("%d", &n) != EOF) {
		a[0] = b[0] = -1;
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		scanf("%d", &m);
		for (int j = 1; j <= m; ++j)
			scanf("%d", &b[j]);
		memset(dp, 0, sizeof(dp));
		for (int j = 1; j <= m; ++j) {
			int k = 0;
			for (int i = 1; i <= n; ++i) {
				dp[i][j] = dp[i][j - 1];
				s[i][j] = -1;
				// If a[i] < b[j], then dp[i][j - 1] will have a chance to
				//		contribute to the optimal values next time when a[i0] == b[j]
				// The reason is if in some i0 where a[i0] == b[j], we'll try to
				// 		find the maximum sub-state in this way:
				//			k = 0;
				//			for (int kk = 0; kk < i0; ++kk)
				//				if (a[kk] < a[i0] && dp[kk][j - 1] > dp[k][j - 1])
				//					k = j;
				//		considering that a[i0] == b[j] and this is eqvalent to find
				//		the maximum k where a[k] < b[j] and dp[k][j - 1] is maximum
				//		for each k less than i
				if (a[i] < b[j] && dp[i][j - 1] > dp[k][j - 1])
					k = i;
				if (a[i] == b[j] && dp[i][j] < dp[k][j - 1] + 1) {
					dp[i][j] = dp[k][j - 1] + 1;
					s[i][j] = k;
				}
			}
		}
		int ni = 0;
		int nj = m;
		int maxi = 0;
		vector<int> ans;
		for (int i = n; i >= 1; --i) {
			if (dp[i][m] > maxi) {
				maxi = dp[i][m];
				ni = i;
			}
		}
		printf("%d\n", maxi);
		if (maxi > 0) {
			while (dp[ni][nj] > 0) {
				int ss = s[ni][nj];
				if (ss == -1) {
					--nj;
				} else {
					ans.push_back(a[ni]);
					if (ss == 0) {
						break;
					} else {
						--nj;
						ni = ss;
					}
				}
			}	
		}
		reverse(ans.begin(), ans.end());
		for (int i = 0; i < ans.size(); ++i) {
			if (i) putchar(' ');
			printf("%d", ans[i]);
		}
		puts("");
	}
	return 0;
}
