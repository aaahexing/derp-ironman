#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1024;
const long long INFF = (1LL << 62);

int n, m, x, y, a[MAXN][MAXN];
long long row[MAXN], col[MAXN];

inline long long sqr(long long x) {
	return x * x;
}

inline long long gaoI(int &x) {
	long long cost, mini = INFF;
	for (int i = 0; i <= n + n; i += 2) {
		cost = 0;
		for (int r = 1; r <= n; ++r)
			cost += row[r] * sqr((i - (r * 2 - 1)) * 2);
		if (mini > cost) {
			mini = cost;
			x = i / 2;
		}
	}
	return mini;
}

inline long long gaoJ(int &y) {
	long long cost, mini = INFF;
	for (int j = 0; j <= m + m; j += 2) {
		cost = 0;
		for (int c = 1; c <= m; ++c)
			cost += col[c] * sqr((j - (c * 2 - 1)) * 2);
		if (mini > cost) {
			mini = cost;
			y = j / 2;
		}
	}
	return mini;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(row, 0, sizeof(row));
		memset(col, 0, sizeof(col));
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &a[i][j]);
				row[i] += a[i][j];
				col[j] += a[i][j];
			}
		}
		cout << gaoI(x) + gaoJ(y) << endl;
		cout << x << " " << y << endl;
	}
	return 0;
}
