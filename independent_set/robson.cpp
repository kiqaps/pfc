#include <bits/stdc++.h>
#include "AdjList.h"
#include "AdjMatrix.h"
#include "Independent.h"

using namespace std;

int ms (AdjList graph);
int ms2 (AdjList graph, set<int> vertexes);

set<int> getSmallestComponent (AdjList graph);
void chooseAB(AdjList graph, int& a, int& b);
bool is_contained (AdjList graph, set<int> A, set<int> B);
bool edge (AdjList graph, int a, int b);

void p (AdjList g) { cout << "G\n" << g << endl << endl; }

operator[]

int main()
{
    int t[] = {1,2,3,4,5};
    set<int> s(t, t+5);
//    freopen("input.txt", "r", stdin);
//    int order;
//    cin >> order;
//    AdjMatrix matrix(order);
//
//    for (int i = 0; i < order; i++)
//        for (int j = 0; j < order; j++)
//            cin >> matrix[i][j];
//
//    AdjList graph(matrix);
//    cout << ms (graph) << endl;
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

    if (is_contained(graph, vFA, vFB))
        return ms (graph - B);

    return max(ms (graph - B), 1 + ms (graph - graph.getSubgraph(vFB)));
}

int ms2 (AdjList graph, set<int> S)
{
    if (S.size() <= 1)
        return 0;

    if (S.size() == 2)
    {
        int s1 = *(S.begin());
        int s2 = *(next(S.begin()));

        if (edge(graph, s1, s2))
            return 0;
        else
            return 2 + ms (graph /* - vFS1 - vFS2*/);
    }

//    if (S.size() == 3)
    return 0;
}

int ms1 (AdjList graph, int s1, int s2)
{
    set<int> vS1, vFS1, vS2, vFS2;
    graph.getVertexNeighborhood(s1, vS1);
    graph.getVertexNeighborhood(s2, vS2);
    vFS1 = vS1;
    vFS2 = vS2;
    vFS1.insert(s1);
    vFS2.insert(s2);

    if (vS1.size() <= 1)
        return ms (graph);

    if (edge(graph, s1, s2))
    {
        if (vS1.size() <= 3)
            return ms (graph);
        else
            return 1 + max (ms(graph - graph.getSubgraph(vFS1)), ms(graph - graph.getSubgraph(vFS2)));
    }

    vector<int> intersecao (vS1.size() + vS2.size());
    vector<int>::iterator it = set_intersection(vS1.begin(), vS1.end(), vS2.begin(), vS2.end(), intersecao.begin());
    intersecao.resize(it - intersecao.begin());

    if (intersecao.size() != 0)
        return ms1(graph - graph.getSubgraph(set<int>(intersecao.begin(), intersecao.end())), s1, s2);

    if (vS2.size() == 2)
    {
        set<int>::iterator it = vS1.begin();
        int E = *it, F = *(++it);

        if (edge(graph, E, F))
            return  1 + ms (graph - graph.getSubgraph(vFS1));

        set<int> vE, vF, vFE, vFF;
        graph.getVertexNeighborhood(E, vE);
        graph.getVertexNeighborhood(F, vF);
        vFE = vE;
        vFF = vF;
        vFE.insert(E);
        vFF.insert(F);

        vector<int> vuniao (vE.size() + vF.size());
        vector<int>::iterator it2 = set_union(vE.begin(), vE.end(), vF.begin(), vF.end(), vuniao.begin());
        vuniao.resize(it2 - vuniao.begin());
        set<int> uniao (vuniao.begin(), vuniao.end());
        uniao.erase(s1);

        if (is_contained(graph, uniao, vS2))
            return 3 + ms (graph - graph.getSubgraph(vFS1) - graph.getSubgraph(vFS2));
        return max (1 + ms(graph - graph.getSubgraph(vFS1)), 3 + ms(graph - graph.getSubgraph(vFE) - graph.getSubgraph(vFF) - graph.getSubgraph(vFS2)));
    }
    return 1 + max (ms (graph - graph.getSubgraph(vFS2)), ms2(graph - graph.getSubgraph(vFS1) - s2, vS2));
}

bool edge (AdjList graph, int a, int b)
{
    set<int> v;
    if (graph.getVertexNeighborhood(a, v))
        return v.find(b) != v.end();
    return false;
}

bool is_contained (AdjList graph, set<int> A, set<int> B)
{
    for (set<int>::iterator it = A.begin(); it != A.end(); it++)
        if (B.find(*it) == B.end())
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
