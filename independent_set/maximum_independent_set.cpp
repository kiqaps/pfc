#include <bits/stdc++.h>
#include "./AdjMatrix.h"
#include "Independent.h"
#include <ctime>

using namespace std;

string create_bitmask(int N, int K);
bool next_combination(int N, string & bitmask, set<int> & combination);
set<int> maximum_independet_set(AdjMatrix g, int fromWhere = 1);

int main()
{
    freopen("input.txt", "r", stdin);
    clock_t tbegin, tend;
    int n_vertex;

    cin >> n_vertex;

    AdjMatrix graph(n_vertex);

    for (int i = 0; i < n_vertex; i++)
        for (int j = 0; j < n_vertex; j++)
            cin >> graph[i][j];

    set<int> maxIndependentSet = build_maximal_independent_set(AdjList(graph));

    cout << "Maximal:" << endl;
    cout << "Tamanho = " << maxIndependentSet.size() << " : {";
    int fromWhere = maxIndependentSet.size();
    for (set<int>::iterator it = maxIndependentSet.begin(); it != maxIndependentSet.end(); it++)
    {
        cout << " " << *it;
    }
    cout << " }" << endl;

    maxIndependentSet.clear();
    cout << "Normal:" << endl;
    tbegin = clock();
    maxIndependentSet = maximum_independet_set(graph);
    tend = clock();

    cout << "Tempo: " << (double)(tend - tbegin)/CLOCKS_PER_SEC << endl;

    cout << "Tamanho = " << maxIndependentSet.size() << " : {";
    for (set<int>::iterator it = maxIndependentSet.begin(); it != maxIndependentSet.end(); it++)
    {
        cout << " " << *it;
    }
    cout << " }" << endl;

    maxIndependentSet.clear();
    cout << endl << "Melhorado:" << endl;
    tbegin = clock();
    maxIndependentSet = maximum_independet_set(graph, fromWhere);
    tend = clock();

    cout << "Tempo: " << (double)(tend - tbegin)/CLOCKS_PER_SEC << endl;

    cout << "Tamanho = " << maxIndependentSet.size() << " : {";
    for (set<int>::iterator it = maxIndependentSet.begin(); it != maxIndependentSet.end(); it++)
    {
        cout << " " << *it;
    }
    cout << " }" << endl;

    return 0;
}

set<int> maximum_independet_set(AdjMatrix g, int fromWhere)
{
    set<int> maximum_set, combination;
    for (int i = fromWhere; i <= g.getOrder(); i++)
    {
        bool found_set = false;
        string bitmask = create_bitmask(g.getOrder(), i);
        while (1)
        {
            bool flag = next_combination(g.getOrder(), bitmask, combination);

            if (is_independent_set(g, combination))
            {
                found_set = true;
                maximum_set = combination;
                break;
            }

            if (!flag)
                break;
        }

        if (!found_set)
            break;
    }
    return maximum_set;
}

string create_bitmask(int N, int K)
{
    string bitmask(K, 1);
    bitmask.resize(N, 0);
    return bitmask;
}

bool next_combination(int N, string & bitmask, set<int> & combination)
{
    combination.clear();
    for (int i = 0; i < N; ++i)
        if (bitmask[i]) combination.insert(i);
    return prev_permutation(bitmask.begin(), bitmask.end());
}
