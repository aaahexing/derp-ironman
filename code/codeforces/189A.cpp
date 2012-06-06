#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n, a, b, c, dp[4010][3];
	while (cin >> n >> a >> b >> c) {
		memset(dp, -1, sizeof(dp));
		dp[0][0] = dp[0][1] = dp[0][2] = 0;
		for (int i = 1; i <= n; ++i) {
			if (i >= a) {
				if (dp[i - a][0] >= 0)
					dp[i][0] = dp[i - a][0] + 1;
			}
			if (i >= b) {
				if (dp[i - b][1] >= 0)
					dp[i][1] = max(dp[i][1], dp[i - b][1] + 1);
				if (dp[i - b][0] >= 0)
					dp[i][1] = max(dp[i][1], dp[i - b][0] + 1);
			}
			if (i >= c) {
				if (dp[i - c][2] >= 0)
					dp[i][2] = max(dp[i][2], dp[i - c][2] + 1);
				if (dp[i - c][1] >= 0)
					dp[i][2] = max(dp[i][2], dp[i - c][1] + 1);
				if (dp[i - c][0] >= 0)
					dp[i][2] = max(dp[i][2], dp[i - c][0] + 1);
			}
		}
		cout << max(dp[n][0], max(dp[n][1], dp[n][2])) << endl;
	}
}
