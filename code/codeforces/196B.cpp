#include <set>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int INFF = 1000000000;
const int di[] = { -1, 0, 1, 0 };
const int dj[] = { 0, -1, 0, 1 };

int n, m, si, sj;
pair<int, int> pr[1510][1510];
char a[1510][1510], v[1510][1510];

bool go(int i, int j) {
	int mi = ((i % n) + n) % n, mj = ((j % m) + m) % m;
	if (a[mi][mj] == '#')
		return false;
	if (pr[mi][mj].first != INFF)
		return pr[mi][mj].first != i || pr[mi][mj].second != j;
	pr[mi][mj] = make_pair(i, j);
	for (int dd = 0; dd < 4; ++dd) {
		if (go(i + di[dd], j + dj[dd]))
			return true;
	}
	return false;
}

bool gao() {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			pr[i][j] = make_pair(INFF, INFF);
	return go(si, sj);
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 0; i < n; ++i)
			scanf("%s", a[i]);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (a[i][j] == 'S') {
					si = i, sj = j;
				}
			}
		}
		printf("%s\n", gao() ? "Yes" : "No");
	}
	return 0;
}
