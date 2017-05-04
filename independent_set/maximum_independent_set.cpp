#include <bits/stdc++.h>
#include "./AdjMatrix.h"
#include "Independent.h"

using namespace std;

string create_bitmask(int N, int K);
bool next_combination(int N, string & bitmask, set<int> & combination);
set<int> maximum_independet_set(AdjMatrix g);
set<int> maximum_independet_set_MELHORADO(AdjMatrix g);

int main()
{
    freopen("input.txt", "r", stdin);
    int n_vertex;

    cin >> n_vertex;

    AdjMatrix graph(n_vertex);

    for (int i = 0; i < n_vertex; i++)
        for (int j = 0; j < n_vertex; j++)
            cin >> graph[i][j];

    set<int> maxIndependentSet = maximum_independet_set(graph);

    cout << "Tamanho = " << maxIndependentSet.size() << " : {";
    for (set<int>::iterator it = maxIndependentSet.begin(); it != maxIndependentSet.end(); it++)
    {
        cout << " " << *it;
    }
    cout << " }" << endl;

    return 0;
}

set<int> maximum_independet_set(AdjMatrix g)
{
    set<int> maximum_set, combination;
    for (int i = 1; i <= g.getOrder(); i++)
    {
        string bitmask = create_bitmask(g.getOrder(), i);
        while (1)
        {
            bool flag = next_combination(g.getOrder(), bitmask, combination);

            if (is_independent_set(g, combination))
            {
                maximum_set = combination;
                break;
            }

            if (!flag)
                break;
        }
    }
    return maximum_set;
}

set<int> maximum_independet_set_MELHORADO(AdjList g)
{
    set<int> maximum_set, combination;
    for (int i = 1; i <= g.getOrder(); i++)
    {
        string bitmask = create_bitmask(g.getOrder(), i);
        while (1)
        {
            bool flag = next_combination(g.getOrder(), bitmask, combination);

            if (is_independent_set(g, combination))
            {
                maximum_set = combination;
                break;
            }

            if (!flag)
                break;
        }
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
