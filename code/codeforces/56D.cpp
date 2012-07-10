#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1024;

enum Operation {
	Nothing,
	Replace,
	Insert,
	Delete
};

char a[MAXN], b[MAXN];
int n, m, insert_n, s[MAXN][MAXN], dp[MAXN][MAXN];

void gao(int i, int j, int &ins_n) {
	if (i == 0 && j == 0)
		return;
	if (s[i][j] == Nothing) {
		gao(i - 1, j - 1, ins_n);
	} else if (s[i][j] == Replace) {
		gao(i - 1, j - 1, ins_n);
		printf("REPLACE %d %c\n", j + ins_n, a[i - 1]);
	} else if (s[i][j] == Insert) {
		gao(i - 1, j, ins_n);
		printf("INSERT %d %c\n", j + 1 + ins_n, a[i - 1]);
		++ins_n;
	} else {
		gao(i, j - 1, ins_n);
		printf("DELETE %d\n", j + ins_n);
		--ins_n;
	}
}

int main() {
	while (scanf("%s%s", b, a) != EOF) {
		n = strlen(a);
		m = strlen(b);
		for (int i = 0; i <= n; ++i)
			memset(dp[i], 0x7f, sizeof(int) * (m + 1));
		dp[0][0] = 0;
		for (int i = 0; i <= n; ++i) {
			dp[i][0] = i;
			s[i][0] = Insert;
		}
		for (int j = 0; j <= m; ++j) {
			dp[0][j] = j;
			s[0][j] = Delete;
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				// Do nothing
				if (a[i - 1] == b[j - 1]) {
					if (dp[i][j] > dp[i - 1][j - 1]) {
						dp[i][j] = dp[i - 1][j - 1];
						s[i][j] = Nothing;
					}
				}
				// Replace
				if (dp[i][j] > dp[i - 1][j - 1] + 1) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
					s[i][j] = Replace;
				}
				// Insert
				if (dp[i][j] > dp[i - 1][j] + 1) {
					dp[i][j] = dp[i - 1][j] + 1;
					s[i][j] = Insert;
				}
				// Delete
				if (dp[i][j] > dp[i][j - 1] + 1) {
					dp[i][j] = dp[i][j - 1] + 1;
					s[i][j] = Delete;
				}
			}
		}
		printf("%d\n", dp[n][m]);
		insert_n = 0;
		gao(n, m, insert_n);
	}
	return 0;
}
