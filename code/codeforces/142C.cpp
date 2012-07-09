#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int pat[][3] = {
	{7, 2, 2},
	{4, 7, 4},
	{2, 2, 7},
	{1, 7, 1}
};

const int opt[10][10] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 1, 1, 2, 2, 3, 3, 4},
	{ 0, 0, 0, 1, 2, 2, 3, 4, 4, 5},
	{ 0, 0, 0, 2, 2, 4, 4, 5, 6, 7},
	{ 0, 0, 0, 2, 3, 4, 5, 6, 7, 8},
	{ 0, 0, 0, 3, 4, 5, 6, 8, 9, 10},
	{ 0, 0, 0, 3, 4, 6, 7, 9, 10, 12},
	{ 0, 0, 0, 4, 5, 7, 8, 10, 12, 13}
};

char ch, board[20][20];
int n, m, maxi, mask[10];
pair< pair<int, int>, int > ans[21];
pair< pair<int, int>, int > res[21];

void gao(int i, int j, int cc) {
	if (j >= m) {
		gao(i + 1, 0, cc);
		return;
	}
	if (i >= n) {
		if (cc > maxi) {
			maxi = cc;
			for (int ii = 0; ii < cc; ++ii)
				ans[ii] = res[ii];
		}
		return;
	}
	if (maxi == opt[n][m])
		return;
	if (cc + (n - i) * m / 5 <= maxi)
		return;
	if (cc + opt[n - i][m] <= maxi)
		return;
	if (i + 3 <= n && j + 3 <= m) {
		// Try to put 1 of 4 patterns
		for (int pi = 0; pi < 4; ++pi) {
			bool ok = true;
			for (int ii = i; ii < i + 3; ++ii) {
				if (mask[ii] & (pat[pi][ii - i] << j)) {
					ok = false;
					break;
				}
			}
			if (ok) {
				for (int ii = i; ii < i + 3; ++ii) {
					mask[ii] |= (pat[pi][ii - i] << j);
				}
				res[cc] = make_pair(make_pair(i, j), pi);
				gao(i, j + 1, cc + 1);
				for (int ii = i; ii < i + 3; ++ii) {
					mask[ii] ^= (pat[pi][ii - i] << j);
				}
			}
		}
	}
	// Don't put
	gao(i, j + 1, cc);
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		maxi = 0;
		memset(ans, -1, sizeof(ans));
		gao(0, 0, 0);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j <= m; ++j)
				board[i][j] = (j == m ? '\n' : '.');
		for (int c = 0; c < maxi; ++c) {
			int pi = ans[c].second;
			int ii = ans[c].first.first;
			int jj = ans[c].first.second;
			for (int i = ii; i < ii + 3; ++i) {
				for (int j = jj; j < jj + 3; ++j) {
					if (pat[pi][i - ii] & (1 << (j - jj)))
						board[i][j] = 'A' + c;
				}
			}
		}
		printf("%d\n", maxi);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j)
				putchar(board[i][j]);
			putchar('\n');
		}
	}
	return 0;
}

