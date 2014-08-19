#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int SEGMENT_COUNT = 7;
const int SEGMENT_STATE_MASK_COUNT = 1 << SEGMENT_COUNT;
// gfedcba
const int DIGIT_SEGMENT_MASKS[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};
// A table containing all the possible states.
int state_table[SEGMENT_STATE_MASK_COUNT][10];

// Output 10 corner cases for small dataset.
void OutputSmallCornerCases(int &case_i) {
    // seq: 9 -> 8 -> 7 -> 6 -> 5 -> ?
    // broken segments: b
    cout << "5 1011011 1011111 1010000 1011111 1011011" << endl;
    // 4
    cerr << "Case #" << ++case_i << ": 0010011" << endl;

    // seq: 8
    cout << "1 1111111" << endl;
    // Good LED.
    cerr << "Case #" << ++case_i << ": 1110000" << endl;

    // 5 -> 4 -> 3 -> 2 -> 1
    cout << "5 0000000 0000000 0000000 0000100 0000000" << endl;
    // 0
    cerr << "Case #" << ++case_i << ": 0000100" << endl;

    // 2 -> 1 -> 0 -> 9
    cout << "4 0001000 0010000 0011010 0011010" << endl;
    // 8
    cerr << "Case #" << ++case_i << ": 0011010" << endl;
}

// Output corner cases for large dataset.
void OutputLargeCornerCases(int &case_i) {
    // 9 -> 8 -> 7 -> 6 -> 5 -> 4 -> ? 
    // broken segments: a-g
    cout << "6 0000000 0000000 0000000 0000000 0000000 0000000" << endl;
    // 3
    cerr << "Case #" << ++case_i << ": 0000000" << endl;

    // seq: 8 -> 7 -> 6 -> 5 -> 4 -> 3
    // good LED
    cout << "6 1111111 1110000 1011111 1011011 0110011 1111001" << endl;
    // 2
    cerr << "Case #" << ++case_i << ": 1101101" << endl;

    // 1 -> 0 -> 9 ---> 4 or 0 -> 9 -> 8 ---> 3
    // a, b, d, e, f, g
    cout << "7 0010000 0010000 0010000 0010000 0010000 0010000 0010000"
         << endl;
    // 4 or 3
    cerr << "Case #" << ++case_i << ": ERROR!" << endl;

    cout << "2 1011001 0110001" << endl;
    cerr << "Case #" << ++case_i << ": 1111001" << endl;
}

string StateToDisplay(int state) {
    string result = "";
    for (int i = 0; i < SEGMENT_COUNT; ++i) {
        if (state & (1 << i)) {
            result += "1";
        } else {
            result += "0";
        }
    }
    return result;
}

inline int CalculateState(int digit, int mask) {
    return DIGIT_SEGMENT_MASKS[digit] & mask;
}

void ShowState(int state) {
    char m[7][4];
    memset(m, ' ', sizeof(m));
    if (state & 1) {
        m[0][1] = m[0][2] = '*';
    }
    if (state & 2) {
        m[1][3] = m[2][3] = '*';
    }
    if (state & 4) {
        m[4][3] = m[5][3] = '*';
    }
    if (state & 8) {
        m[6][1] = m[6][2] = '*';
    }
    if (state & 16) {
        m[4][0] = m[5][0] = '*';
    }
    if (state & 32) {
        m[1][0] = m[2][0] = '*';
    }
    if (state & 64) {
        m[3][1] = m[3][2] = '*';
    }
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 4; ++j) {
            cerr << m[i][j];
        }
        cerr << endl;
    }
    cerr << endl;
}

// Generate a table for all the possible states.
void GenerateStateTable() {
    for (int mask = 0; mask < SEGMENT_STATE_MASK_COUNT; ++mask) {
        for (int i = 0; i < 10; ++i) {
            state_table[mask][i] = DIGIT_SEGMENT_MASKS[i] & mask;
        }
    }
}

pair<int, int> GetNext(const vector<int> &states) {
    int next = -1;
    int count = 0;
    const int n = (int)states.size();
    if (n >= 10) {
        return make_pair(states[n % 10], 1);
    }
    for (int mask = 0; mask < SEGMENT_STATE_MASK_COUNT; ++mask) {
        for (int s = 0; s < 10; ++s) {
            bool found_position = true;
            for (int i = 0; i < n; ++i) {
                int expected = state_table[mask][(s + 10 - (i % 10)) % 10];
                if (states[i] != expected) {
                    found_position = false;
                    break;
                }
            }
            if (found_position) {
                int to_next = state_table[mask][(s + 10 - (n % 10)) % 10];
                if (next == -1 || next == to_next) {
                    next = to_next;
                    ++count;
                } else {
                    return make_pair(-1, 0);
                }
            }
        }
    }
    return make_pair(next, count);
}

inline int CountBroken(int mask) {
    int count = 0;
    for (int i = 0; i < SEGMENT_COUNT; ++i) {
        if (!(mask & (1 << i))) {
            ++count;
        }
    }
    return count;
}

// Output all cases whose sequence size is no more than 20.
void OutputAllCases(int &case_i, int case_n) {
    GenerateStateTable();

    const int max_sequence_n = 15;
    const int max_state_mask = SEGMENT_STATE_MASK_COUNT;
    for (int mask = 0; mask < max_state_mask && case_i < case_n; ++mask) {
        for (int n = 1; n <= max_sequence_n && case_i < case_n; ++n) {
            vector<int> states(n);
            for (int i = 0; i < n; ++i) {
                int ii = (0 + 10 - (i % 10)) % 10;
                states[i] = state_table[mask][ii];
            }
            pair<int, int> ans = GetNext(states);
            // The inputs.
            // Output the number of sequence to generate.
            cout << n;
            // Generate the sequence.
            for (int i = 0; i < n; ++i) {
                cout << " " << StateToDisplay(states[i]);
                // // for debugging.
                // ShowState(states[i]);
            }
            cout << endl;

            // The outputs.
            // The expected answer for the next state.
            cerr << "Case #" << ++case_i << ": ";
            // Determine the uniqueness.
            int next = ans.first;
            if (next == -1) {
                cerr << "ERROR!" << endl;
            } else {
                int next_state = CalculateState((0 + 10 - (n % 10)) % 10, mask);
                assert(next == next_state);
                cerr << StateToDisplay(next_state) << endl;
            }
        }
    }
}

// Output random cases here.
// Make sure that it won't generate the 'trickest' cases for small case.
void OutputRandomCases(int &case_i, int case_n, int level) {
    // Generate the mask table.
    GenerateStateTable();

    int max_broken = 0;
    int max_sequence_n = 0;
    int seen_sequence_n_mask = 0;
    if (level == 0) {
        max_broken = 2;
        max_sequence_n = 5;
    } else {
        max_broken = 7;
        max_sequence_n = 100;
    }
    // Generate the test cases.
    for (; case_i < case_n; ) {
        int s = rand() % 10;
        int mask = rand() % SEGMENT_STATE_MASK_COUNT;
        while (CountBroken(mask) > max_broken) {
            mask = rand() % SEGMENT_STATE_MASK_COUNT;
        }
        int n = rand() % max_sequence_n + 1;
        if (!(seen_sequence_n_mask & (1 << 0))) {
            n = 1;
        } else if (!(seen_sequence_n_mask & (1 << 1))) {
            n = max_sequence_n;
        }
        vector<int> states(n);
        for (int i = 0; i < n; ++i) {
            int num = (s + 10 - (i % 10)) % 10;
            states[i] = CalculateState(num, mask);
        }
        // Get the next state and its corresponding count.
        pair<int, int> ans = GetNext(states);
        // Use this case if it's for large data set or there's no tricky case.
        if (level == 1 || (ans.first == -1 || ans.second == 1)) {
            // Set the completness flag.
            if (n == 1) {
                seen_sequence_n_mask |= (1 << 0);
            } else if (n == max_sequence_n) {
                seen_sequence_n_mask |= (1 << 1);
            }
            // The inputs.
            // Output the number of sequence to generate.
            cout << n;
            // Generate the sequence.
            for (int i = 0; i < n; ++i) {
                cout << " " << StateToDisplay(states[i]);
                // // for debugging.
                // ShowState(states[i]);
            }
            cout << endl;

            // The outputs.
            // The expected answer for the next state.
            cerr << "Case #" << ++case_i << ": ";
            // Determine the uniqueness.
            int next = ans.first;
            if (next == -1) {
                cerr << "ERROR!" << endl;
            } else {
                int next_state = CalculateState((s + 10 - (n % 10)) % 10, mask);
                assert(next == next_state);
                cerr << StateToDisplay(next_state) << endl;
            }
        }
    }
}

void OutputCases(int level) {
    int case_i = 0;
    int case_n = 100;
    if (level == 1) {
        case_n = 2000;
    }
    cout << case_n << endl;
    if (level == 0) {
        OutputSmallCornerCases(case_i);
    } else {
        // OutputLargeCornerCases.
        OutputLargeCornerCases(case_i);
        OutputAllCases(case_i, case_n);
    }
    OutputRandomCases(case_i, case_n, level);
}

int main(int argc, char *argv[]) {
    assert(argc == 3);
    int level = atoi(argv[1]);
    int seed = atoi(argv[2]);

    srand(seed);
    OutputCases(level);

    return 0;
}
