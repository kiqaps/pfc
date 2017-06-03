#include "AdjList.h"

using namespace std;

AdjList::AdjList(Mat matriz_adj)
{
    int ordem = matriz_adj.size();

    for (int i = 0; i < ordem; i++)
        adj_list[i].clear();

    for (int i = 0; i < ordem; i++)
    {
        for (int j = i + 1; j < ordem; j++)
        {
            if (matriz_adj[i][j])
            {
                adj_list[i].push_back(j);
                adj_list[j].push_back(i);
            }
        }
        sort(adj_list[i].begin(), adj_list[i].end());
    }
}

int AdjList::ordem()
{
    return adj_list.size();
}

int AdjList::grauMinimo()
{
    int grau_minimo = INT_MAX;
    for (auto it = adj_list.begin(); it != adj_list.end(); it++)
        grau_minimo = min (grau_minimo, (int)(it->second).size());
    return grau_minimo;
}

int AdjList::grauMaximo()
{
    int grau_maximo = INT_MIN;
    for (auto it = adj_list.begin(); it != adj_list.end(); it++)
        grau_maximo = max (grau_maximo, (int)(it->second).size());
    return grau_maximo;
}

int AdjList::grau(int vertice)
{
    return adj_list[vertice].size();
}

bool AdjList::aresta(int v1, int v2)
{
    return find(adj_list[v1].begin(), adj_list[v1].end(), v2) != adj_list[v1].end();
}

map< int, vector<int> >::iterator AdjList::begin()
{
    return adj_list.begin();
}

map< int, vector<int> >::iterator AdjList::end()
{
    return adj_list.end();
}

vector<int> AdjList::vizinhanca(int vertice)
{
    return adj_list[vertice];
}

vector<int> AdjList::vizinhancaFechada(int vertice)
{
    vector<int> v = adj_list[vertice];
    v.push_back(vertice);
    return v;
}

void AdjList::removerVertice(int vertice)
{
    vector<int> vizinhos = adj_list[vertice];
    for (size_t i = 0; i < vizinhos.size(); i++)
    {
        vector<int>& v = adj_list[vizinhos[i]];
        auto it = find(v.begin(), v.end(), vertice);
        v.erase(it);
    }
    adj_list.erase(vertice);
}

AdjList operator- (const AdjList& lhs, vector<int> rhs)
{
    AdjList ret(lhs);
    for (size_t i = 0; i < rhs.size(); i++)
        ret.removerVertice(rhs[i]);
    return ret;
}

AdjList operator- (const AdjList& lhs, int rhs)
{
    AdjList ret(lhs);
    ret.removerVertice(rhs);
    return ret;
}

ostream& operator<< (ostream& strm, AdjList& graph)
{
    for (auto it = graph.adj_list.begin(); it != graph.adj_list.end(); it++)
    {
        strm << "[" << it->first << "] => {";
        for (size_t i = 0; i < (it->second).size(); i++)
            strm << " " << (it->second)[i];
        strm << " }" << endl;
    }
    return strm;
}
