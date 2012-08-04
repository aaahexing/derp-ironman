#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
const int INFF = 1000000000;

int n, a, b, d; 
vector< pair<int, int> > adj[MAXN];

struct State {
	int dis;
	long long cnt;
	long long esum;
	long long cost;
public:
	State() {
		dis = 0;
		cnt = esum = cost = 0;
	}
	bool operator< (const State &s) const {
		return esum * s.cnt < cnt * s.esum;
	}
};

State gao(int i, int src) {
	State ret;
	vector<State> sub;
	for (int j = 0; j < adj[i].size(); ++j) {
		int ii = adj[i][j].first;
		if (ii != src) {
			sub.push_back(gao(ii, i));
			sub.back().dis = adj[i][j].second;
			sub.back().esum += sub.back().dis * 2;
		}
	}
	sort(sub.begin(), sub.end());
	++ret.cnt;
	int tbase = 0;
	for (int j = 0; j < sub.size(); ++j) {
		ret.cnt += sub[j].cnt;
		ret.esum += sub[j].esum;
		ret.cost += sub[j].cost + (tbase + sub[j].dis) * sub[j].cnt;
		tbase += sub[j].esum;
	}
	return ret;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i)
			adj[i].clear();
		for (int e = 0; e < n - 1; ++e) {
			scanf("%d%d%d", &a, &b, &d);
			adj[a].push_back(make_pair(b, d));
			adj[b].push_back(make_pair(a, d));
		}
		printf("%.12lf\n", 1.0 * gao(1, -1).cost / (n - 1));
	}
	return 0;
}
