#include <bits/stdc++.h>
#include "AdjList.h"
#include "AdjMatrix.h"
#include "Independent.h"

using namespace std;

void imprimir(int v) { cout << v << endl; }
int main()
{
    freopen("input.txt", "r", stdin);

    int n_vertexes;
    cin >> n_vertexes;

    AdjMatrix graph(n_vertexes);

    for (int i = 0; i < n_vertexes; i++)
        for (int j = 0; j < n_vertexes; j++)
            cin >> graph[i][j];

    cout << is_connected(AdjList(graph)) << endl;

    set<int> c;
    vector<bool> v(graph.getOrder(), false);
    while(get_next_connected_component(v, AdjList(graph), c))
    {
        cout << "Component:" << endl;
        for (set<int>::iterator it = c.begin(); it!=c.end(); it++)
            cout << "\t" << *it << endl;
    }
}
