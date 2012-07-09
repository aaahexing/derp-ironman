#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INFF = 1000000000;

int n, m;
char s[110];
pair<int, int> dp[110][51][2];

inline pair<int, int> shift(const pair<int, int> &pr, int v) {
	return make_pair(pr.first + v, pr.second + v);
}

inline pair<int, int> getopt(const pair<int, int> &pr, const pair<int, int> &ppr) {
	return make_pair(min(pr.first, ppr.first), max(pr.second, ppr.second));
}

int main() {
	while (scanf("%s%d", s, &m) != EOF) {
		n = strlen(s);
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= n; ++j)
				dp[i][j][0] = dp[i][j][1] = make_pair(INFF, -INFF);
		dp[0][0][0] = dp[0][0][1] = make_pair(0, 0);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j <= i && j <= m; ++j) {
				for (int k = 0; k < 2; ++k) {
					if (dp[i][j][k].first > dp[i][j][k].second) {
						continue;
					}
					// To be 'F'
					for (int jj = j + (s[i] == 'F' ? 0 : 1); jj <= m; jj += 2) {
						dp[i + 1][jj][k] = getopt(dp[i + 1][jj][k], shift(dp[i][j][k], k == 0 ? -1 : 1));
					}
					// To be 'T'
					for (int jj = j + (s[i] == 'T' ? 0 : 1); jj <= m; jj += 2) {
						dp[i + 1][jj][1 - k] = getopt(dp[i + 1][jj][1 - k], shift(dp[i][j][k], 0));
					}
				}
			}
		}
		int ans = 0;
		for (int k = 0; k < 1; ++k)
			ans = max(ans, max(-dp[n][m][k].first, dp[n][m][k].second));
		printf("%d\n", ans);
	}
	return 0;
}
