/**
 * Sample solution.
 *
 * Problem: Seven Segment Display.
 * Author: Xing He (xinghe@google.com)
 *
 * Sample input (sequence of "9 -> 8 -> 7 -> 6 -> 5", segment 'b' is broken):
 * 5
 * 1011011
 * 1011111
 * 1010000
 * 1011111
 * 1011011
 *
 * Sample output ("4", segment 'b' is broken):
 * 0010011
 *
 */
#include <cstdio>
#include <vector>
using namespace std;

/*

   * The display examples for the digits:

 -----           -----   -----           -----   -----   -----   -----   -----
|     |       |       |       | |     | |       |             | |     | |     |
|     |       |       |       | |     | |       |             | |     | |     |
|     |       |       |       | |     | |       |             | |     | |     |
                 -----   -----   -----   -----   -----           -----   -----
|     |       | |             |       |       | |     |       | |     |       |
|     |       | |             |       |       | |     |       | |     |       |
|     |       | |             |       |       | |     |       | |     |       |
 -----           -----   -----           -----   -----           -----   -----

   * The individual segments of a seven-segment display:

                                   --a-- 
                                  |     |
                                  f     b
                                  |     |
                                   --g--
                                  |     |
                                  e     c
                                  |     |
                                   --d--

   * Then the corresponding masks for digits above(in the order of "abcdefg"):

1111110 0110000 1101101 1111001 0110011 1011011 1011111 1110000 1111111 1111011

*/

const int SEGMENT_COUNT = 7;
const int SEGMENT_STATE_MASK_COUNT = 1 << SEGMENT_COUNT;
// For convenience, use the order of "gfedcba" here.
const int DIGIT_SEGMENT_MASKS[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

int gao(const vector<int> &sequence) {
    // Try all the possibilities of the starting number.
    int ans = -1;
    const int n = (int)sequence.size();
    // if (n >= 10) {
    //     return sequence[n % 10];
    // }
    for (int s = 9; s >= 0; --s) {
        bool ok = true;
        int segment_bad = 0;
        int segment_good = 0;
        for (int i = 0; i < n; ++i) {
            int expected = (s + 10 - (i % 10)) % 10;
            int broken_mask = sequence[i] ^ DIGIT_SEGMENT_MASKS[expected];
            if ((broken_mask & sequence[i]) != 0) {
                // Conflict!
                // Some segments should not be litted for the expected
                // number but are litted now!
                ok = false;
                break;
            }
            // Some segments are surely bad.
            segment_bad |= broken_mask;
            // Some segments are surely good.
            segment_good |= sequence[i];
        }
        if (ok) {
            // No conflict found, but there may still be broken segments.
            int next = (s + 10 - (n % 10)) % 10;
            // Loop all the valid subset of states for good segments.
            for (int mask = 0; mask < SEGMENT_STATE_MASK_COUNT; ++mask) {
                if ((segment_good & mask) == segment_good
                        && (segment_bad & mask) == 0) {
                    int to_show = DIGIT_SEGMENT_MASKS[next] & mask;
                    if (ans == -1 || to_show == ans) {
                        ans = to_show;
                    } else {
                        return -1;
                    }
                }
            }
        }
    }
    // We can determine the final state.
    return ans;
}

int main(int argc, char* argv[]) {
    int n, case_n;
    char state[16];
    scanf("%d", &case_n);
    for (int ca = 1; ca <= case_n; ++ca) {
        scanf("%d", &n);
        vector<int> sequence(n);
        for (int i = 0; i < n; ++i) {
            sequence[i] = 0;
            scanf("%s", state);
            for (int j = 0; state[j]; ++j) {
                if (state[j] == '1') {
                    sequence[i] |= (1 << j);
                }
            }
        }

        int ans = gao(sequence);
        printf("Case #%d: ", ca);
        if (ans == -1) {
            puts("ERROR!");
        } else {
            for (int i = 0; i < SEGMENT_COUNT; ++i) {
                putchar((ans & (1 << i)) > 0 ? '1' : '0');
            }
            puts("");
        }
    }
    return 0;
}
