#include "bruteforce.h"

using namespace std;

bool is_independent_set(AdjList g, vector<int> vertices)
{
    bool is_independent_set = true;
    for (size_t i = 0; i < vertices.size(); i++)
        for (size_t j = 0; j < vertices.size(); j++)
            if (g.aresta(vertices[i], vertices[j]))
                return false;
    return is_independent_set;
}

bool is_maximal_independent_set(AdjList g, vector<int> vertices)
{
    if (!is_independent_set(g, vertices))
        return false;

    for (auto it = g.begin(); it != g.end(); it++)
    {
        if (find(vertices.begin(), vertices.end(), it->first) == vertices.end())
        {
            vertices.push_back(it->first);
            if (is_independent_set(g, vertices))
                return false;
            vertices.erase(prev(vertices.end()));
        }
    }
    return true;
}

vector<int> build_maximal_independent_set(AdjList graph)
{
    vector<int> independent_set;
    int minimum_degree;
    auto it = graph.begin();

    while (graph.ordem())
    {
        minimum_degree = graph.grauMinimo();
        for (it = graph.begin(); it != graph.end(); it++)
            if (graph.grau(it->first) == minimum_degree)
                break;

        independent_set.push_back(it->first);
        graph = graph - graph.vizinhancaFechada(it->first);
    }
    return independent_set;
}

int mis_bruteforce(AdjList g, int fromWhere)
{
    int ret = fromWhere;
    vector<int> combination;
    for (int i = fromWhere + 1; i <= g.ordem(); i++)
    {
        bool found_set = false;
        string bitmask = create_bitmask(g.ordem(), i);
        while (1)
        {
            bool flag = next_combination(g.ordem(), bitmask, combination);

            if (is_independent_set(g, combination))
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
