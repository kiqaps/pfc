#include <bits/stdc++.h>
#include "AdjList.h"

using namespace std;

#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

bool is_dominating_set(AdjList g, vector<int> vertices);
bool is_minimal_dominating_set(AdjList g, vector<int> vertices);
vector<int> build_minimal_dominating_set(AdjList graph);
int mds_bruteforce(AdjList g);
int mds_bruteforce_improved(AdjList g);

string create_bitmask(int N, int K);
bool next_combination(int N, string & bitmask, vector<int> & combination);

#endif // BRUTEFORCE_H
