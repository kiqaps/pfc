#include "AdjMatrix.h"
#include <vector>

AdjMatrix::AdjMatrix(int order)
{
    this->order = order;
    this->matrix = std::vector< std::vector<int> >(order, std::vector<int>(order, 0));
}

int AdjMatrix::getMaximumDegree()
{
    int d = this->order + 1;
    for (int i = 0; i < this->order; i++)
    {
        int dd = this->getVertexDegree(i);
        d = (dd > d) ? dd : d;
    }
    return d;
}

int AdjMatrix::getMinimumDegree()
{
    int d = this->order + 1;
    for (int i = 0; i < this->order; i++)
    {
        int dd = this->getVertexDegree(i);
        d = (dd < d) ? dd : d;
    }
    return d;
}

int AdjMatrix::getVertexDegree(int vertex_id)
{
    int d = 0;
    for (int i = 0; i < this->order; i++)
        if (this->matrix[vertex_id][i] == 1)
            d++;
    return d;
}

std::vector<int>& AdjMatrix::operator[] (const int x)
{
    return this->matrix[x];
}
