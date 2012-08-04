#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int n, a[MAXN], v[MAXN];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; ++i)
			scanf("%d", &a[i]);
		sort(a, a + n, greater<int>());
		if (a[n - 1] != 0) {
			puts("-1");
		} else {
			int s = 0;
			for (int i = 0; i < n; ++i)
				s += a[i];
			memset(v, 0, sizeof(v));
			s %= 3;
			if (s) {
				vector< pair<int, int> > vv[2];
				for (int i = 0; i < n; ++i) {
					if (a[i] % 3 == 1) {
						vv[0].push_back(make_pair(a[i], i));
					} else if (a[i] % 3 == 2) {
						vv[1].push_back(make_pair(a[i], i));
					}
				}
				sort(vv[0].begin(), vv[0].end());
				sort(vv[1].begin(), vv[1].end());
				if (vv[s - 1].size() > 0) {
					v[vv[s - 1][0].second] = 1;
					s = 0;
				} else if (vv[2 - s].size() > 1) {
					v[vv[2 - s][0].second] = 1;
					v[vv[2 - s][1].second] = 1;
					s = 0;
				}
			}
			if (s != 0) {
				puts("-1");
			} else {
				int head_zero = 0;
				for (int i = 0; i < n; ++i) {
					if (!v[i]) {
						if (head_zero == 1)
							break;
						if (head_zero == 0)
							head_zero = (a[i] == 0 ? 1 : 2);
						putchar('0' + a[i]);
					}
				}
				putchar('\n');
			}
		}
	}
	return 0;
}
