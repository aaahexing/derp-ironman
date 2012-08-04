#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int DIRV = 1;
const int DIRH = 2;
const int MAXN = 256;
const int MODD = 1000000007;

const char dice[2][7][3][4] = {
	{
		{
			"...",
			"...",
			"..."
		},
		{
			"...",
			".O.",
			"..."
		},
		{
			"..O",
			"...",
			"O.."
		},
		{
			"..O",
			".O.",
			"O.."
		},
		{
			"O.O",
			"...",
			"O.O"
		},
		{
			"O.O",
			".O.",
			"O.O"
		},
		{
			"O.O",
			"O.O",
			"O.O"
		}
	},
	{
		{
			"...",
			"...",
			"..."
		},
		{
			"...",
			".O.",
			"..."
		},
		{
			"O..",
			"...",
			"..O"
		},
		{
			"O..",
			".O.",
			"..O"
		},
		{
			"O.O",
			"...",
			"O.O"
		},
		{
			"O.O",
			".O.",
			"O.O"
		},
		{
			"OOO",
			"...",
			"OOO"
		}
	}
};

char s[MAXN * 4][MAXN * 4];
int n, m, dp[MAXN], col[MAXN], two[MAXN][4], a[MAXN][MAXN];

bool can(int di, int ii, int jj) {
	for (int ni = 0; ni < 7; ++ni) {
		bool equal = true;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				if (dice[di][ni][i][j] != s[ii + i][jj + j])
					equal = false;
		if (equal)
			return true;
	}
	return false;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 0; i < 4 * n + 1; ++i)
			scanf("%s", s[i]);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				a[i + 1][j + 1] = 0;
				if (can(0, i * 4 + 1, j * 4 + 1))
					a[i + 1][j + 1] |= DIRV;
				if (can(1, i * 4 + 1, j * 4 + 1))
					a[i + 1][j + 1] |= DIRH;
			}
		}
		memset(col, 0, sizeof(col));
		for (int j = 1; j <= m; ++j) {
			col[j] = 1;
			if (n & 1)
				col[j] = 0;
			for (int i = 1; i <= n; ++i)
				if (!(a[i][j] & DIRV))
					col[j] = 0;
		}
		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		for (int j = 1; j <= m; ++j) {
			if (col[j]) {
				dp[j] = (dp[j] + dp[j - 1]) % MODD;
			}
			if (j >= 2) {
				memset(two, 0, sizeof(two));
				two[0][0] = 1;
				for (int i = 0; i < n; ++i) {
					// put horizontally
					if ((a[i + 1][j] & DIRH) && (a[i + 1][j - 1] & DIRH))
						two[i + 1][0] = (two[i + 1][0] + two[i][0]) % MODD;
					// put vertically
					for (int mask = 0; mask < 4; ++mask) {
						if (two[i][mask] > 0) {
							int nmask = 0;
							for (int ii = 0; ii < 2; ++ii) {
								if (!(mask & (1 << ii))) {
									if (i + 2 <= n && (a[i + 1][j - ii] & DIRV) && (a[i + 2][j - ii] & DIRV))
										nmask |= (1 << ii);
									else
										goto NEXT;
								}
							}
							two[i + 1][nmask] = (two[i + 1][nmask] + two[i][mask]) % MODD;
							NEXT:;							
						}
					}	
				}
				dp[j] = (dp[j] + dp[j - 2] * 1LL * (two[n][0] - (col[j]) * col[j - 1])) % MODD;
			}
		}
		printf("%d\n", dp[m]);
	}
	return 0;
}
