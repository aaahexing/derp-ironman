#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

vector<int> v;
char s[1000010];
int l, r, n, ans;

int main() {
	while (scanf("%s", s) != EOF) {
		v.clear();
		n = strlen(s);
		for (r = n - 1; r >= 0; ) {
			for (; r >= 0 && s[r] == '0'; --r);
			if (r < 0)
				break;
			for (l = r; l >= 0 && s[l] == '1'; --l);
			// [l + 1, r]
			if (r - l == 1) {
				v.push_back(n - 1 - r + 1000010);
			} else {
				v.push_back(n - 1 - r);
				for (int i = r; i > l; --i)
					s[i] = '0';
				if (l >= 0) {
					s[l] = '1';
				} else {
					v.push_back(n + 1000010);
				}
			}
			r = l;
		}
		printf("%d\n", v.size());
		for (int i = 0; i < v.size(); ++i)
			printf("%c2^%d\n", v[i] >= 1000010 ? '+' : '-', v[i] >= 1000010 ? v[i] - 1000010 : v[i]);
	}
	return 0;
}
