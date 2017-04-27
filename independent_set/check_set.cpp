#include <iostream>
#include <set>
#include "AdjMatrix.h"

using namespace std;

bool is_independent_set(AdjMatrix g, set<int> the_set);

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

    cout << is_independent_set(graph, independent_set) << endl;
    return 0;
}

bool is_independent_set(AdjMatrix g, set<int> the_set)
{
    set<int>::iterator prev = the_set.end(); prev--;
    bool is_independent_set = true;
    for (set<int>::iterator it = the_set.begin(); it != prev && is_independent_set; it++)
    {
        set<int>::iterator it2 = it;
        for (it2++; it2 != the_set.end(); it2++)
        {
            if (g[*it][*it2] == 1)
            {
                is_independent_set = false;
                break;
            }
        }
    }
    return is_independent_set;
}
