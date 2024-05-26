// https://www.infoarena.ro/job_detail/3230567?action=view-source

#include <iostream>
#include <fstream>
#include <climits>
#include <vector>

long long _GCD(long long a, long long b) {
    long long r;
    while (b > 0) {
        r = a % b;
        a = b, b = r;
    }
    return a;
}

int main() {
    std::ifstream fin("euclid.in");
    std::ofstream fout("euclid.out");

    int testCases; fin >> testCases;

    for (int x = 0; x < testCases; x += 1) {
        int m, n, h, w; fin >> m >> n >> h >> w;
        std::vector<std::vector<int>> mat(m, std::vector<int>(n));
        for (int i = 0; i < m; i += 1) {
            for (int j = 0; j < n; j += 1) {
                fin >> mat[i][j];
            }
        }

        long long Max = 0;
        for (int i = 0; i <= m - h; i += 1) {
            for (int j = 0; j <= n - w; j += 1) {
                long long GCD = mat[i][j];
                for (int k = i; k < i + h && GCD > Max; k += 1) {
                    for (int l = j; l < j + w && GCD > Max; l += 1) {
                        GCD = _GCD(GCD, 1LL * mat[k][l]);
                    }
                }
                Max = std::max(Max, GCD);
            }
        }

        fout << "Case #" << x + 1 << ": " << Max << '\n';
    }

    fin.close(), fout.close();
    return 0;
}