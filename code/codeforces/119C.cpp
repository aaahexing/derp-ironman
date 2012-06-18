#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 51;

struct Subject {
	int i;
	long long a, b, c;
} s[MAXN];

inline bool operator< (const Subject &l, const Subject &r) {
	return l.c < r.c;
}

int n, m, k;
long long dp[MAXN][MAXN][101];
pair<int, int> ss[MAXN][MAXN][101];

int main() {
	while (cin >> n >> m >> k) {
		for (int i = 0; i < m; ++i) {
			s[i].i = i + 1;
			cin >> s[i].a >> s[i].b >> s[i].c;
		}
		sort(s, s + m);
		memset(dp, -1, sizeof(dp));
		for (int i = 0; i < m; ++i) {
			for (long long x = s[i].a; x <= s[i].b; ++x) {
				if (dp[1][i][x - s[i].a] < x)
					dp[1][i][x - s[i].a] = x;
			}
		}
		for (int t = 1; t < n; ++t) {
			for (int i = 0; i < m; ++i) {
				for (int j = 0; j <= 100; ++j) {
					if (dp[t][i][j] >= 0) {
						for (int ii = i + 1; ii < m; ++ii) {
							if (s[ii].c <= s[i].c)
								continue;
							long long xx;
							long long x = j + s[i].a;
							xx = x + k;
							if (xx >= s[ii].a && xx <= s[ii].b) {
								if (dp[t + 1][ii][xx - s[ii].a] < dp[t][i][j] + xx) {
									dp[t + 1][ii][xx - s[ii].a] = dp[t][i][j] + xx;
									ss[t + 1][ii][xx - s[ii].a] = make_pair(i, j);
								}
							}
							xx = x * k;
							if (xx >= s[ii].a && xx <= s[ii].b) {
								if (dp[t + 1][ii][xx - s[ii].a] < dp[t][i][j] + xx) {
									dp[t + 1][ii][xx - s[ii].a] = dp[t][i][j] + xx;
									ss[t + 1][ii][xx - s[ii].a] = make_pair(i, j);
								}
							}
						}
					}
				}
			}
		}
		int si = -1, sj = -1;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j <= 100; ++j) {
				if (dp[n][i][j] >= 0 && (si == -1 || dp[n][si][sj] < dp[n][i][j]))
					si = i, sj = j;
			}
		}
		if (si == -1) {
			cout << "NO" << endl;
		} else {
			vector< pair<int, long long> > ans;
			for (int t = n; t >= 1; --t) {
				ans.push_back(make_pair(s[si].i, s[si].a + sj));
				pair<int, int> pr = ss[t][si][sj];
				si = pr.first;
				sj = pr.second;
			}
			reverse(ans.begin(), ans.end());
			cout << "YES" << endl;
			for (int i = 0; i < ans.size(); ++i)
				cout << ans[i].first << " " << ans[i].second << endl;
		}
	}
	return 0;
}
