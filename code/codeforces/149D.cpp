#include <stack>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 710;
const int MODD = 1000000007;

char s[MAXN];
int n, m[MAXN], dp[MAXN][MAXN][3][3];

int gao(int l, int r, int cl, int cr) {
	if (l > r)
		return 1;
	int &ret = dp[l][r][cl][cr];
	if (ret != -1)
		return ret;
	ret = 0;
	int mm = m[l];
	if (mm == r) {
		for (int c = 0; c < 2; ++c) {
			if (c != cl)
				ret = (ret + gao(l + 1, r - 1, c, 2)) % MODD;
			if (c != cr)
				ret = (ret + gao(l + 1, r - 1, 2, c)) % MODD;
		}
	} else {
		for (int c = 0; c < 2; ++c) {
			if (c != cl)
				ret = (ret + gao(l + 1, mm - 1, c, 2) * 1LL * gao(mm + 1, r, 2, cr)) % MODD;
			ret = (ret + gao(l + 1, mm - 1, 2, c) * 1LL * gao(mm + 1, r, c, cr)) % MODD;
		}
	}
	return ret;
}

int main() {
	while (scanf("%s", s) != EOF) {
		stack<int> S;
		n = strlen(s);
		memset(dp, -1, sizeof(dp));
		for (int i = 0; i < n; ++i) {
			if (s[i] == '(') {
				S.push(i);
			} else {
				int ii = S.top(); S.pop();
				m[ii] = i;
				m[i] = ii;
			}
		}
		printf("%d\n", gao(0, n - 1, 2, 2));
	}
	return 0;
}
