#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 128;

char a[MAXN][MAXN];
int n, m, k, dp[MAXN][MAXN][16];
pair<int, int> ss[MAXN][MAXN][16];

int main() {
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		for (int i = 0; i < n; ++i)
			scanf("%s", a[i]);
		for (int j = 0; j < m; ++j)
			for (int kk = 0; kk <= k; ++kk)
				dp[n][j][kk] = (kk == 0 ? 0 : -1);
		for (int i = n - 1; i >= 0; --i) {
			for (int j = 0; j < m; ++j) {
				a[i][j] -= '0';
				for (int kk = 0; kk <= k; ++kk) {
					dp[i][j][kk] = -1;
					int pk = ((k + 1 - a[i][j] + kk) % (k + 1) + (k + 1)) % (k + 1);
					//printf("kk = %d, pk = %d, a = %d\n", kk, pk, a[i][j]);
					if (j > 0 && dp[i + 1][j - 1][pk] >= 0) {
						if (dp[i][j][kk] < dp[i + 1][j - 1][pk] + a[i][j]) {
							dp[i][j][kk] = dp[i + 1][j - 1][pk] + a[i][j];
							ss[i][j][kk] = make_pair(j - 1, pk);
						}
					}
					if (j < m - 1 && dp[i + 1][j + 1][pk] >= 0) {
						if (dp[i][j][kk] < dp[i + 1][j + 1][pk] + a[i][j]) {
							dp[i][j][kk] = dp[i + 1][j + 1][pk] + a[i][j];
							ss[i][j][kk] = make_pair(j + 1, pk);
						}
					}
				}
			}
		}
		int ansj = -1;
		for (int j = 0; j < m; ++j) {
			if (ansj == -1 || dp[0][ansj][0] < dp[0][j][0]) {
				ansj = j;
			}
		}
		if (dp[0][ansj][0] == -1) {
			puts("-1");
		} else {
			k = 0;
			vector<int> cols;
			printf("%d\n", dp[0][ansj][0]);
			cols.push_back(ansj);
			for (int i = 0; i < n - 1; ++i) {
				pair<int, int> pr = ss[i][ansj][k];
				ansj = pr.first;
				k = pr.second;
				cols.push_back(ansj);
			}
			reverse(cols.begin(), cols.end());
			printf("%d\n", cols[0] + 1);
			for (int i = 0; i < n - 1; ++i)
				printf("%c", cols[i] > cols[i + 1] ? 'L' : 'R');
			puts("");
		}
	}
	return 0;
}
