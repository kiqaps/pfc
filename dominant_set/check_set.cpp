#include <bits/stdc++.h>
#include "./AdjMatrix.h"
#include "Dominant.h"

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    int new_set_member, n_vertex;
    set<int> dominant_set;

    cin >> n_vertex;

    AdjMatrix graph(n_vertex);

    for (int i = 0; i < n_vertex; i++)
        for (int j = 0; j < n_vertex; j++)
            cin >> graph[i][j];

    cin >> new_set_member;
    while (new_set_member >= 0 && new_set_member < n_vertex)
    {
        dominant_set.insert(new_set_member);
        cin >> new_set_member;
    }

    cout << is_dominant_set(graph, dominant_set) << endl;
    return 0;
}
