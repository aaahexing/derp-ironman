#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 501;
const int INFF = 1000000000;

int n, m, ans;
int s[2][MAXN][MAXN][2];
int a[MAXN][MAXN], t[MAXN][MAXN];

void init() {
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			t[i][j] = a[i][j] + t[i - 1][j] + t[i][j - 1] - t[i - 1][j - 1];
}

inline int get(int i0, int j0, int i1, int j1) {
	return t[i1][j1] - t[i0 - 1][j1] - t[i1][j0 - 1] + t[i0 - 1][j0 - 1];
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				scanf("%d", &a[i][j]);
		init();
		ans = -INFF;
		int mk = min((n - 1) >> 1, (m - 1) >> 1);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				s[0][i][j][0] = s[0][i][j][1] = a[i][j];
		for (int k = 1; k <= mk; ++k) {
			int l = (k << 1) | 1;
			for (int i = 1; i + l - 1 <= n; ++i) {
				for (int j = 1; j + l - 1 <= m; ++j) {
					int i0 = i, j0 = j;
					int i1 = i + l - 1, j1 = j + l - 1;
					s[k & 1][i0][j0][0] = s[(k & 1) ^ 1][i1][j1 - 2][1] + get(i0, j0, i1, j1) - get(i0 + 1, j0, i1, j1 - 1) + a[i1][j1 - 1];
					s[k & 1][i1][j1][1] = s[(k & 1) ^ 1][i0][j0 + 2][0] + get(i0, j0, i1, j1) - get(i0, j0 + 1, i1 - 1, j1) + a[i0][j0 + 1];
					ans = max(ans, s[k & 1][i0][j0][0]);
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
