#include "AdjList.h"
#include <set>
#include <ostream>

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

bool AdjList::addVertex(int vertex_id, std::set<int> adj_vertexes)
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
    for (std::map< int, std::set<int> >::iterator it = this->adj_list.begin(); it != this->adj_list.end(); it++)
    {
        int dd = (it->second).size();
        d = (d < dd) ? dd : d;
    }
    return d;
}

int AdjList::getMinimumDegree()
{
    int d = this->order;
    for (std::map< int, std::set<int> >::iterator it = this->adj_list.begin(); it != this->adj_list.end(); it++)
    {
        int dd = (it->second).size();
        d = (d > dd) ? dd : d;
    }
    return d;
}

int AdjList::getVertexDegree(int vertex_id)
{
    std::map< int, std::set<int> >::iterator it = this->adj_list.find(vertex_id);
    return (it == this->adj_list.end()) ? -1 : (it->second).size();
}

void AdjList::removeVertex(int vertex_id)
{
    std::map< int, std::set<int> >::iterator it = this->adj_list.find(vertex_id);
    for (std::set<int>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); it2++)
    {
        std::map< int, std::set<int> >::iterator it3 = this->adj_list.find(*it2);
        (it3->second).erase(vertex_id);
    }
    this->adj_list.erase(it);
}

std::ostream& operator<< (std::ostream& strm, AdjList& graph)
{
    for (std::map< int, std::set<int> >::iterator it = graph.adj_list.begin(); it != graph.adj_list.end(); it++)
    {
        strm << "[" << it->first << "] => {";
        for (std::set<int>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); it2++)
            strm << " " << *it2;
        strm << " }" << std::endl;
    }
    return strm;
}
