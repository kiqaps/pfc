#include <bits/stdc++.h>
#include "AdjList.h"

using namespace std;

#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

bool is_independent_set(AdjList g, vector<int> vertices);
bool is_maximal_independent_set(AdjList g, vector<int> vertices);
vector<int> build_maximal_independent_set(AdjList graph);
int mis_bruteforce(AdjList g, int fromWhere = 0);
string create_bitmask(int N, int K);
bool next_combination(int N, string & bitmask, vector<int> & combination);

#endif // BRUTEFORCE_H
