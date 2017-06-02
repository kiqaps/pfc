#include "Graph.h"
#include "AdjMatrix.h"
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
        AdjList(AdjMatrix graph);
        AdjList(const AdjList& graph) = default;
        bool getVertexNeighborhood(int vertex_id, std::set<int>& neighborhood);
        bool addVertex(int vertex_id);
        bool addVertex(int vertex_id, std::set<int> adj_vertexes);
        void removeVertex(int vertex_id);
        int getMaximumDegree();
        int getMinimumDegree();
        int getVertexDegree(int vertex_id);
        AdjList getSubgraph(std::set<int> vertexes);
        std::map< int, std::set<int> >::iterator begin();
        std::map< int, std::set<int> >::iterator end();
        std::set<int>& operator[] (const int vertex_id);
        friend AdjList operator- (const AdjList& lhs, const AdjList& rhs);
        friend AdjList operator- (const AdjList& lhs, int rhs);
        friend std::ostream& operator<< (std::ostream& strm, AdjList& graph);

    private:
        std::map< int, std::set<int> > adj_list;
};

#endif // ADJLIST_H
