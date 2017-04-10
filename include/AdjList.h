#include "Graph.h"
#include <map>
#include <vector>

#ifndef ADJLIST_H
#define ADJLIST_H

class AdjList: public Graph
{
    public:
        AdjList(int order);
        AdjList();
        bool addVertex(int vertex_id);
        bool addVertex(int vertex_id, std::vector<int> adj_vertexes);
        void removeVertex(int vertex_id);
        int getMaximumDegree();
        int getMinimumDegree();
        int getVertexDegree(int vertex_id);

    private:
        std::map< int, std::vector<int> > adj_list;
};

#endif // ADJLIST_H
