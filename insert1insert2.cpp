// https://kilonova.ro/submissions/382189

#include <iostream>
#include <vector>
#include <array>

const int mod = 666013;

struct query {
    int tip;
    int pos, val;
};

void update(std::vector<int>& aint, int node, int left, int right, int pos, int val) {
    if (left == right) {
        aint[node] = val;
    } else {
        int middle = (left + right) >> 1;
        if (pos <= middle) {
            update(aint, node << 1, left, middle, pos, val);
        } else {
            update(aint, node << 1 | 1, middle + 1, right, pos, val);
        }

        aint[node] = (aint[node << 1] + aint[node << 1 | 1]) % mod;
    }
}

int findKth(std::vector<int>& aint, int node, int left, int right, int k) {
    if (left == right) {
        return left;
    } else {
        int middle = (left + right) >> 1;
        if (k <= aint[node << 1]) {
            return findKth(aint, node << 1, left, middle, k);
        } else {
            return findKth(aint, node << 1 | 1, middle + 1, right, k - aint[node << 1]);
        }
    }
}

int suma;

void Query(std::vector<int>& aint, int node, int left, int right, int leftQuery, int rightQuery) {
    if (leftQuery <= left && right <= rightQuery) {
        suma += aint[node], suma %= mod;
    } else {
        int middle = (left + right) >> 1;
        if (leftQuery <= middle) {
            Query(aint, node << 1, left, middle, leftQuery, rightQuery);
        }
        if (middle < rightQuery) {
            Query(aint, node << 1 | 1, middle + 1, right, leftQuery, rightQuery);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n; std::cin >> n;
    std::vector<query> v(n);
    int sizeAINT = 0;
    for (int i = 0; i < n; i += 1) {
        std::cin >> v[i].tip;
        if (v[i].tip == 1 || v[i].tip == 2) {
            std::cin >> v[i].pos >> v[i].val; v[i].pos += 1;
            sizeAINT += 1;
        }
    }

    std::vector<int> aint(4 * sizeAINT + 1);
    for (int i = 1; i <= sizeAINT; i += 1) {
        update(aint, 1, 1, sizeAINT, i, 1);
    }

    for (int i = n - 1; i >= 0; i -= 1) {
        if (v[i].tip != 3) {
            v[i].pos = findKth(aint, 1, 1, sizeAINT, v[i].pos);
            update(aint, 1, 1, sizeAINT, v[i].pos, 0);
        }
    }

    int res = 0;
    std::array<int, 2> posLast;
    for (int i = 0; i < n; i += 1) {
        if (v[i].tip == 3) {
            suma = 0, Query(aint, 1, 1, sizeAINT, std::min(posLast[0], posLast[1]), std::max(posLast[0], posLast[1]));
            res += suma, res %= mod;
        } else {
            update(aint, 1, 1, sizeAINT, v[i].pos, v[i].val);
            posLast[v[i].tip - 1] = v[i].pos;
        }
    }

    std::cout << res;
    return 0;
}