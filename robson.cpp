#include <bits/stdc++.h>
#include "AdjList.h"

using namespace std;

int ms(AdjList grafo);
void escolherAB(AdjList graph, int& a, int& b);
vector<int> uniao (vector<int> v1, vector<int> v2);
vector<int> interseccao (vector<int> v1, vector<int> v2);
bool estaContido(vector<int> v1, vector<int> v2);
AdjList subgrafo(AdjList grafo, vector<int> vertices);
vector<int> getSmallestComponent (AdjList graph);
bool get_next_connected_component(vector<bool> & visited, AdjList graph, vector<int> & component);
bool is_connected (AdjList graph);
void bfs(vector<bool> & visited, AdjList graph, int vertex, vector<int>* c = NULL);

int main()
{
    freopen("input.txt", "r", stdin);

    int ordem;
    cin >> ordem;
    Mat matriz(ordem, vector<int>(ordem));

    for (int i = 0; i < ordem; i++)
        for (int j = 0; j < ordem; j++)
            cin >> matriz[i][j];

    AdjList grafo(matriz);
    int a, b;
    escolherAB(grafo, a, b);
    cout << a << endl << b << endl;
    return 0;
}

int ms(AdjList grafo)
{
    cout << grafo << endl << endl;
    if (!is_connected(grafo))
    {
        vector<int> C = getSmallestComponent(grafo);
        return ms(grafo - C) + (C.size() <= 2 ? 1 : ms(subgrafo(grafo, C)));
    }

    if (grafo.ordem() <= 1)
        return grafo.ordem();

    int A = -1, B = -1;
    escolherAB(grafo, A, B);
    vector<int> vFB = grafo.vizinhancaFechada(B);
    return max(ms(grafo - B), 1 + ms(grafo - vFB));
}

void escolherAB(AdjList graph, int& a, int& b)
{
    size_t dd, d = graph.ordem();
    for (auto it = graph.begin(); it != graph.end(); it++)
    {
        if (d > (it->second).size())
        {
            dd = 0;
            d = (it->second).size();
            a = it->first;
            for (size_t i = 0; i < d; i++)
            {
                size_t degree = graph.grau((it->second)[i]);
                if (dd < degree)
                {
                    dd = degree;
                    b = (it->second)[i];
                }
            }
        }
        else if (d == (it->second).size())
        {
            for (size_t i = 0; i < d; i++)
            {
                size_t degree = graph.grau((it->second)[i]);
                if (dd < degree)
                {
                    dd = degree;
                    b = (it->second)[i];
                    a = it->first;
                }
            }
        }
    }
}

vector<int> uniao (vector<int> v1, vector<int> v2)
{
    vector<int> ret (v1.size() + v2.size());
    auto it = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), ret.begin());
    ret.resize(it - ret.begin());
    return ret;
}

vector<int> interseccao (vector<int> v1, vector<int> v2)
{
    vector<int> ret (v1.size() + v2.size());
    auto it = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), ret.begin());
    ret.resize(it - ret.begin());
    return ret;
}

bool estaContido(vector<int> v1, vector<int> v2)
{
    vector<int> ret (v1.size());
    auto it = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), ret.begin());
    ret.resize(it - ret.begin());
    return ret.size() == 0;
}

AdjList subgrafo(AdjList grafo, vector<int> vertices)
{
    vector<int> outer;
    for (auto it = grafo.begin(); it != grafo.end(); it++)
        if (find(vertices.begin(), vertices.end(), it->first) == vertices.end())
            outer.push_back(it->first);
    return grafo - outer;
}

vector<int> getSmallestComponent (AdjList graph)
{
    size_t t = graph.ordem();
    vector<int> c, smallest;
    vector<bool> visited(graph.ordem(), false);

    while (get_next_connected_component(visited, graph, c))
    {
        if (c.size() <= t) {
            t = c.size();
            smallest = vector<int>(c);
        }
    }
    return smallest;
}

bool get_next_connected_component(vector<bool> & visited, AdjList graph, vector<int> & component)
{
    int i;
    for (i = 0; i < graph.ordem(); i++)
        if (!visited[i])
            break;

    if (i == graph.ordem())
        return false;

    component.clear();
    bfs(visited, graph, i,  &component);
    return true;
}

bool is_connected (AdjList graph)
{
    vector<bool> visited(graph.ordem(), false);
    bfs(visited, graph, 0);
    for (int i = 0; i < graph.ordem(); i++)
        if (!visited[i])
            return false;
    return true;
}

void bfs(vector<bool> & visited, AdjList graph, int vertex, vector<int>* c)
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
            c->push_back(v);

        vector<int> vizinhanca = graph.vizinhanca(v);
        for (size_t i = 0; i < vizinhanca.size(); i++)
        {
            if (enqueued.find(vizinhanca[i]) == enqueued.end())
            {
                vertexes.push(vizinhanca[i]);
                enqueued.insert(vizinhanca[i]);
            }
        }
    }
}
