#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1001;

char s[MAXN][MAXN];
int n, m, r[MAXN], c[MAXN];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(r, 0, sizeof(r));
		memset(c, 0, sizeof(c));
		for (int i = 0; i < n; ++i) {
			scanf("%s", s[i]);
			for (int j = 0; j < m; ++j) {
				r[i] += s[i][j] == '*';
				c[j] += s[i][j] == '*';
			}
		}
		long long ans = 0;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				ans += (s[i][j] == '*') ? (r[i] - 1LL) * (c[j] - 1LL) : 0;
		cout << ans << endl;
	}
	return 0;
}
