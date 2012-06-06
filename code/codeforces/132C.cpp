#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INFF = 1000000000;

int n, m;
char s[128];
const int d[] = {-1, 1};
pair<int, int> dp[128][128][2];

int main() {
	while (scanf("%s%d", s, &m) != EOF) {
		n = strlen(s);
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= m; ++j)
				dp[i][j][0] = dp[i][j][1] = make_pair(INFF, -INFF);
		dp[0][0][0] = dp[0][0][1] = make_pair(0, 0);
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= m; ++j) {
				for (int k = 0; k < 2; ++k) {
					for (int jj = (s[i - 1] == 'F' ? 0 : 1); jj <= j; jj += 2) {
						dp[i][j][k].first = min(dp[i][j][k].first, dp[i - 1][j - jj][k].first + d[k]);
						dp[i][j][k].second = max(dp[i][j][k].second, dp[i - 1][j - jj][k].second + d[k]);
					}
					for (int jj = (s[i - 1] == 'T' ? 0 : 1); jj <= j; jj += 2) {
						dp[i][j][k].first = min(dp[i][j][k].first, dp[i - 1][j - jj][1 - k].first);
						dp[i][j][k].second = max(dp[i][j][k].second, dp[i - 1][j - jj][1 - k].second);
					}
				}
			}
		}
		int ans = 0;
		for (int k = 0; k < 2; ++k) {
			ans = max(ans, abs(dp[n][m][k].first));
			ans = max(ans, abs(dp[n][m][k].second));
		}
		printf("%d\n", ans);
	}
	return 0;
}

