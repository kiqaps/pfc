#include <bits/stdc++.h>
#include "AdjList.h"
#include "robson.h"
#include "bruteforce.h"

using namespace std;

double escala (int ordem);

int main(int argc, char** argv)
{
    clock_t t1, t2;
    int ordem, r[3];
    while (cin >> ordem)
    {

        Mat matriz(ordem, vector<int>(ordem));

        for (int i = 0; i < ordem; i++)
            for (int j = 0; j < ordem; j++)
                cin >> matriz[i][j];

        AdjList grafo(matriz);

        t1 = clock();
        r[0] = mis_bruteforce(grafo);
        t2 = clock();
        cout << (double)(t2 - t1) / (CLOCKS_PER_SEC/escala(ordem));

        t1 = clock();
        vector<int> maximal = build_maximal_independent_set(grafo);
        r[1] = mis_bruteforce(grafo, maximal.size());
        t2 = clock();
        cout << "\t" << (double)(t2 - t1) / (CLOCKS_PER_SEC/escala(ordem));
        t1 = clock();
        r[2] = ms(grafo);
        t2 = clock();
        cout << "\t" << (double)(t2 - t1) / (CLOCKS_PER_SEC/escala(ordem)) << endl;

        if (r[0] != r[1] || r[1] != r[2])
        {
            cerr << ordem << endl;
            for (int i = 0; i < ordem; i++)
            {
                for (int j = 0; j < ordem; j++)
                {
                    cerr << matriz[i][j] << " ";
                }
                cerr << endl;
            }
        }
    }
    return 0;
}

double escala (int ordem)
{
    if (ordem <= 10)
        return 1000000;
    else if (ordem < 15)
        return 1000;
    else if (ordem < 25)
        return 1;
    else
        return 1./60.;
}
