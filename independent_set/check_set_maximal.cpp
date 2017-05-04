#include <iostream>
#include <cstdio>
#include <set>
#include "AdjMatrix.h"
#include "Independent.h"

using namespace std;

int main()
{
    int new_set_member, n_vertex;
    set<int> independent_set;

    cin >> n_vertex;

    AdjMatrix graph(n_vertex);

    for (int i = 0; i < n_vertex; i++)
        for (int j = 0; j < n_vertex; j++)
            cin >> graph[i][j];

    cin >> new_set_member;
    while (new_set_member >= 0 && new_set_member < n_vertex)
    {
        independent_set.insert(new_set_member);
        cin >> new_set_member;
    }

    cout << is_maximal_independent_set(graph, independent_set) << endl;
    return 0;
}
