#include <bits/stdc++.h>
#include "AdjList.h"

using namespace std;

#ifndef TREE_H
#define TREE_H

#define FREE                -1
#define BOUND               0
#define REQUIRED            1

int mds(AdjList g);
bool pegarEndVertex(AdjList g, int& v, int& u);

#endif // ROBSON_H
