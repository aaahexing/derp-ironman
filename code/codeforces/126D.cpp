#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int cas, dc, dci[88];
long long n, fib[88], dp[88][2];

int main() {
	fib[0] = fib[1] = 1;
	for (int i = 2; i < 88; ++i)
		fib[i] = fib[i - 1] + fib[i - 2];
	cin >> cas;
	while (cas--) {
		cin >> n;
		dc = 1;
		for (int i = 87; i >= 1 && n; --i) {
			if (n >= fib[i]) {
				dci[dc++] = i;
				n -= fib[i];
			}
		}
		reverse(dci + 1, dci + dc);
		--dc;
		dp[0][0] = 1;
		dp[0][1] = 0;
		int length = dci[1] - 1;
		for (int i = 1; i <= dc; ++i) {
			dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
			dp[i][1] = dp[i - 1][0] * (length / 2) + dp[i - 1][1] * ((length + 1) / 2);
			length = dci[i + 1] - dci[i] - 1;
		}
		cout << dp[dc][0] + dp[dc][1] << endl;
	}
	return 0;
}
