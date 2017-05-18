#include "AdjList.h"
#include "AdjMatrix.h"
#include <set>

#ifndef INDEPENDENT_H_INCLUDED
#define INDEPENDENT_H_INCLUDED

std::set<int> build_maximal_independent_set(AdjList graph);
bool is_independent_set(AdjMatrix g, std::set<int> the_set);
bool is_maximal_independent_set(AdjMatrix graph, std::set<int> the_set);

void bfs(std::vector<bool> & visited, AdjList graph, int vertex, std::set<int>* c = NULL);
bool is_connected (AdjList graph);
bool get_next_connected_component(std::vector<bool> & visited, AdjList graph, std::set<int> & component);

#endif // INDEPENDENT_H_INCLUDED
