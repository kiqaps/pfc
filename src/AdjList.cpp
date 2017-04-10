#include "AdjList.h"
#include <vector>

AdjList::AdjList(int order)
{
    this->order = order;
    for (int i = 0; i < order; i++)
        this->adj_list[i].clear();
}

AdjList::AdjList()
{
    this->order = 0;
}

bool AdjList::addVertex(int vertex_id)
{
    if (this->adj_list.find(vertex_id) == this->adj_list.end())
    {
        this->order += 1;
        this->adj_list[vertex_id].clear();
        return true;
    }
    return false;
}

bool AdjList::addVertex(int vertex_id, std::vector<int> adj_vertexes)
{
    if (this->adj_list.find(vertex_id) == this->adj_list.end())
    {
        this->order += 1;
        this->adj_list[vertex_id] = adj_vertexes;
        return true;
    }
    return false;
}

int AdjList::getMaximumDegree()
{
    int d = 0;
    for (std::map< int, std::vector<int> >::iterator it = this->adj_list.begin(); it != this->adj_list.end(); it++)
    {
        int dd = (it->second).size();
        d = (d < dd) ? dd : d;
    }
    return d;
}

int AdjList::getMinimumDegree()
{
    int d = this->order;
    for (std::map< int, std::vector<int> >::iterator it = this->adj_list.begin(); it != this->adj_list.end(); it++)
    {
        int dd = (it->second).size();
        d = (d > dd) ? dd : d;
    }
    return d;
}

int AdjList::getVertexDegree(int vertex_id)
{
    std::map< int, std::vector<int> >::iterator it = this->adj_list.find(vertex_id);
    return (it == this->adj_list.end()) ? -1 : (it->second).size();
}

void AdjList::removeVertex(int vertex_id)
{
    // TODO
}
