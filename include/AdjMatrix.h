#include "Graph.h"
#include <vector>

#ifndef ADJMATRIX_H
#define ADJMATRIX_H


class AdjMatrix: public Graph
{
    public:
        AdjMatrix(int);
        int getMaximumDegree();
        int getMinimumDegree();
        int getVertexDegree(int vertex_id);
        std::vector<int>& operator[] (const int x);
    protected:

    private:
        AdjMatrix();
        std::vector< std::vector< int > > matrix;

};

#endif // ADJMATRIX_H
