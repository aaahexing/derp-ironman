#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 512;

char a[MAXN][MAXN];
int n, m, dp[MAXN][26][26];
pair<int, int> pre[MAXN][26][26];

void output(int i, pair<int, int> s) {
	if (i > 0) {
		pair<int, int> pr = pre[i][s.first][s.second];
		output(i - 1, pr);
	}
	for (int j = 0; j < m; ++j) {
		printf("%c", 'a' + ((j & 1) ? s.second : s.first));
	}
	putchar('\n');
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 0; i < n; ++i)
			scanf("%s", a[i]);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 26; ++j) {
				for (int k = 0; k < 26; ++k) {
					int cc = 0;
					for (int l = 0; l < m; ++l)
						cc += (a[i][l] != 'a' + ((l & 1) ? k : j));
					if (j == k)
						cc = m + 1;
					dp[i][j][k] = cc;
					pre[i][j][k] = make_pair(-1, -1);
				}
			}
		}
		
		vector< pair<int, pair<int, int> > > priii_v;
		for (int i = 1; i < n; ++i) {
			priii_v.clear();
			for (int j = 0; j < 26; ++j) {
				for (int k = 0; k < 26; ++k) {
					if (j != k)
						priii_v.push_back(make_pair(dp[i - 1][j][k], make_pair(j, k)));
				}
			}
			sort(priii_v.begin(), priii_v.end());
			for (int j = 0; j < 26; ++j) {
				for (int k = 0; k < 26; ++k) {
					if (j == k) continue;
					pair<int, pair<int, int> > priii;
					pair<int, int> pr = make_pair(-1, -1);
					for (int p = 0; p < priii_v.size(); ++p) {
						priii = priii_v[p];
						if (priii.second.first != j && priii.second.second != k)
							break;
					}
					dp[i][j][k] += dp[i - 1][priii.second.first][priii.second.second];
					pre[i][j][k] = priii.second; 
				}
			}
		}
		pair<int, int> ans = make_pair(-1, -1);
		for (int j = 0; j < 26; ++j) {
			for (int k = 0; k < 26; ++k) {
				if (j == k) continue;
				if (ans.first == -1 || dp[n - 1][j][k] < dp[n - 1][ans.first][ans.second]) {
					ans = make_pair(j, k);
				}
			}
		}
		printf("%d\n", dp[n - 1][ans.first][ans.second]);
		output(n - 1, ans);
	}
	return 0;
}
