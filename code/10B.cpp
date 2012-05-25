#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, k, m, ax, ay, cx, cy;
int d[100][100], s[100][100];

void take(int ax, int ay, int m) {
	for (int y = ay; y < ay + m; ++y) {
		for (int i = y; i <= k; ++i)
			++s[ax][i];
	}
}

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		cx = cy = (k + 1) / 2;
		memset(s, 0, sizeof(s));
		for (int x = 1; x <= k; ++x)
			for (int y = 1; y <= k; ++y)
				d[x][y] = d[x][y - 1] + abs(x - cx) + abs(y - cy);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &m);
			int ax = -1, ay = -1, mini = 1000000000;
			for (int x = 1; x <= k; ++x) {
				for (int y = 1; y + m - 1 <= k; ++y) {
					if (s[x][y + m - 1] - s[x][y - 1] == 0) {
						if (d[x][y + m - 1] - d[x][y - 1] < mini) {
							ax = x, ay = y;
							mini = d[x][y + m - 1] - d[x][y - 1];
						}
					}
				}
			}
			if (ax == -1) {
				puts("-1");
			} else {
				take(ax, ay, m);
				printf("%d %d %d\n", ax, ay, ay + m - 1);
			}
		}
	}
	return 0;
}
