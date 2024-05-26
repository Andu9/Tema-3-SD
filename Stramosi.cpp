// https://www.infoarena.ro/job_detail/3230408?action=view-source

#include <fstream>
#include <vector>
#include <iostream>

int main() {
    std::ifstream fin("stramosi.in");
    std::ofstream fout("stramosi.out");

    int n, m; fin >> n >> m;
    std::vector<std::vector<int>> dp(20, std::vector<int>(n + 1));

    for (int i = 1; i <= n; i += 1) {
        fin >> dp[0][i];
    }

    for (int i = 1; i < 20; i += 1) {
        std::cout << i << ' ';
        for (int j = 1; j <= n; j += 1) {
            dp[i][j] = dp[i - 1][dp[i - 1][j]];
        }
    }

    for (int i = 0; i < m; i += 1) {
        int x, y; fin >> x >> y;

        int exp = 0;

        while (y) {
            if (y % 2 == 1) {
                x = dp[exp][x];
            }

            exp += 1;
            y >>= 1;
        }

        fout << x << '\n';
    }

    fin.close(), fout.close();
    return 0;
}