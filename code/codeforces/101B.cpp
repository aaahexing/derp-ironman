#include <map>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 200100;
const int MODD = 1000000007;

struct Bus {
	int s, t;
};

inline bool operator< (const Bus &l, const Bus &r) {
	return l.t < r.t;
}

map<int, int> mi;
Bus bus[MAXN / 2];
int n, m, dp[MAXN], sum[MAXN];

int makeIndex() {
	mi.clear();
	mi[0] = mi[n] = 0;
	for (int i = 0; i < m; ++i)
		mi[bus[i].s] = mi[bus[i].t] = 0;
	int nn = 0;
	for (map<int, int>::iterator it = mi.begin(); it != mi.end(); ++it)
		it->second = nn++;
	return nn;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 0; i < m; ++i)
			scanf("%d%d", &bus[i].s, &bus[i].t);
		int bi = 0;
		n = makeIndex();
		dp[0] = 1;
		sum[0] = 0;
		sum[1] = 1;
		sort(bus, bus + m);
		for (int i = 1; i < n; ++i) {
			dp[i] = 0;
			for (; bi < m && mi[bus[bi].t] == i; ++bi) {
				int ll = mi[bus[bi].s];
				int rr = mi[bus[bi].t];
				dp[i] = ((long long)dp[i] + sum[rr] - sum[ll] + MODD) % MODD;
			}
			sum[i + 1] = ((long long)sum[i] + dp[i]) % MODD;
		}
		printf("%d\n", dp[n - 1]);
	}
	return 0;
}
