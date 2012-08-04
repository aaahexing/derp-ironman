#include <map>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

struct DisjointSet {
	int r[MAXN];
	int c[MAXN];
	void init(int n) {
		for (int i = 1; i <= n; ++i) {
			r[i] = i;
			c[i] = 1;
		}
	}
	int getRoot(int i) {
		if (r[i] != i)
			r[i] = getRoot(r[i]);
		return r[i];
	}
	int getC(int i) {
		return c[getRoot(i)];
	}
	void setRoot(int i, int j) {
		i = getRoot(i);
		j = getRoot(j);
		if (i != j) {
			c[i] += c[j];
			r[j] = i;
		}
	}
} ds;

struct EdgeNode {
	int i, a, b, d;
	bool operator< (const EdgeNode &e) const {
		return d < e.d;
	}
} edge[MAXN];

vector< pair<int, int> > adj[MAXN];
int n, vn, vi[MAXN], cc[MAXN], vv[MAXN], tot[MAXN], edge_c[MAXN], edge_t[MAXN];

int gao(int i, int *vi, int tot_i) {
	vv[i] = 1;
	int ret = cc[i];
	tot[tot_i] += cc[i];
	for (int j = 0; j < adj[i].size(); ++j) {
		pair<int, int> e = adj[i][j];
		if (!vv[e.second]) {
			edge_c[e.first] += gao(e.second, vi, tot_i);
			edge_t[e.first] = tot_i;
			ret += edge_c[e.first];
		}
	}
	return ret;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n - 1; ++i) {
			edge[i].i = i;
			scanf("%d%d%d", &edge[i].a, &edge[i].b, &edge[i].d);
		}
		ds.init(n);
		sort(edge + 1, edge + n);
		memset(edge_c, 0, sizeof(edge_c));
		vector<int> ans;
		long long most = 0;
		for (int s = 1; s <= n - 1; ) {
			int t = s + 1;
			while (t <= n - 1 && edge[t].d == edge[s].d) ++t;
			map<int, int> roots;
			for (int i = s; i < t; ++i) {
				int ra = ds.getRoot(edge[i].a);
				int rb = ds.getRoot(edge[i].b);
				roots[ra] = 1;
				roots[rb] = 1;
			}
			vn = 0;
			for (map<int, int> :: iterator it = roots.begin(); it != roots.end(); ++it) {
				vi[vn] = it->first;
				it->second = vn++;
			}
			int total = 0;
			for (int i = 0; i < vn; ++i) {
				cc[i] = ds.getC(vi[i]);
				total += cc[i];
				adj[i].clear();
			}
			for (int i = s; i < t; ++i) {
				int ss = roots[ds.getRoot(edge[i].a)];
				int tt = roots[ds.getRoot(edge[i].b)];
				adj[ss].push_back(make_pair(i, tt));
				adj[tt].push_back(make_pair(i, ss));
			}
			int tot_n = 0;
			memset(vv, 0, sizeof(int) * vn);
			for (int i = 0; i < vn; ++i) {
				if (!vv[i]) {
					tot[tot_n++] = 0;
					gao(i, vi, tot_n - 1);
				}
			}
			for (int i = s; i < t; ++i) {
				int vc = edge_c[i];
				int total = tot[edge_t[i]];
				edge_c[i] = vc * (total - vc);
				if (vc * 1LL * (total - vc) > most) {
					most = vc * 1LL * (total - vc);
					ans.clear();
				}
				if (vc * 1LL * (total - vc) == most) {
					ans.push_back(edge[i].i);
				}
			}
			for (int i = s; i < t; ++i)
				ds.setRoot(edge[i].a, edge[i].b);
			s = t;
		}
		sort(ans.begin(), ans.end());
		cout << most * 2 << " " << ans.size() << endl;
		for (int i = 0; i < ans.size(); ++i)
			cout << ans[i] << " ";
		cout << endl;
	}
	return 0;
}
