// https://kilonova.ro/submissions/380271

#include <iostream>

const int n = 1e6;

struct Node {
    int freq = 0;
    long long sum = 0;
}aint[4 * n + 1];


void update(int node, int left, int right, long long val) {
    if (left == right) {
        aint[node].sum += val;
        aint[node].freq += 1;
    } else {
        int middle = (left + right) >> 1;
        if (val <= middle) {
            update(node << 1, left, middle, val);
        } else {
            update(node << 1 | 1, middle + 1, right, val);
        }

        aint[node].sum = aint[node << 1].sum + aint[node << 1 | 1].sum;
        aint[node].freq = aint[node << 1].freq + aint[node << 1 | 1].freq;
    }
}

long long query(int node, int left, int right, long long val) {
    if (left == right) {
        if (aint[node].freq == 0) {
            return 0;
        } else {
            return (aint[node].sum / aint[node].freq) * val;
        }
    }

    int middle = (left + right) >> 1;
    if (val >= aint[node << 1].freq + 1) {
        return aint[node << 1].sum + query(node << 1 | 1, middle + 1, right, val - aint[node << 1].freq);
    } else {
        return query(node << 1, left, middle, val);
    }
}

int main() {
    //std::cout << sizeof(aint) << '\n';

    std::ios::sync_with_stdio(0);
    std::cin.tie(0);


    int queries; std::cin >> queries;
    for (int i = 0; i < queries; i += 1) {
        int type, val; std::cin >> type >> val;
        if (type == 1) {
            update(1, 1, n, 1LL * val);
        } else {
            std::cout << query(1, 1, n, 1LL * val) << '\n';
        }
    }
    return 0;
}