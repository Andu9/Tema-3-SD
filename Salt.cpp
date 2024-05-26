// https://codeforces.com/gym/103999/submission/262192525

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    const int mod = 1e9 + 7;

    int n; std::cin >> n;

    std::vector<int> power2(n + 1), powersMod(n + 1);
    power2[1] = 0, powersMod[0] = 1, powersMod[1] = 2;
    for (int i = 2; i <= n; i += 1) {
        power2[i] = 1 + power2[i >> 1];
        powersMod[i] = (powersMod[i - 1] << 1) % mod;
    }
    int Size = power2[n] + 1;

    std::vector<std::vector<int>> rmq(Size + 2, std::vector<int>(n + 1));
    for (int i = 1; i <= n; i += 1) {
        std::cin >> rmq[0][i];
    }

    for (int i = 1; i <= Size; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            rmq[i][j] = rmq[i - 1][j];
            if (j + (1 << (i - 1)) <= n && rmq[i - 1][j + (1 << (i - 1))] > rmq[i][j]) {
                rmq[i][j] = rmq[i - 1][j + (1 << (i - 1))];
            }
        }
    }

    int q; std::cin >> q;
    for (int j = 1; j <= q; j += 1) {
        int left, right; std::cin >> left >> right;

        int distance = right - left + 1;
        int index = power2[distance];
        int power = (1 << index);

        int Max = std::max(rmq[index][left], rmq[index][right - power + 1]);

        std::cout << 1LL * Max * powersMod[distance - 1] % mod << '\n';
    }
    return 0;
}