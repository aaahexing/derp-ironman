#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

long long n, ans, sum, a[MAXN];

int main() {
	while (cin >> n) {
		for (int i = 0; i < n; ++i)
			cin >> a[i];
		ans = sum = 0;
		for (int i = 1; i < n; ++i) {
			if (a[i] + sum < a[i - 1]) {
				ans += (a[i - 1] - a[i] - sum);
				sum += (a[i - 1] - a[i] - sum);
			}
			a[i] += sum;
		}
		cout << ans << endl;
	}
	return 0;
}
