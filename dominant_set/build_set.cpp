#include <iostream>
#include <cstdio>
#include "AdjList.h"

using namespace std;

set<int> build_dominant_set(AdjList graph);

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

    set<int> dominant_set = build_dominant_set(graph);
    cout << "Minimal Dominant Set = {";
    for (set<int>::iterator it = dominant_set.begin(); it != dominant_set.end(); it++)
        cout << " " << *it;
    cout << " }" << endl;
    return 0;
}

set<int> build_dominant_set(AdjList graph)
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
