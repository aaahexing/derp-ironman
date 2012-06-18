#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 3010;
const long long INFF = MAXN * 1000000000LL;

struct Marble {
	int x, c;	
} a[MAXN];

inline bool operator< (const Marble &l, const Marble &r) {
	return l.x < r.x;
}

int n;
long long s[MAXN], dp[MAXN][2];

inline long long cost(int i, int j) {
	return s[i] - s[j - 1] - (i - j + 1) * 1LL * a[j].x; 
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i)
			scanf("%d%d", &a[i].x, &a[i].c);
		sort(a + 1, a + 1 + n);
		s[0] = 0;
		for (int i = 1; i <= n; ++i)
			s[i] = s[i - 1] + a[i].x;
		dp[1][0] = INFF;
		dp[1][1] = a[1].c;
		for (int i = 2; i <= n; ++i) {
			dp[i][0] = dp[i][1] = INFF;
			// Pin
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + a[i].c;
			// No pin
			for (int j = 1; j < i; ++j)
				dp[i][0] = min(dp[i][0], dp[j][1] + cost(i, j));
		}
		cout << min(dp[n][0], dp[n][1]) << endl;
	}
	return 0;
}
