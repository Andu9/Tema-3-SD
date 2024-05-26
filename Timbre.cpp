// https://www.infoarena.ro/job_detail/3230594?action=view-source

#include <fstream>
#include <queue>
#include <utility>
#include <iostream>

int main() {
    std::ifstream fin("timbre.in");
    std::ofstream fout("timbre.out");

    int n, m, k; fin >> n >> m >> k;
    std::priority_queue<std::pair<int, int>> interval;
    std::priority_queue<int, std::vector<int>, std::greater<int>> costuri;

    for (int i = 0; i < m; i += 1) {
        int right, cost; fin >> right >> cost;
        interval.push(std::make_pair(right, cost));
    }


    int totalCost = 0;
    while (n > 0) {
        while (!interval.empty() && interval.top().first >= std::max(n, k)) {
            costuri.push(interval.top().second);
            interval.pop();
        }

        n -= k, totalCost += costuri.top(), costuri.pop();
    }

    fout << totalCost;

    fin.close(), fout.close();
    return 0;
}