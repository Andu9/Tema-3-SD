// https://codeforces.com/gym/103999/submission/261939475

#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>
#include <deque>

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n; std::cin >> n;
    std::vector<int> freq(n, 0);
    std::vector<std::pair<int, int>> nums;
    for (int i = 0; i < n; i += 1) {
        int x, y; std::cin >> x >> y;
        nums.emplace_back(std::make_pair(x, i));
        nums.emplace_back(std::make_pair(y, i));
    }
    std::sort(nums.begin(), nums.end());

    int noInDeque = 0, sol = INT_MAX;
    std::deque<std::pair<int, int>> nElems;
    for (int i = 0; i < (int) nums.size(); i += 1) {

        freq[nums[i].second] += 1;
        nElems.push_back(nums[i]);
        noInDeque += freq[nums[i].second] == 1;

        while (!nElems.empty() && noInDeque == n) {
            sol = std::min(sol, nElems.back().first - nElems.front().first);
            freq[nElems.front().second] -= 1;
            noInDeque -= freq[nElems.front().second] == 0;
            nElems.pop_front();
        }
    }
    std::cout << sol;
    return 0;
}