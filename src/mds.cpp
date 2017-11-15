#include "mds.h"

using namespace std;

int mds(AdjList g)
{
    vector<int> status(g.ordem(), BOUND);

    int mds = 0;

    while (g.ordem() > 2)
    {
        vector< vector<int> > vizinhos(3, vector<int>());
        vector< vector<int> > endVertexes(3, vector<int>());

        for (auto it = g.begin(); it != g.end(); it++)
        {
            vector<int> vv = it->second;
            if (vv.size() == 1)
            {
                endVertexes[status[it->first] + 1].push_back(it->first);
                vizinhos[status[it->first] + 1].push_back(vv[0]);
            }
        }

        while (!endVertexes[0].empty())
        {
            int v = endVertexes[0].back();
            g = g - v;
            endVertexes[0].pop_back();
        }

        while (!endVertexes[1].empty())
        {
            int v = endVertexes[1].back();
            int u = vizinhos[1].back();

            status[u] = REQUIRED;
            g = g - v;

            endVertexes[1].pop_back();
            vizinhos[1].pop_back();
        }

        while (!endVertexes[2].empty())
        {
            int v = endVertexes[2].back();
            int u = vizinhos[2].back();

            mds++;
            if (status[u] != REQUIRED)
                status[u] = FREE;
            g = g - v;

            endVertexes[2].pop_back();
            vizinhos[2].pop_back();
        }
    }

    if (g.ordem() == 2)
    {
        auto it = g.begin();
        auto it2 = next(g.begin());

        if (status[it->first] == REQUIRED && status[it2->first] == REQUIRED)
            mds += 2;
        else if (status[it->first] != FREE || status[it2->first] != FREE)
            mds++;
    }
    else if (g.ordem() == 1)
    {
        auto it = g.begin();
        if (status[it->first] != FREE)
            mds++;
    }
    return mds;
}
