#include "AdjList.h"
#include "AdjMatrix.h"
#include <set>
#include <iostream>

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

AdjList::AdjList(AdjMatrix graph)
{
    this->order = graph.getOrder();
    for (int i = 0; i < this->order; i++)
        this->adj_list[i].clear();

    for(int i = 0; i < graph.getOrder(); i++)
        for (int j = 0; j < graph.getOrder(); j++)
            if (graph[i][j] == 1)
                adj_list[i].insert(j);
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

AdjList AdjList::getSubgraph(std::set<int> vertexes)
{
    AdjList ret;
    for (std::set<int>::iterator it = vertexes.begin(); it != vertexes.end(); it++)
    {
        std::set<int> neighborhood;
        if (this->getVertexNeighborhood(*it, neighborhood))
        {
            for (std::set<int>::iterator it2 = neighborhood.begin(); it2 != neighborhood.end();)
            {
                if (vertexes.find(*it2) == vertexes.end())
                    it2 = neighborhood.erase(it2);
                else it2++;
            }
            ret.addVertex(*it, neighborhood);
        }
    }
    return ret;
}

bool AdjList::getVertexNeighborhood(int vertex_id, std::set<int>& neighborhood)
{
    std::map< int, std::set<int> >::iterator it = this->adj_list.find(vertex_id);
    if (it != this->adj_list.end())
    {
        neighborhood = it->second;
        return true;
    }
    return false;
}

void AdjList::removeVertex(int vertex_id)
{
    std::map< int, std::set<int> >::iterator it = this->adj_list.find(vertex_id);

    if (it == this->adj_list.end())
        return;

    for (std::set<int>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); it2++)
    {
        std::map< int, std::set<int> >::iterator it3 = this->adj_list.find(*it2);
        (it3->second).erase(vertex_id);
    }
    this->order -= 1;
    this->adj_list.erase(it);
}

std::map< int, std::set<int> >::iterator AdjList::begin()
{
    return this->adj_list.begin();
}

std::map< int, std::set<int> >::iterator AdjList::end()
{
    return this->adj_list.end();
}

std::set<int>& AdjList::operator[] (const int vertex_id)
{
    return this->adj_list[vertex_id];
}

AdjList operator- (const AdjList& lhs, int rhs)
{
    AdjList ret(lhs);
    ret.removeVertex(rhs);
    return ret;
}

AdjList operator- (const AdjList& lhs, const AdjList& rhs)
{
    AdjList ret(lhs);
    for (std::map< int, std::set<int> >::const_iterator it = rhs.adj_list.begin(); it != rhs.adj_list.end(); it++)
        ret.removeVertex(it->first);
    return ret;
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
