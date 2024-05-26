// https://www.pbinfo.ro/detalii-evaluare/35954095

#include <iostream>
#include <vector>

using namespace std;

vector <int> power2, position, freq;
vector <vector <int>> minim, maxim;

int main ()
{
    ios_base::sync_with_stdio (false);
    cin.tie (NULL), cout.tie (NULL);

    
    int n, i, j, m, x, y, sz, dist, index, pow2, minn, maxx;
    cin >> n;


    power2.resize (n + 1), power2[1] = 0;
    for (i = 2; i <= n; i += 1)
        power2[i] = 1 + power2[i / 2];
    sz = power2[n];


    minim.assign (sz + 1, vector <int> (n + 1));
    maxim.assign (sz + 1, vector <int> (n + 1));
    for (i = 1; i <= n; i += 1)
        cin >> minim[0][i], maxim[0][i] = minim[0][i];

    
    freq.resize (n + 1, 0);
    position.resize (n + 1), j = 1;
    for (i = 1; i <= n; i += 1)
    {
        while (freq[minim[0][i]] > 0)
            freq[minim[0][j]] -= 1, j += 1;
        freq[minim[0][i]] += 1, position[i] = j;
    }


    for (i = 1; i <= sz; i += 1)
    {
        for (j = 1; j <= n; j += 1)
        {
            minim[i][j] = minim[i - 1][j];
            maxim[i][j] = maxim[i - 1][j];
            if (j + (1 << (i - 1)) <= n)
            {
                if (minim[i - 1][j + (1 << (i - 1))] < minim[i][j])
                    minim[i][j] = minim[i - 1][j + (1 << (i - 1))];
                if (maxim[i - 1][j + (1 << (i - 1))] > maxim[i][j])
                    maxim[i][j] = maxim[i - 1][j + (1 << (i - 1))];
            }
        }
    }


    cin >> m;
    for (i = 1; i <= m; i += 1)
    {
        cin >> x >> y, dist = y - x + 1;
        index = power2[dist], pow2 = (1 << index);
        
        
        minn = min (minim[index][x], minim[index][y - pow2 + 1]);
        maxx = max (maxim[index][x], maxim[index][y - pow2 + 1]);
        
        
        if (position[y] <= x and dist == maxx - minn + 1)
            cout << 1;
        else
            cout << 0;
    }
    return 0;
}

