#include <bits/stdc++.h>
#include "AdjList.h"
#include "bruteforce.h"
#include "mds.h"

using namespace std;

int main(int argc, char** argv)
{
    int c = 1;
    int ordem;
    while (cin >> ordem)
    {
        Mat adjMat = Mat(ordem, vector<int>(ordem, 0));

        for (int i = 0; i < ordem; i++)
            for (int j = 0; j < ordem; j++)
                cin >> adjMat[i][j];

        AdjList g(adjMat);
        vector<int> minimal = build_minimal_dominating_set(g);

        bool is = is_minimal_dominating_set(g, minimal);

        printf("Test: %d\tMinimalSize: %d\tIsMinimalMinimal: %d", c++, minimal.size(), is);
        fflush(stdin);

        int ret, iret, lret;
        clock_t t1, t2;
        double diff_bf, diff_ibf, diff_linear;
        t1 = clock();
        ret = mds_bruteforce(g);
        t2 = clock();
        diff_bf = (double) (t2 - t1) / CLOCKS_PER_SEC;

        printf("\tBF: %d\tT BF: %f", ret, diff_bf);
        fflush(stdin);

        t1 = clock();
        iret = mds_bruteforce_improved(g);
        t2 = clock();
        diff_ibf = (double) (t2 - t1) / CLOCKS_PER_SEC;

        printf("\tI-BF: %d\tT I-BF: %f", iret, diff_ibf);
        fflush(stdin);

        t1 = clock();
        lret = mds(g);
        t2 = clock();
        diff_linear = (double) (t2 - t1) / CLOCKS_PER_SEC;

        printf("\tLinear: %d\tT Linear: %f\n", lret, diff_linear);
        fflush(stdin);

        if (!is)
            fprintf(stderr, "%d: IS MINIMAL PROBLEM\n", c-1);

        if (lret != ret || ret != iret)
            fprintf(stderr, "%d: PROBLEMA DE RESPOSTA\n", c-1);
    }
    return 0;
}
