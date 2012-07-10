#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 20;

const int c0[] = { 2, 1, 0, 1, 2 };
const int c1[] = { 6, 7, 8, 7, 6 };
const int di[] = { 1, 1, 0, 0, -1, -1 };
const int dj[] = { -1, 1, 2, -2, -1, 1 };

int dp[1 << MAXN];
char ts[16], s[16][16], a[16][16];

int gao() {
	int mask = 0, po = 0;
	for (int i = 0; i < 5; ++i) {
		for (int j = c0[i]; j <= c1[i]; j += 2) {
			if (s[i][j] == 'O') {
				mask |= (1 << po);
			}
			++po;
		}
	}
	int &ret = dp[mask];
	if (ret == -1) {
		ret = 0;
		for (int i = 0; i < 5 && !ret; ++i) {
			for (int j = c0[i]; j <= c1[i] && !ret; j += 2) {
				if (s[i][j] != 'O')
					continue;
				for (int k = 0; k < 6 && !ret; ++k) {
					int ii = i, jj = j;
					while (ii >= 0 && ii < 5 && jj >= c0[ii] && jj <= c1[ii] && s[ii][jj] == 'O') {
						s[ii][jj] = 'X';
						ii += di[k];
						jj += dj[k];
						if (!gao()) {
							ret = 1;
							break;
						}
					}
					while (ii != i || jj != j) {
						ii -= di[k];
						jj -= dj[k];
						s[ii][jj] = 'O';
					}
				}
			}
		}
	}
	return ret > 0;
}


int main() {
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < 16; ++i)
		for (int j = 0; j < 16; ++j)
			s[i][j] = '?';
	for (int i = 0; i < 5; ++i) {
		for (int j = c0[i]; j <= c1[i]; j += 2) {
			scanf("%s", ts);
			s[i][j] = ts[0];
		}
	}
	printf("%s\n", gao() ? "Karlsson" : "Lillebror");
	return 0;
}

