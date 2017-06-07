#include "robson.h"

using namespace std;

int ms(AdjList grafo)
{
    if (!is_connected(grafo))
    {
        vector<int> C = getSmallestComponent(grafo);
        return ms(grafo - C) + (C.size() <= 2 ? 1 : ms(subgrafo(grafo, C)));
    }

    if (grafo.ordem() <= 1)
        return grafo.ordem();

    int A = -1, B = -1;
    escolherAB(grafo, A, B);
    vector <int> vA = grafo.vizinhanca(A);
    vector <int> vFA = grafo.vizinhancaFechada(A);
    vector <int> vB = grafo.vizinhanca(B);
    vector <int> vFB = grafo.vizinhancaFechada(B);

    if (vA.size() == 1)
        return 1 + ms(grafo - vFA);

    if (vA.size() == 2)
    {
        auto it = vA.begin();
        if (*it == B)
            it++;
        int BB = *it;

        if (grafo.aresta(B, BB))
            return 1 + ms(grafo - vFA);

        vector<int> vFBB = grafo.vizinhancaFechada(BB);
        return max(2 + ms(grafo - vFB - vFBB), 1 + ms2(grafo - vFA, n2(grafo, A, vA)));
    }

    if (vA.size() == 3)
        return max(ms2(grafo - A, vA), 1 + ms(grafo - vFA));

    if (estaContido(vFA, vFB)) // Se A domina B
        return ms(grafo - B);

    return max(ms(grafo - B), 1 + ms(grafo - vFB));
}

int ms1(AdjList grafo, int s1, int s2)
{
    vector<int> vS1 = grafo.vizinhanca(s1);
    vector<int> vFS1 = grafo.vizinhancaFechada(s1);
    vector<int> vS2 = grafo.vizinhanca(s2);
    vector<int> vFS2 = grafo.vizinhancaFechada(s2);

    if (vS1.size() <= 1)
        return ms(grafo);

    if (grafo.aresta(s1, s2))
    {
        if (vS1.size() <= 3)
            return ms(grafo);

        return 1 + max(ms(grafo - vFS1), ms(grafo - vFS2));
    }

    vector<int> vS1_interseccao_vS2 = interseccao(vS1, vS2);

    if (vS1_interseccao_vS2.size() > 0)
        return ms1(grafo - vS1_interseccao_vS2, s1, s2);

    if (vS2.size() == 2)
    {
        auto it = vS1.begin();
        int E = *(it++);
        int F = *it;
        vector<int> vE = grafo.vizinhanca(E);
        vector<int> vFE = grafo.vizinhancaFechada(E);
        vector<int> vF = grafo.vizinhanca(F);
        vector<int> vFF = grafo.vizinhancaFechada(F);

        if (grafo.aresta(E, F))
            return 1 + ms(grafo - vFS1);

        vector<int> vE_uniao_vF = uniao(vE, vF);
        auto it2 = find(vE_uniao_vF.begin(), vE_uniao_vF.end(), s1);
        if (it2 != vE_uniao_vF.end())
            vE_uniao_vF.erase(it2);

        if (estaContido(vE_uniao_vF, vS2))
            return 3 + ms(grafo - vFS1 - vFS2);

        return max(1 + ms(grafo - vFS1), 3 + ms(grafo - vFE - vFF - vFS2));

    }
    return 1 + max(ms(grafo - vFS2), ms2(grafo - vFS1 - s2, vS2));
}

int ms2(AdjList grafo, vector<int> vertices)
{
    vertices = ordena(grafo, vertices);
    if (vertices.size() <= 1)
        return 0;

    if (vertices.size() == 2)
    {
        if (grafo.aresta(vertices[0], vertices[1]))
            return 0;
        else
        {
            vector<int> vFS1 = grafo.vizinhancaFechada(vertices[0]);
            vector<int> vFS2 = grafo.vizinhancaFechada(vertices[1]);
            return 2 + ms(grafo - vFS1 - vFS2);
        }
    }

    if (vertices.size() == 3)
    {
        vector<int> vS1 = grafo.vizinhanca(vertices[0]);

        if (vS1.size() == 0)
            return 1 + ms1(grafo - vertices[0], *(next(vertices.begin())), *(next(vertices.begin(), 2)));

        if (grafo.aresta(vertices[0], vertices[1])
            && grafo.aresta(vertices[1], vertices[2])
            && grafo.aresta(vertices[2], vertices[0]))
            return 0;

        int xx[3][2] =
        {
            {1, 2},
            {0, 2},
            {0, 1}
        };

        for (int i = 0; i < 3; i++)
        {
            if (grafo.aresta(vertices[i], vertices[xx[i][0]]) && grafo.aresta(vertices[i], vertices[xx[i][1]]))
            {
                vector<int> vFJ = grafo.vizinhancaFechada(vertices[xx[i][0]]);
                vector<int> vFK = grafo.vizinhancaFechada(vertices[xx[i][1]]);
                return 2 + ms(grafo - vFJ - vFK);
            }
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                if (grafo.aresta(vertices[i], vertices[xx[i][j]]))
                {
                    int k = 1 - j;
                    vector<int> vFK = grafo.vizinhancaFechada(vertices[xx[i][k]]);
                    return 1 + ms1(grafo - vFK, vertices[i], vertices[xx[i][j]]);
                }
            }
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                vector<int> vSI = grafo.vizinhanca(vertices[i]);
                vector<int> vSJ = grafo.vizinhanca(vertices[xx[i][j]]);
                vector<int> vSI_uniao_vSJ = uniao(vSI, vSJ);

                for (auto it = grafo.begin(); it != grafo.end(); it++)
                {
                    if (find(vSI_uniao_vSJ.begin(), vSI_uniao_vSJ.end(), it->first) != vSI_uniao_vSJ.end())
                        return ms2(grafo - it->first, vertices);
                }
            }
        }

        vector<int> vFS1 = grafo.vizinhancaFechada(vertices[0]);
        if (vS1.size() == 1)
            return 1 + ms1(grafo - vFS1, *(next(vertices.begin())), *(next(vertices.begin(), 2)));

        vector<int> vFS2 = grafo.vizinhancaFechada(vertices[1]);
        vector<int> vFS3 = grafo.vizinhancaFechada(vertices[2]);
        return max(1 + ms1(grafo - vFS1, *(next(vertices.begin())), *(next(vertices.begin(), 2))),
            ms2(grafo - vFS2 - vFS3 - vertices[0], vFS1));
    }

    if (vertices.size() == 4)
    {
        for (auto it = grafo.begin(); it != grafo.end(); it++)
            if ((it->second).size() <= 3)
                return ms(grafo);

        vector<int> vFS1 = grafo.vizinhancaFechada(vertices[0]);
        vector<int> SmenosS1 = vertices;
        SmenosS1.erase(SmenosS1.begin());
        return max(1 + ms(grafo - vFS1), ms2(grafo - vertices[0], SmenosS1));
    }
    return ms(grafo);
}

vector<int> ordena(AdjList grafo, vector<int> v)
{
    vector< pair<int, int> > vetorPar;

    for (size_t i = 0; i < v.size(); i++)
        vetorPar.push_back(make_pair(v[i], grafo.grau(v[i])));

    sort(vetorPar.begin(), vetorPar.end(), [](const pair<int,int> & left, const pair<int,int> & right){
            return left.second < right.second;
         });

    vector<int> ret;
    for (size_t i = 0; i < v.size(); i++)
        ret.push_back(vetorPar[i].first);
    return ret;
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

vector<int> n2(AdjList grafo, int A, vector<int> vizinhanca)
{
    vector<int> n2;
    for (size_t i = 0; i < vizinhanca.size(); i++)
    {
        vector <int> v2 = grafo.vizinhanca(vizinhanca[i]);
        n2 = uniao(n2, v2);
    }
    auto it = find(n2.begin(), n2.end(), A);
    if (it != n2.end())
        n2.erase(it);
    return n2;
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
    map<int, bool> visited;

    while (get_next_connected_component(visited, graph, c))
    {
        if (c.size() <= t) {
            t = c.size();
            smallest = vector<int>(c);
        }
    }
    return smallest;
}

bool get_next_connected_component(map<int,bool> & visited, AdjList graph, vector<int> & component)
{
    auto it = graph.begin();
    for (; it != graph.end(); it++)
        if (!visited[it->first])
            break;

    if (it == graph.end())
        return false;

    component.clear();
    bfs(visited, graph, it->first,  &component);
    return true;
}

bool is_connected (AdjList graph)
{
    map<int, bool> visited;
    auto it = graph.begin();
    bfs(visited, graph, it->first);
    for (auto it = graph.begin(); it != graph.end(); it++)
        if (!visited[it->first])
            return false;
    return true;
}

void bfs(map<int, bool> & visited, AdjList graph, int vertex, vector<int>* c)
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
