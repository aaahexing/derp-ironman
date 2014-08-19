#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int gao(int n, int m, int tar[]) {
    int ans = 0;
    vector< pair<int, int> > rects;
    for (int i = 0; i < n; ++i) {
        tar[i] = 1 << tar[i];
    }
    sort(tar, tar + n);
    for (int i = n - 1; i >= 0; ) {
        // Find whether there're valid tiles to cut.
        bool can_cut = false;
        for (int j = 0; j < rects.size(); ++j) {
            if (rects[j].first <= 0) {
                continue;
            }
            if (rects[j].first >= tar[i] && rects[j].second >= tar[i]) {
                if (rects[j].first > tar[i]) {
                    rects.push_back(make_pair(rects[j].first - tar[i],
                                              tar[i]));
                }
                if (rects[j].second > tar[i]) {
                    rects.push_back(make_pair(tar[i],
                                              rects[j].second - tar[i]));
                }
                if (rects[j].first > tar[i] && rects[j].second > tar[i]) {
                    rects.push_back(make_pair(rects[j].first - tar[i],
                                              rects[j].second - tar[i]));
                }
                rects[j].first = -1;
                can_cut = true;
                break;
            }
        }
        if (can_cut) {
            --i;
        } else {
            // Buy one more!
            rects.push_back(make_pair(m, m));
            ++ans;
        }
    }
    return ans;
}

int main(int argc, char *argv[]) {
    int cas, n, m, tar[1024];
    scanf("%d", &cas);
    for (int ca = 1; ca <= cas; ++ca) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &tar[i]);
        }
        printf("Case #%d: %d\n", ca, gao(n, m, tar));
    }
    return 0;
}
