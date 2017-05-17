#include <iostream>
#include <cstdio>
#include "AdjList.h"
#include "Independent.h"

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    int order, input;

    cin >> order;
    AdjMatrix graph(order);

    for (int i = 0; i < order; i++)
        for (int j = 0; j < order; j++)
            cin >> graph[i][j];

    set<int> independent_set = build_maximal_independent_set(AdjList(graph));
    cout << "Independent_Set = {";
    for (set<int>::iterator it = independent_set.begin(); it != independent_set.end(); it++)
        cout << " " << *it;
    cout << " }" << endl;
    return 0;
}
