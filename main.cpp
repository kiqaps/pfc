#include <bits/stdc++.h>
#include "AdjList.h"
#include "robson.h"
#include "bruteforce.h"

using namespace std;

int main()
{
    clock_t t1, t2;

    freopen("input.txt", "r", stdin);

    int ordem, t;
    cin >> ordem;
    Mat matriz(ordem, vector<int>(ordem));

    for (int i = 0; i < ordem; i++)
        for (int j = 0; j < ordem; j++)
            cin >> matriz[i][j];

    AdjList grafo(matriz);

    cout << "\t\t\tTempo\t\tM.I.S." << endl;
    t1 = clock();
    t = (mis_bruteforce(grafo)).size();
    t2 = clock();
    cout << "BruteForce\t\t" << (double)(t2 - t1) / CLOCKS_PER_SEC << "\t\t" << t << endl;
    t1 = clock();
    t = (mis_bruteforce(grafo, (build_maximal_independent_set(grafo)).size())).size();
    t2 = clock();
    cout << "BruteForce-M\t\t" << (double)(t2 - t1) / CLOCKS_PER_SEC << "\t\t" << t << endl;
    t1 = clock();
    t = ms(grafo);
    t2 = clock();
    cout << "Robson\t\t\t" << (double)(t2 - t1) / CLOCKS_PER_SEC << "\t" << t << endl;
    return 0;
}
