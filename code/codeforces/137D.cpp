#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 501;

char s[MAXN];
int n, k, m[MAXN][MAXN], p[MAXN][MAXN], dp[MAXN][MAXN];

int main() {
	while (scanf("%s%d", s, &k) != EOF) {
		n = strlen(s);
		for (int i = 0; i < n; ++i) {
			for (int j = i; j < n; ++j) {
				int ii = i, jj = j, ss = 0;
				for (; ii < jj; ++ii, --jj)
					ss += (s[ii] != s[jj]);
				m[i][j] = ss;
			}
		}
		memset(p, -1, sizeof(p));
		memset(dp, 0x7f, sizeof(dp));
		dp[0][0] = 0;
		for (int i = 0; i <= n; ++i)
			p[i][0] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= i; ++j) {
				p[i][j] = -1;
				dp[i][j] = n + 1;
				for (int ii = i - 1; ii >= 0; --ii) {
					if (dp[i][j] > dp[ii][j - 1] + m[ii][i - 1]) {
						dp[i][j] = dp[ii][j - 1] + m[ii][i - 1];
						p[i][j] = ii;
					}
				}
			}
		}
		int ansi = 1;
		for (int j = 1; j <= k; ++j)
			if (dp[n][ansi] > dp[n][j])
				ansi = j;
		vector<string> ans;
		printf("%d\n", dp[n][ansi]);
		for (int j = ansi; n > 0; --j) {
			string ss = "";
			int nn = p[n][j];
			int ll = n - 1 - nn + 1;
			for (int i = nn; i <= n - 1; ++i)
				ss += s[i];
			int ii = 0, jj = ll - 1;
			while (ii < jj) {
				if (ss[ii] != ss[jj])
					ss[jj] = ss[ii];
				++ii, --jj;
			}
			ans.push_back(ss);
			n = nn;
		}
		reverse(ans.begin(), ans.end());
		for (int i = 0; i < ans.size(); ++i) {
			if (i) putchar('+');
			printf("%s", ans[i].c_str());
		}
		puts("");
	}
	return 0;
}

