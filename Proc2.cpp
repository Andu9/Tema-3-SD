// https://www.infoarena.ro/job_detail/3230082?action=view-source

#include <fstream>
#include <utility>
#include <queue>

int main() {
    std::ifstream fin("proc2.in");
    std::ofstream fout("proc2.out");

    int n, m; fin >> n >> m;

    std::priority_queue<int, std::vector<int>, std::greater<int>> freeProcessors;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> processingTasks;

    for (int i = 0; i < n; i += 1) {
        freeProcessors.push(i + 1);
    }

    for (int i = 0; i < m; i += 1) {
        int start, time; fin >> start >> time;

        while (!processingTasks.empty() && processingTasks.top().first <= start) { /// Some tasks are still being processed
            freeProcessors.push(processingTasks.top().second); /// Earliest task finished
            processingTasks.pop();
        }
        fout << freeProcessors.top() << '\n';
        processingTasks.push(std::make_pair(start + time, freeProcessors.top()));
        freeProcessors.pop();
    }

    fin.close(), fout.close();
    return 0;
}