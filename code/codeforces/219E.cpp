#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 200010;
const int MAXSEG = (262144) * 2;

class SegTree {
	int n;
	int lsum[MAXSEG];
	int rsum[MAXSEG];
	pair<int, int> msum[MAXSEG];
public:
	inline int lson(int rt) {
		return rt << 1;
	}
	inline int rson(int rt) {
		return (rt << 1) | 1;
	}
	
	inline void pushUp(int rt, int l, int r) {
		int m = (l + r) >> 1;
		lsum[rt] = lsum[lson(rt)];
		rsum[rt] = rsum[rson(rt)];
		if (lsum[rt] == m - l) {
			lsum[rt] += lsum[rson(rt)];
		}
		if (rsum[rt] == r - m) {
			rsum[rt] += rsum[lson(rt)];
		}
		msum[rt] = make_pair(-1, -2);
		if (msum[lson(rt)].second - msum[lson(rt)].first > msum[rt].second - msum[rt].first) {
			msum[rt] = msum[lson(rt)];
		}
		if (lsum[rson(rt)] + rsum[lson(rt)] > msum[rt].second - msum[rt].first) {
			msum[rt] = make_pair(m - rsum[lson(rt)], m + lsum[rson(rt)]);
		}
		if (msum[rson(rt)].second - msum[rson(rt)].first > msum[rt].second - msum[rt].first) {
			msum[rt] = msum[rson(rt)];
		}
	}
	void init(int rt, int l, int r) {
		if (r - l == 1) {
			lsum[rt] = rsum[rt] = 1;
			msum[rt] = make_pair(l, r);
			return;
		}
		int m = (l + r) >> 1;
		init(lson(rt), l, m);
		init(rson(rt), m, r);
		pushUp(rt, l, r);
	}
	void update(int rt, int l, int r, int i, int d) {
		if (r - l == 1) {
			lsum[rt] = rsum[rt] = d;
			msum[rt] = (d > 0 ? make_pair(l, r) : make_pair(-1, -2));
			return;
		}
		int m = (l + r) >> 1;
		if (i < m) {
			update(lson(rt), l, m, i, d);
		} else {
			update(rson(rt), m, r, i, d);
		}
		pushUp(rt, l, r);
	}
	int findFirst(int rt, int l, int r, int w) {
		if (r - l == 1) {
			return l;
		}
		int m = (l + r) >> 1;
		if (msum[lson(rt)].second - msum[lson(rt)].first >= w) {
			return findFirst(lson(rt), l, m, w);
		} else if (rsum[lson(rt)] + lsum[rson(rt)] >= w) {
			return m - rsum[lson(rt)];
		} else {
			return findFirst(rson(rt), m, r, w);
		}
	}
	// [1, ?) 
	int findLeftLongest() {
		return lsum[1];
	}
	// [?, n + 1)
	int findRightLongest() {
		return rsum[1];
	}
	pair<int, int> findMax() {
		return msum[1];
	}

	// interfaces
	inline void init(int _n) {
		n = _n;
		init(1, 1, _n + 1);
	}
	inline int push(int i) {
		pair<int, int> seg = findMax();
		int ii = (seg.first + seg.second) >> 1;
		// printf("seg = [%d, %d)\n", seg.first, seg.second);
		// first
		if (seg.first == 1) {
			ii = 1;
		} else if (seg.second == n + 1) {
			ii = n;
		} else {
			int ll = seg.second - seg.first;
			int tar = ll / 2;
			ii = (seg.first + seg.second) >> 1;
			if (ll % 2 == 0) {
				--tar;
				int l = findFirst(1, 1, n + 1, ll - 1);
				seg = make_pair(l, l + ll - 1);
				ii = (seg.first + seg.second) >> 1;
			}
			if (findLeftLongest() - 1 >= tar) {
				tar = findLeftLongest() - 1;
				ii = 1;
			}
			if (findRightLongest() - 1 > tar) {
				tar = findRightLongest() - 1;
				ii = n;
			}
		}
		update(1, 1, n + 1, ii, 0);
		return ii;
	}
	inline void pop(int ii) {
		update(1, 1, n + 1, ii, 1);
	}
} seg;

int n, m, t, d, s[1000010];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		seg.init(n);
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &t, &d);
			if (t == 1) {
				s[d] = seg.push(d);
				printf("%d\n", s[d]);
			} else {
				seg.pop(s[d]);
			}
		}
	}	
	return 0;
}
