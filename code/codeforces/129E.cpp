#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1024;
const int MODD = 1000000007;

int n, m, k, sum, dp[MAXN][MAXN];

int main() {
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		int nn = max(n, m);
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= nn; ++i)
			dp[i][0] = 1;
		for (int c = 1; c <= k; ++c) {
			sum = 0;
			for (int i = 2; i <= nn; ++i) {
				sum = (sum + dp[i - 2][c - 1]) % MODD;
				dp[i][c] = (sum + dp[i - 1][c]) % MODD;
			}
		}
		printf("%d\n", (int)(((long long)dp[n][k] * dp[m][k]) % MODD));
	}
	return 0;
}
