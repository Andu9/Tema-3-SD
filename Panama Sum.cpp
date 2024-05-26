// https://kilonova.ro/submissions/382211

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

struct values {
    long long totalSum;
    long long prefSum, sufSum;
    long long maxSum;
};

void update(std::vector<values>& aint, int node, int val) {
    aint[node].totalSum = aint[node].maxSum = val;
    aint[node].prefSum = aint[node].sufSum = val;
}

void updateAINT(std::vector<values>& aint, int left, int right, int node, int pos, int val) {
    if (left == right) {
        update(aint, node, val);
    } else {
        int middle = (left + right) >> 1;
        if (pos <= middle) {
            updateAINT(aint, left, middle, node << 1, pos, val);
        } else {
            updateAINT(aint, middle + 1, right, node << 1 | 1, pos, val);
        }

        aint[node].totalSum = aint[node << 1].totalSum + aint[node << 1 | 1].totalSum;
        aint[node].prefSum = std::max(aint[node << 1].prefSum, aint[node << 1].totalSum + aint[node << 1 | 1].prefSum);
        aint[node].sufSum = std::max(aint[node << 1 | 1].sufSum, aint[node << 1 | 1].totalSum + aint[node << 1].sufSum);
        aint[node].maxSum = std::max({aint[node << 1].maxSum,
                                      aint[node << 1 | 1].maxSum,
                                      aint[node << 1].sufSum + aint[node << 1 | 1].prefSum
                                     });
    }
}

long long sumPrefix, maxim;

void query(std::vector<values>& aint, int left, int right, int leftQuery, int rightQuery, int node) {
    if (leftQuery <= left && right <= rightQuery) {
        maxim = std::max({maxim, aint[node].maxSum, sumPrefix + aint[node].prefSum});
        sumPrefix = std::max(sumPrefix + aint[node].totalSum, aint[node].sufSum);
    } else {
        int middle = (left + right) >> 1;
        if (leftQuery <= middle) {
            query(aint, left, middle, leftQuery, rightQuery, node << 1);
        }
        if (middle < rightQuery) {
            query(aint, middle + 1, right, leftQuery, rightQuery, node << 1 | 1);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, q; std::cin >> n >> q;
    std::vector<values> posAINT(4 * n + 1), negAINT(4 * n + 1);
    for (int i = 1; i <= n; i += 1) {
        long long val; std::cin >> val;

        if (i & 1) {
            updateAINT(posAINT, 1, n, 1, i, val);
            updateAINT(negAINT, 1, n, 1, i, -val);
        } else {
            updateAINT(posAINT, 1, n, 1, i, -val);
            updateAINT(negAINT, 1, n, 1, i, val);
        }
    }

    for (int i = 0; i < q; i += 1) {
        int type, a, b; std::cin >> type >> a >> b;
        if (type == 1) {
            if (a & 1) {
                updateAINT(posAINT, 1, n, 1, a, b);
                updateAINT(negAINT, 1, n, 1, a, -b);
            } else {
                updateAINT(posAINT, 1, n, 1, a, -b);
                updateAINT(negAINT, 1, n, 1, a, b);
            }
        } else {
            maxim = LLONG_MIN, sumPrefix = 0;
            query(posAINT, 1, n, a, b, 1);

            long long temp = maxim;

            maxim = INT_MIN, sumPrefix = 0;
            query(negAINT, 1, n, a, b, 1);

            std::cout << std::max(temp, maxim) << '\n';
        }
    }
    return 0;
}