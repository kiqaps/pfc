#include "AdjList.h"
#include "AdjMatrix.h"
#include <set>

#ifndef DOMINANT_H_INCLUDED
#define DOMINANT_H_INCLUDED

std::set<int> build_minimal_dominant_set(AdjList graph);
bool is_dominant_set(AdjMatrix g, std::set<int> the_set);
bool is_minimal_dominant_set(AdjMatrix g, std::set<int> the_set);

#endif // DOMINANT_H_INCLUDED
