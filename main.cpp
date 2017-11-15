#include <bits/stdc++.h>
#include "AdjList.h"
#include "bruteforce.h"
#include "mds.h"

using namespace std;

/*

10
0 0 0 0 0 0 1 1 1 1
0 0 0 0 0 0 1 1 1 1
0 0 0 0 0 0 1 1 1 1
0 0 0 0 0 0 1 1 1 1
0 0 0 0 0 0 1 1 1 1
0 0 0 0 0 0 1 1 1 1
1 1 1 1 1 1 0 1 1 1
1 1 1 1 1 1 1 0 1 1
1 1 1 1 1 1 1 1 0 1
1 1 1 1 1 1 1 1 1 0


*/

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
        cout << "Test: "<< (c++) << ", MinimalSize: " << minimal.size() << ", IsMinimalMinimal: " << is_minimal_dominating_set(g, minimal);
        int ret, iret, lret;
        clock_t t1, t2;
        double diff_bf, diff_ibf, diff_linear;
        t1 = clock();
        ret = mds_bruteforce(g);
        t2 = clock();

        diff_bf = (double) (t2 - t1) / CLOCKS_PER_SEC;



        t1 = clock();
        iret = mds_bruteforce_improved(g);
        t2 = clock();

        diff_ibf = (double) (t2 - t1) / CLOCKS_PER_SEC;

        t1 = clock();
        lret = mds(g);
        t2 = clock();

        diff_linear = (double) (t2 - t1) / CLOCKS_PER_SEC;

        cout << ", BF: " << ret << ", I-BF: " << iret << ", Linear: " << lret << ", T BF: " << diff_bf << ", T I-BF: " << diff_ibf << ", T Linear: " << diff_linear;

        if (ret != iret)
            cout << " *********************";
        else if (ret != lret)
            cout << " !!!!!!!!!!!!!!!!!!!!!";
        cout <<endl;
    }
    return 0;
}
