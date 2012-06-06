#include <set>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int MODD = 1000000007;

char s[MAXN];
int m, n, dp[MAXN][2610];

int main() {
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < 26; ++i)
		dp[1][i] = 1;
	for (int i = 2; i <= 100; ++i) {
		for (int j = 0; j <= 2600; ++j) {
			for (int k = 0; k < 26; ++k) {
				if (j >= k)
					dp[i][j] = (dp[i][j] + dp[i - 1][j - k]) % MODD;
			}
		}
	}
	scanf("%d", &m);
	for (int t = 0; t < m; ++t) {
		scanf("%s", s);
		int sum = 0;
		for (n = 0; s[n]; ++n)
			sum += s[n] - 'a';
		printf("%d\n", (dp[n][sum] + MODD - 1) % MODD);
	}
}

