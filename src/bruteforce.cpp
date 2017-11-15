#include "bruteforce.h"

using namespace std;

bool is_dominating_set(AdjList g, vector<int> vertices)
{
    vector<bool> dominated = vector<bool>(g.ordem(), false);
    for (size_t i = 0; i < vertices.size(); i++)
    {
        vector<int> viz = g.vizinhancaFechada(vertices[i]);
        for (size_t j = 0; j < viz.size(); j++)
            dominated[viz[j]] = true;
    }

    for (int i = 0; i < g.ordem(); i++)
        if (!dominated[i])
            return false;

    return true;
}

bool is_minimal_dominating_set(AdjList g, vector<int> vertices)
{
    if (!is_dominating_set(g, vertices))
        return false;

    for (size_t i = 0; i < vertices.size(); i++)
    {
        vector<int> vv = vertices;
        auto it = next(vv.begin(), i);
        vv.erase(it);

        if (is_dominating_set(g, vv))
            return false;
    }
    return true;
}

vector<int> build_minimal_dominating_set(AdjList graph)
{
    vector<int> dominant_set;
    int maximum_degree;
    auto it = graph.begin();

    while (graph.ordem())
    {
        maximum_degree = graph.grauMaximo();
        for (it = graph.begin(); it != graph.end(); it++)
            if (graph.grau(it->first) == maximum_degree)
                break;

        dominant_set.push_back(it->first);
        graph = graph - graph.vizinhancaFechada(it->first);
    }
    return dominant_set;
}

int mds_bruteforce(AdjList g)
{
    int ret = g.ordem();
    vector<int> combination;
    for (int i = g.ordem() - 1; i >= 1; i--)
    {
        bool found_set = false;
        string bitmask = create_bitmask(g.ordem(), i);
        while (1)
        {
            bool flag = next_combination(g.ordem(), bitmask, combination);

            if (is_dominating_set(g, combination))
            {
                found_set = true;
                ret = i;
                break;
            }

            if (!flag)
                break;
        }

        if (!found_set)
            break;
    }
    return ret;
}

int mds_bruteforce_improved(AdjList g)
{
    int ret = g.ordem();
    vector<int> combination;
    for (int i = 1; i < g.ordem(); i++)
    {
        string bitmask = create_bitmask(g.ordem(), i);
        while (1)
        {
            bool flag = next_combination(g.ordem(), bitmask, combination);
            if (is_dominating_set(g, combination))
                return combination.size();

            if (!flag)
                break;
        }
    }
    return ret;
}

string create_bitmask(int N, int K)
{
    string bitmask(K, 1);
    bitmask.resize(N, 0);
    return bitmask;
}

bool next_combination(int N, string & bitmask, vector<int> & combination)
{
    combination.clear();
    for (int i = 0; i < N; ++i)
        if (bitmask[i]) combination.push_back(i);
    return prev_permutation(bitmask.begin(), bitmask.end());
}
