// https://kilonova.ro/submissions/382210

#include <fstream>
#include <vector>

void update(std::vector<int>& aint,
            std::vector<int>& lazy,
            int node, int left, int right,
            int leftUpdate, int rightUpdate, int val) {
    if (lazy[node] && left != right) {
        lazy[node << 1] += lazy[node];
        lazy[node << 1 | 1] += lazy[node];
        aint[node << 1] += lazy[node];
        aint[node << 1 | 1] += lazy[node];
        lazy[node] = 0;
    }

    if (leftUpdate <= left && right <= rightUpdate) {
        aint[node] += val;
        lazy[node] += val;
    } else {
        int middle = (left + right) >> 1;
        if (leftUpdate <= middle) {
            update(aint, lazy, node << 1, left, middle, leftUpdate, rightUpdate, val);
        }
        if (middle < rightUpdate) {
            update(aint, lazy, node << 1 | 1, middle + 1, right, leftUpdate, rightUpdate, val);
        }
        aint[node] = std::min(aint[node << 1], aint[node << 1 | 1]);
    }
}

int main() {
    std::ifstream fin("sirbun.in");
    std::ofstream fout("sirbun.out");

    int n; fin >> n;
    std::vector<int> v(n + 1);
    std::vector<int> aint(4 * n + 1);
    std::vector<int> lazy(4 * n + 1);
    for (int i = 1; i <= n; i += 1) {
        fin >> v[i];
        update(aint, lazy, 1, 1, n, i, i, i);
    }

    int i = 1;
    long long res = 0;
    for (int j = 1; j <= n; j += 1) {
        update(aint, lazy, 1, 1, n, v[j], n, -1);

        while (i <= j && aint[1] < 0) {
            update(aint, lazy, 1, 1, n, v[i], n, 1), i += 1;
        }

        res += j - i + 1;
    }

    fout << res;

    fin.close(), fout.close();
    return 0;
}