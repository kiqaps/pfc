#include "Independent.h"
#include <set>
#include <map>
#include <queue>

using namespace std;

set<int> build_maximal_independent_set(AdjList graph)
{
    set<int> independent_set;
    int minimum_degree;
    map< int, set<int> >::iterator it;

    while (graph.getOrder())
    {
        minimum_degree = graph.getMinimumDegree();
        for (it = graph.begin(); it != graph.end(); it++)
        {
            if (graph.getVertexDegree(it->first) == minimum_degree)
                break;
        }

        independent_set.insert(it->first);

        for (set<int>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); it2++)
            graph.removeVertex(*it2);
        graph.removeVertex(it->first);
    }
    return independent_set;
}

bool is_independent_set(AdjMatrix g, set<int> the_set)
{
    set<int>::iterator prev = the_set.end(); prev--;
    bool is_independent_set = true;
    for (set<int>::iterator it = the_set.begin(); it != prev && is_independent_set; it++)
    {
        set<int>::iterator it2 = it;
        for (it2++; it2 != the_set.end(); it2++)
        {
            if (g[*it][*it2] == 1)
            {
                is_independent_set = false;
                break;
            }
        }
    }
    return is_independent_set;
}

bool is_maximal_independent_set(AdjMatrix graph, set<int> the_set)
{
    if (!is_independent_set(graph, the_set))
        return false;

    for (int i = 0; i < graph.getOrder(); i++)
    {
        if (the_set.find(i) == the_set.end())
        {
            the_set.insert(i);
            if (is_independent_set(graph, the_set))
                return false;
            the_set.erase(i);
        }
    }
    return true;
}

void bfs(vector<bool> & visited, AdjList graph);
void bfs(vector<bool> & visited, AdjList graph, int vertex, set<int>* c)
{
    set<int> enqueued;
    queue<int> vertexes;
    vertexes.push(vertex);
    enqueued.insert(vertex);

    while (!vertexes.empty())
    {
        int v = vertexes.front();
        vertexes.pop();

        visited[v] = true;

        if (c != NULL)
            c->insert(v);

        set<int> neighborhood = graph[v];
        for (set<int>::iterator it = neighborhood.begin(); it != neighborhood.end(); it++)
        {
            if (enqueued.find(*it) == enqueued.end())
            {
                vertexes.push(*it);
                enqueued.insert(*it);
            }
        }
    }
}

bool get_next_connected_component(vector<bool> & visited, AdjList graph, set<int> & component)
{
    int i;
    for (i = 0; i < graph.getOrder(); i++)
        if (!visited[i])
            break;

    if (i == graph.getOrder())
        return false;

    component.clear();
    bfs(visited, graph, i,  &component);
    return true;
}

bool is_connected (AdjList graph)
{
    vector<bool> visited(graph.getOrder(), false);
    bfs(visited, graph, 0);
    for (int i = 0; i < graph.getOrder(); i++)
        if (!visited[i])
            return false;
    return true;
}
