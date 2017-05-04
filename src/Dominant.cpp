#include "Dominant.h"
#include <set>
#include <map>
#include <vector>

using namespace std;

set<int> build_minimal_dominant_set(AdjList graph)
{
    set<int> dominant_set;
    int maximum_degree;
    map< int, set<int> >::iterator it;

    while (graph.getOrder())
    {
        maximum_degree = graph.getMaximumDegree();
        for (it = graph.begin(); it != graph.end(); it++)
        {
            if (graph.getVertexDegree(it->first) == maximum_degree)
                break;
        }

        dominant_set.insert(it->first);

        for (set<int>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); it2++)
            graph.removeVertex(*it2);
        graph.removeVertex(it->first);
    }
    return dominant_set;
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
