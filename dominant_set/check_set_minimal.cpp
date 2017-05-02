#include <bits/stdc++.h>
#include "./AdjMatrix.h"

using namespace std;

bool is_dominant_set(AdjMatrix g, set<int> the_set);
bool is_minimal_dominant_set(AdjMatrix g, set<int> the_set);

int main()
{
    int new_set_member, n_vertex;
    set<int> dominant_set;

    cin >> n_vertex;

    AdjMatrix graph(n_vertex);

    for (int i = 0; i < n_vertex; i++)
        for (int j = 0; j < n_vertex; j++)
            cin >> graph[i][j];

    cin >> new_set_member;
    while (new_set_member >= 0 && new_set_member < n_vertex)
    {
        dominant_set.insert(new_set_member);
        cin >> new_set_member;
    }

    cout << is_minimal_dominant_set(graph, dominant_set) << endl;
    return 0;
}

bool is_minimal_dominant_set(AdjMatrix g, set<int> the_set)
{
    if (!is_dominant_set(g, the_set))
        return false;

    for (set<int>::iterator it = the_set.begin(); it != the_set.end(); it++)
    {
        set<int> new_set;
        for (set<int>::iterator it2 = the_set.begin(); it2 != the_set.end(); it2++)
            if (it2 != it)
                new_set.insert(*it2);
        if (is_dominant_set(g, new_set))
            return false;
    }

    return true;
}

bool is_dominant_set(AdjMatrix g, set<int> the_set)
{
    vector<bool> vertexes = vector<bool>(g.getOrder(), false);

    for (set<int>::iterator it = the_set.begin(); it != the_set.end(); ++it)
    {
        vertexes[*it] = true;
        for (int i = 0; i < g.getOrder(); i++)
            if (g[*it][i] == 1)
                vertexes[i] = true;
    }

    for (int i = 0; i < g.getOrder(); i++)
    {
        if (!vertexes[i])
            return false;
    }
    return true;
}
