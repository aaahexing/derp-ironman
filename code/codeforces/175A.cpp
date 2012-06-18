#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char s[32];
int n, ans;

inline int getNum(int l, int r) {
	if (s[l] == '0' && r - l > 1)
		return -1;
	int ret = 0;
	for (int i = l; i < r; ++i) {
		ret = ret * 10 + s[i] - '0';
		if (ret > 1000000)
			return -1;
	}
	return ret;
}

int main() {
	while (scanf("%s", s) != EOF) {
		ans = -1;
		n = strlen(s);
		for (int l = 1; l <= n; ++l) {
			for (int r = l + 1; r < n; ++r) {
				int a = getNum(0, l);
				int b = getNum(l, r);
				int c = getNum(r, n);
				if (a >= 0 && b >= 0 && c >= 0)
					ans = max(ans, a + b + c);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
