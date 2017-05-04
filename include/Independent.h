#include "AdjList.h"
#include "AdjMatrix.h"
#include <set>

#ifndef INDEPENDENT_H_INCLUDED
#define INDEPENDENT_H_INCLUDED

std::set<int> build_maximal_independent_set(AdjList graph);
bool is_independent_set(AdjMatrix g, std::set<int> the_set);
bool is_maximal_independent_set(AdjMatrix graph, std::set<int> the_set);


#endif // INDEPENDENT_H_INCLUDED
