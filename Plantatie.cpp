// https://infoarena.ro/job_detail/2881271?action=view-source

#include <fstream>
#include <vector>

using namespace std;

ifstream f("plantatie.in");
ofstream g("plantatie.out");

vector <int> pow2;
vector <vector <vector <int>>> rmq;

int main ()
{
    int n, m, i, j, k, sz, newi, newj, x, y, length, power2, index;
    f >> n >> m;


    pow2.resize (n + 1), pow2[1] = 0;
    for (i = 2; i <= n; i += 1)
        pow2[i] = 1 + pow2[i / 2];
    sz = pow2[n];


    rmq.assign (sz + 1, vector <vector <int>> (n + 1, vector <int> (n + 1)));
    for (i = 1; i <= n; i += 1)
    {
        for (j = 1; j <= n; j += 1)
            f >> rmq[0][i][j];
    }


    for (k = 1; k <= sz; k += 1)
    {
        for (i = 1; i <= n - (1 << k) + 1; i += 1)
        {
            for (j = 1; j <= n - (1 << k) + 1; j += 1)
            {
                newi = i + (1 << (k - 1));
                newj = j + (1 << (k - 1));
                rmq[k][i][j] = max (
                                     max (rmq[k - 1][i][j], rmq[k - 1][i][newj]) ,
                                     max (rmq[k - 1][newi][j], rmq[k - 1][newi][newj])
                                    );
            }
        }
    }


    for (i = 1; i <= m; i += 1)
    {
        f >> x >> y >> length;
        index = pow2[length], power2 = (1 << index);
        newi = x + length - power2, newj = y + length - power2;
        g << max (
                   max (rmq[index][x][y], rmq[index][x][newj]),
                   max (rmq[index][newi][y], rmq[index][newi][newj])
                  ) << '\n';
    }
    return 0;
}