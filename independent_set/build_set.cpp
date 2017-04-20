#include <iostream>
#include <cstdio>
#include "AdjList.h"

using namespace std;

set<int> build_independent_set(AdjList graph);

int main()
{
    int order, input;

    cin >> order;
    AdjList graph(order);

    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            cin >> input;
            if (input)
                graph[i].insert(j);
        }
    }

    set<int> independent_set = build_independent_set(graph);
    cout << "Independent_Set = {";
    for (set<int>::iterator it = independent_set.begin(); it != independent_set.end(); it++)
        cout << " " << *it;
    cout << " }" << endl;
    return 0;
}

set<int> build_independent_set(AdjList graph)
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
