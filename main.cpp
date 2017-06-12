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
    gt1 = clock();
    while (cin >> ordem)
    {

        Mat matriz(ordem, vector<int>(ordem));

        for (int i = 0; i < ordem; i++)
            for (int j = 0; j < ordem; j++)
                cin >> matriz[i][j];

        AdjList grafo(matriz);
        cout << "Ordem: " << ordem << "\t\tTempo\t\tResposta" << endl;
        t1 = clock();
        vector<int> maximal = build_maximal_independent_set(grafo);
        t2 = clock();
        cout << "Maximal\t\t\t" << (double)(t2 - t1) / (CLOCKS_PER_SEC/1000) << "\t" << maximal.size() << endl;
        t1 = clock();
        t[0] = mis_bruteforce(grafo);
        t2 = clock();
        cout << "BruteForce\t\t" << (double)(t2 - t1) / (CLOCKS_PER_SEC/1000) << "\t\t" << t[0] << endl;
        t1 = clock();
        t[1] = mis_bruteforce(grafo, maximal.size());
        t2 = clock();
        cout << "BruteForce-Improved\t" << (double)(t2 - t1) / (CLOCKS_PER_SEC/1000) << "\t\t" << t[1] << endl;
        t1 = clock();
        t[2] = ms(grafo);
        t2 = clock();
        cout << "Robson\t\t\t" << (double)(t2 - t1) / (CLOCKS_PER_SEC/1000) << "\t\t" << t[2] << endl << endl;

        if (t[0] != t[1])
            cerr << "DEU RUIM" << endl;
        else if (t[1] != t[2]) {
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
    if (ordem <= 5)
        return 1000000;
    else if (ordem < 15)
        return 1000;
    else if (ordem < 25)
        return 1;
    else
        return 1/60;
}
