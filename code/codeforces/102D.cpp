#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 200010;
const int MODD = 1000000007;

struct Stop {
	int s, t;
	bool operator< (const Stop &ss) const {
		return t < ss.t;
	}
} bus[MAXN];

int n, m, nn, dp[MAXN], sum[MAXN];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		map<int, int> stops;
		stops[0] = stops[n] = 0;
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &bus[i].s, &bus[i].t);
			stops[bus[i].s] = stops[bus[i].t] = 0;
		}
		nn = 0;
		for (map<int, int> :: iterator it = stops.begin(); it != stops.end(); ++it)
			it->second = ++nn;
		sort(bus, bus + m);
		int bi = 0;
		dp[1] = sum[1] = 1;
		for (int i = 2; i <= nn; ++i) {
			dp[i] = 0;
			for (; bi < m && stops[bus[bi].t] == i; ++bi) {
				int ms = stops[bus[bi].s];
				int mt = stops[bus[bi].t];
				dp[i] = ((long long)dp[i] + sum[mt - 1] - sum[ms - 1] + MODD) % MODD;
			}
			sum[i] = ((long long)sum[i - 1] + dp[i]) % MODD;
		}
		printf("%d\n", dp[nn]);
	}
	return 0;
}
