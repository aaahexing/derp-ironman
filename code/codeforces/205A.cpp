#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
	int n, a;
	while (scanf("%d", &n) != EOF) {
		vector< pair<int, int> > v(n);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &v[i].first);
			v[i].second = i + 1;
		}
		sort(v.begin(), v.end());
		if (v.size() >= 2 && v[0].first == v[1].first)
			puts("Still Rozdil");
		else {
			printf("%d\n", v[0].second);
		}
	}
	return 0;
}
