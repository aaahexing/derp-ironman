#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 51;
const int MAXL = 5010;
const int MAXM = 250010;

int n, m, l[MAXN], a[MAXN][MAXL];
long long ans, sum, ldp[MAXN], rdp[MAXN], mdp[MAXN], sdp[MAXN], dp[MAXM];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &l[i]);
			int *aa = a[i];
			const int ln = l[i];
			sdp[i] = 0;
			for (int j = 1; j <= ln; ++j) {
				scanf("%d", &aa[j]);
				sdp[i] += aa[j];
			}
			sum = 0;
			ldp[i] = -100000;
			for (int j = 1; j <= ln; ++j) {
				sum += aa[j];
				ldp[i] = max(ldp[i], sum);
			}
			sum = 0;
			rdp[i] = -100000;
			for (int j = ln; j >= 1; --j) {
				sum += aa[j];
				rdp[i] = max(rdp[i], sum);
			}
			sum = 0;
			mdp[i] = -100000;
			for (int j = 1; j <= ln; ++j) {
				sum = max(sum + aa[j], (long long)aa[j]);
				mdp[i] = max(mdp[i], sum);
			}
		}
		dp[0] = 0;
		ans = -100000;
		for (int i = 1; i <= m; ++i) {
			int ii = 0;
			scanf("%d", &ii);
			dp[i] = max(rdp[ii], sdp[ii] + dp[i - 1]);
			ans = max(ans, dp[i]);
			ans = max(ans, mdp[ii]);
			ans = max(ans, dp[i - 1] + ldp[ii]);
		}
		cout << ans << endl;
	}
	return 0;
}

