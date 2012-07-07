#include <map>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

long long ans;
int n, s, sum, a[MAXN];

int main() {
	while (scanf("%d", &n) != EOF) {
		sum = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			sum += a[i];
		}
		if (sum % 3) {
			puts("0");
		} else {
			sum /= 3;
			s = ans = 0;
			map<int, int> mp;
			for (int i = 1; i <= n; ++i) {
				s += a[i];
				if (s == sum * 2 && i < n) {
					ans += mp[sum];
				}
				++mp[s];
			}
			cout << ans << endl;
		}
	}
	return 0;
}
