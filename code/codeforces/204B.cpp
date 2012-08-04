#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

map<int, int> mp;
int n, color_n, c0[MAXN * 2], c1[MAXN * 2];

inline int getI(int c) {
	if (mp.find(c) == mp.end()) {
		mp[c] = color_n;
		++color_n;
	}
	return mp[c];
}

int main() {
	while (scanf("%d", &n) != EOF) {
		color_n = 0;
		mp.clear();
		memset(c0, 0, sizeof(c0));
		memset(c1, 0, sizeof(c1));
		for (int i = 0; i < n; ++i) {
			int a, b;
			scanf("%d%d", &a, &b);
			int ai = getI(a), bi = getI(b);
			++c0[ai];
			if (bi != ai)
				++c1[bi];
		}
		int ans = -1;
		int least = (n + 1) / 2;
		for (int ci = 0; ci < color_n; ++ci) {
			int op = -1;
			if (c0[ci] >= least) {
				op = 0;
			} else {
				if (c1[ci] + c0[ci] >= least) {
					op = least - c0[ci];
				}
			}
			if (op != -1) {
				if (ans == -1 || op < ans) {
					ans = op;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
