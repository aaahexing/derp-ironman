#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int d[] = { -1, 1 };

int n, m;
char s[151][151];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 0; i < n; ++i)
			scanf("%s", s[i]);
		int rem = 0;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				rem += (s[i][j] == 'W');
		rem -= (s[0][0] == 'W');
		int ans = 0;
		int i = 0, j = 0, dir = 1;
		while (rem > 0) {
			if (dir == 1) {
				for (int jj = j + 1; jj < m; ++jj) {
					if (s[i][jj] == 'W' || (i + 1 < n && s[i + 1][jj] == 'W')) {
						++j;
						++ans;
						goto NEXT;
					}
				}
				++i;
				++ans;
				dir = 1 - dir;
			} else {
				for (int jj = j - 1; jj >= 0; --jj) {
					if (s[i][jj] == 'W' || (i + 1 < n && s[i + 1][jj] == 'W')) {
						--j;
						++ans;
						goto NEXT;
					}
				}
				++i;
				++ans;
				dir = 1 - dir;
			}
			NEXT:;
			if (s[i][j] == 'W')
				--rem;
		}
		printf("%d\n", ans);
	}
}

