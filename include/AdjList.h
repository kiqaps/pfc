#include "Graph.h"
#include <map>
#include <set>
#include <ostream>

#ifndef ADJLIST_H
#define ADJLIST_H

class AdjList: public Graph
{
    public:
        AdjList(int order);
        AdjList();
        bool addVertex(int vertex_id);
        bool addVertex(int vertex_id, std::set<int> adj_vertexes);
        void removeVertex(int vertex_id);
        int getMaximumDegree();
        int getMinimumDegree();
        int getVertexDegree(int vertex_id);
        std::map< int, std::set<int> >::iterator begin();
        std::map< int, std::set<int> >::iterator end();
        std::set<int>& operator[] (const int vertex_id);
        friend std::ostream& operator<< (std::ostream& strm, AdjList& graph);

    private:
        std::map< int, std::set<int> > adj_list;
};

#endif // ADJLIST_H
