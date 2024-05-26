// https://www.infoarena.ro/job_detail/3230053?action=view-source

#include <fstream>
#include <vector>
#include <climits>

int main() {
    std::ifstream fin("kami.in");
    std::ofstream fout("kami.out");

    int n; fin >> n;
    std::vector<int> v(n);
    for (int i = 1; i <= n; i += 1) {
        fin >> v[i];
    }
    v[0] = INT_MAX;

    int m; fin >> m;
    for (int i = 0; i < m; i += 1) {
        int op; fin >> op;
        if (op == 0) {
            int pos, val; fin >> pos >> val;
            v[pos] = val;
        } else {
            int pos; fin >> pos;

            long long snow = v[pos]; pos -= 1;
            while (pos > 0 && snow > v[pos]) {
                snow += v[pos];
                pos -= 1;

                if (snow > (int) 1e9) {
                    pos = 0;
                    break;
                }
            }

            fout << pos << '\n';
        }
    }

    v.clear(), fin.close(), fout.close();
    return 0;
}