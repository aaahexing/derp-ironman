#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000010;

inline int lowbit(int x) {
	return (x & (-x));
}

template<typename T>
class BITree {
	int n;
	T a[MAXN], c[MAXN], ret;
public:
	void init(int _n) {
		n = _n;
		memset(a, 0, sizeof(a));
		memset(c, 0, sizeof(c));
	}
	void add(int i, T v) {
		for (; i <= n; i += lowbit(i)) {
			c[i] += v;
		}
	}
	void update(int i, T v) {
		v -= a[i];
		a[i] += v;
		add(i, v);
	}
	T query(int i) {
		for (ret = 0; i; i -= lowbit(i)) {
			ret += c[i];
		}
		return ret;
	}
};

long long ans;
BITree<int> g_tree;
BITree<int> s_tree;
pair<int, int> pr[MAXN];
int n, a[MAXN], s[MAXN], g[MAXN];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			pr[i] = make_pair(a[i], i);
		}
		sort(pr + 1, pr + 1 + n);
		for (int i = 1; i <= n; ++i)
			a[ pr[i].second ] = i;
		s_tree.init(n);
		for (int i = n; i >= 1; --i) {
			s[i] = s_tree.query(a[i] - 1);
			s_tree.add(a[i], 1);
		}
		g_tree.init(n);
		for (int i = 1; i <= n; ++i) {
			g[i] = g_tree.query(n) - g_tree.query(a[i]);
			g_tree.add(a[i], 1);
		}
		ans = 0;
		for (int i = 1; i <= n; ++i)
			ans += s[i] * 1LL * g[i];
		cout << ans << endl;
	}
	return 0;
}
