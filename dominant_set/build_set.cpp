#include <iostream>
#include <cstdio>
#include "AdjList.h"
#include "Dominant.h"

using namespace std;

int main()
{
    int order, input;

    cin >> order;
    AdjMatrix graph(order);

    for (int i = 0; i < order; i++)
        for (int j = 0; j < order; j++)
            cin >> graph[i][j];

    set<int> dominant_set = build_minimal_dominant_set(AdjList(graph));
    cout << "Minimal Dominant Set = {";
    for (set<int>::iterator it = dominant_set.begin(); it != dominant_set.end(); it++)
        cout << " " << *it;
    cout << " }" << endl;
    return 0;
}


