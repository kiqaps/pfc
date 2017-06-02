#include <bits/stdc++.h>
#include "AdjList.h"
#include "AdjMatrix.h"
#include "Independent.h"

using namespace std;

int ms (AdjList graph);
int ms2 (AdjList graph, set<int> vertexes);

set<int> getSmallestComponent (AdjList graph);
void chooseAB(AdjList graph, int& a, int& b);
bool dominates (AdjList graph, set<int> vFA, set<int> vFB);

void p (AdjList g) { cout << "G\n" << g << endl << endl; }

int main()
{
    freopen("input.txt", "r", stdin);
    int order;
    cin >> order;
    AdjMatrix matrix(order);

    for (int i = 0; i < order; i++)
        for (int j = 0; j < order; j++)
            cin >> matrix[i][j];

    AdjList graph(matrix);
    p(graph);
    int a,b;
    chooseAB(graph, a, b);
    set<int> v;
    graph.getVertexNeighborhood(a, v);
    v.insert(a);
    p(graph - graph.getSubgraph(v));
    return 0;
}

int ms (AdjList graph)
{
    if (!is_connected(graph))
    {
        AdjList C = graph.getSubgraph(getSmallestComponent(graph));
        return ms (graph - C) + (C.getOrder() <= 2 ? 1 : ms(C));
    }

    if (graph.getOrder() <= 1)
        return graph.getOrder();

    int A = -1, B = -1;
    chooseAB(graph, A, B);

    set<int> vA, vFA, vB, vFB;
    graph.getVertexNeighborhood(A, vA);
    graph.getVertexNeighborhood(B, vB);
    vFA = vA;
    vFB = vB;
    vFA.insert(A);
    vFB.insert(B);

    if (vA.size() == 1)
        return 1 + ms (graph - graph.getSubgraph(vFA));

    if (vA.size() == 2)
    {
        set<int>::iterator it = vA.begin();
        if (*it == B) it++;
        int BB = *it;

        if (vB.find(BB) != vB.end())
            return 1 + ms (graph - graph.getSubgraph(vFA));

        set<int> vFBB;
        graph.getVertexNeighborhood(BB, vFBB);
        vFBB.insert(BB);

        set<int> v2A;
        for (set<int>::iterator it2 = vA.begin(); it2 != vA.end(); it2++)
        {
            set<int> v;
            graph.getVertexNeighborhood(*it2, v);
            v2A.insert(v.begin(), v.end());
        }

        return max(2 + ms (graph - graph.getSubgraph(vFB) - graph.getSubgraph(vFBB)), ms2 (graph - graph.getSubgraph(vFA), v2A));
    }

    if (vA.size() == 3)
        return max(ms2 (graph - A, vA), 1 + ms (graph - graph.getSubgraph(vFA)));

    if (dominates(graph, vFA, vFB))
        return ms (graph - B);

    return max(ms (graph - B), 1 + ms (graph - graph.getSubgraph(vFB)));
}

int ms2 (AdjList graph, set<int> vertexes)
{
    return 0;
}

bool dominates (AdjList graph, set<int> vFA, set<int> vFB)
{
    for (set<int>::iterator it = vFA.begin(); it != vFA.end(); it++)
        if (vFB.find(*it) == vFB.end())
            return false;
    return true;
}

void chooseAB(AdjList graph, int& a, int& b)
{
    unsigned int dd, d = graph.getOrder();
    for (map< int, set<int> >::iterator it = graph.begin(); it != graph.end(); it++)
    {
        if (d > (it->second).size())
        {
            dd = 0;
            d = (it->second).size();
            a = it->first;
            for (set<int>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); it2++)
            {
                unsigned int degree = graph.getVertexDegree(*it2);
                if (dd < degree)
                {
                    dd = degree;
                    b = *it2;
                }
            }
        }
        else if (d == (it->second).size())
        {
            for (set<int>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); it2++)
            {
                unsigned int degree = graph.getVertexDegree(*it2);
                if (dd < degree)
                {
                    dd = degree;
                    b = *it2;
                    a = it->first;
                }
            }
        }
    }
}

set<int> getSmallestComponent (AdjList graph)
{
    unsigned int t = graph.getOrder();
    set<int> c, smallest;
    vector<bool> visited(graph.getOrder(), false);

    while (get_next_connected_component(visited, graph, c))
    {
        if (c.size() <= t) {
            t = c.size();
            smallest = set<int>(c);
        }
    }
    return smallest;
}
