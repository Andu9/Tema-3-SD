// https://www.infoarena.ro/job_detail/3230075?action=view-source

#include <fstream>
#include <queue>

int main() {
    std::ifstream fin("bleach.in");
    std::ofstream fout("bleach.out");

    int n, k; fin >> n >> k;
    std::priority_queue<long long, std::vector<long long>, std::greater<long long>> heap;
    for (int i = 0; i <= k; i += 1) { /// In primele k + 1 se gaseste sigur minimul
        long long x; fin >> x; heap.push(x);
    }

    long long result = 0, currentSum = 0;
    for (int i = k + 1; i < n; i += 1) {

        long long minLocal = heap.top(); heap.pop();
        if (minLocal > currentSum) {
            result += minLocal - currentSum;
            currentSum = 2 * minLocal; /// Se aduga si valorile initale si cele din vector
        } else {
            currentSum += minLocal;
        }

        long long x; fin >> x; heap.push(x);
    }

    while (!heap.empty()) {
        long long minLocal = heap.top(); heap.pop();

        if (minLocal > currentSum) {
            result += minLocal - currentSum;
            currentSum = 2 * minLocal;
        } else {
            currentSum += minLocal;
        }
    }

    fout << result;

    fin.close(), fout.close();
    return 0;
}