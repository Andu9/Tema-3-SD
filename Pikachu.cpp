// https://infoarena.ro/job_detail/3231369?action=view-source

#include <fstream>
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

/// Compute the time required if I choose x to be median

long long Try(long long x, int k, const std::vector<long long> v) {
    long long value = 0, Min = LLONG_MAX;
    for (int i = 0; i < k; i += 1) {
        value += std::abs(v[i] - x);
    }
    for (int i = k; i < (int) v.size(); i += 1) {
        value += std::abs(v[i] - x);
        value -= std::abs(v[i - k] - x);

        Min = std::min(Min, value);
    }
    return Min;
}

int main() {
    std::ifstream fin("pikachu.in");
    std::ofstream fout("pikachu.out");

    int n, k; fin >> n >> k;
    std::vector<long long> v(n);
    long long Max = INT_MIN, Min = 0;
    for (int i = 0; i < n; i += 1) {
        fin >> v[i]; Max = std::max(Max, v[i] + 1);
    }

    /// Try to minimize the value by binary search

    while (Min < Max) {
        long long middle = Min + (Max - Min) / 2;
        long long val1 = Try(middle, k, v);
        long long val2 = Try(middle + 1, k, v);


        std::cout << middle << '\n';

        if (val1 > val2) Min = middle + 1;
        else Max = middle;
    }

    fout << Try(Min, k, v);
    return 0;
}