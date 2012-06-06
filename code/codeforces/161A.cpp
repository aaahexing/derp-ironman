#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, x, y, a[100010], b[100010];

int main() {
	scanf("%d%d%d%d", &n, &m, &x, &y);
	for (int i = 0; i < n; ++i)
		scanf("%d", &a[i]);
	for (int j = 0; j < m; ++j)
		scanf("%d", &b[j]);
	sort(a, a + n);
	sort(b, b + m);
	int ap = 0;
	vector< pair<int, int> > ans;
	for (int j = 0; j < m && ap < n; ++j) {
		while (ap < n && b[j] > a[ap] + y)
			++ap;
		if (ap < n && b[j] >= a[ap] - x) {
			ans.push_back(make_pair(ap + 1, j + 1));
			++ap;
		}
	}
	int tot = ans.size();
	printf("%d\n", tot);
	for (int i = 0; i < tot; ++i)
		printf("%d %d\n", ans[i].first, ans[i].second);
	return 0;
}
