#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const long long INFF = 1000000000000000000LL;
const int prime[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

long long n, ans, dp[11][1010];

int main() {
	memset(dp, -1, sizeof(dp));
	dp[0][1] = 1;
	for (int i = 0; i < 10; ++i) {
		for (int j = 1; j <= 1000; ++j) {
			if (dp[i][j] > 0) {
				long long pp = 1;
				for (int k = 0; ; ++k) {
					long long cc = j * (k + 1);
					if (cc <= 1000) {
						if (dp[i + 1][cc] == -1 || dp[i + 1][cc] / pp > dp[i][j]) {
							dp[i + 1][cc] = dp[i][j] * pp;
						}
					}
					if (pp > INFF / prime[i])
						break;
					if (pp > INFF / dp[i][j] / prime[i])
						break;
					pp *= prime[i];
				}
			}
		}
	}
	while (cin >> n) {
		ans = -1;
		for (int i = 0; i <= 10; ++i) {
			if (ans == -1 || dp[i][n] < ans)
				ans = dp[i][n];
		}
		cout << ans << endl;
	}
	return 0;
}

