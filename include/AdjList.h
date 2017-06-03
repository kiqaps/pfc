#include <bits/stdc++.h>

using namespace std;

#ifndef ADJLIST_H
#define ADJLIST_H

typedef vector< vector<int> > Mat;

class AdjList
{
    public:
        AdjList(Mat matriz_adj);
        AdjList(const AdjList& graph) = default;
        int ordem();
        int grauMinimo();
        int grauMaximo();
        int grau(int vertice);
        bool aresta(int v1, int v2);
        vector<int> vizinhanca(int vertice);
        vector<int> vizinhancaFechada(int vertice);
        map< int, vector<int> >::iterator begin();
        map< int, vector<int> >::iterator end();
        void removerVertice(int vertice);
        friend AdjList operator- (const AdjList& lhs, vector<int> rhs);
        friend AdjList operator- (const AdjList& lhs, int rhs);
        friend ostream& operator<< (ostream& strm, AdjList& graph);

    private:
        map< int, vector<int> > adj_list;
};

#endif // ADJLIST_H
