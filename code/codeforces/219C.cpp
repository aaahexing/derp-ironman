#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 500010;

char s[MAXN];
int n, k, dp[MAXN][26], pre[MAXN][26];

void output(int i, int j) {
	if (i > 0) {
		output(i - 1, pre[i][j]);
	}
	putchar('A' + j);
}

int main() {
	while (scanf("%d%d%s", &n, &k, s) != EOF) {
		memset(pre, -1, sizeof(pre));
		memset(dp, 0x3f, sizeof(dp));
		for (int j = 0; j < 26; ++j) {
			dp[0][j] = (s[0] != j + 'A');
		}
		for (int i = 1; i < n; ++i) {
			for (int j = 0; j < k; ++j) {
				int cost = (s[i] != j + 'A');
				for (int jj = 0; jj < k; ++jj) {
					if (jj != j) {
						if (dp[i][j] > dp[i - 1][jj] + cost) {
							dp[i][j] = dp[i - 1][jj] + cost;
							pre[i][j] = jj;
						}
					}
				}
			}
		}
		int mj = 0;
		for (int j = 1; j < k; ++j) {
			if (dp[n - 1][j] < dp[n - 1][mj])
				mj = j;
		}
		printf("%d\n", dp[n - 1][mj]);
		output(n - 1, mj);
		putchar('\n');
	}
	return 0;
}
