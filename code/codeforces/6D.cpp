#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 16;
const int MAXH = 17;

vector<int> ans;
int n, a, b, h[MAXN], dp[MAXN][MAXH][MAXH];
pair< int, pair<int, int> > s[MAXN][MAXH][MAXH];

int main() {
	while (scanf("%d%d%d", &n, &a, &b) != EOF) {
		memset(h, 0, sizeof(h));
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &h[i]);
			++h[i];
		}
		memset(dp, 0x7f, sizeof(dp));
		dp[1][0][h[1]] = 0;
		for (int i = 1; i <= n; ++i)
			for (int ii = 0; ii < MAXH; ++ii)
				for (int jj = 0; jj < MAXH; ++jj)
					s[i][ii][jj] = make_pair(0, make_pair(0, 0));
		for (int i = 1; i <= n; ++i) {
			for (int ii = 0; ii < MAXH; ++ii) {
				for (int jj = 0; jj < MAXH; ++jj) {
					if (dp[i][ii][jj] >= 0x7f7f7f7f)
						continue;
					for (int c = 0; c < MAXH; ++c) {
						if (ii - c * b <= 0) {
							int nextii = max(0, jj - c * a);
							int nextjj = max(0, h[i + 1] - c * b);
							if (dp[i + 1][nextii][nextjj] > dp[i][ii][jj] + c) {
								dp[i + 1][nextii][nextjj] = dp[i][ii][jj] + c;
								s[i + 1][nextii][nextjj] = make_pair(c, make_pair(ii, jj));
							}
						}
						// Cannot attack the extreme archers
						if (i == 1 || i == n) {
							break;
						}
					}
				}
			}
		}
		printf("%d\n", dp[n][0][0]);
		ans.clear();
		int ii = 0, jj = 0;
		for (int i = n; i > 2; --i) {
			pair< int, pair<int, int> > pr = s[i][ii][jj];
			while (pr.first > 0) {
				ans.push_back(i - 1);
				--pr.first;
			}
			ii = pr.second.first;
			jj = pr.second.second;
		}
		for (int i = 0; i < ans.size(); ++i) {
			if (i) putchar(' ');
			printf("%d", ans[i]);
		}
		puts("");
	}
	return 0;
}

