#include <bits/stdc++.h>
#include "AdjList.h"

using namespace std;

#ifndef ROBSON_H
#define ROBSON_H

int ms(AdjList grafo);
int ms1(AdjList grafo, int s1, int s2);
int ms2(AdjList grafo, vector<int> vertices);
vector<int> ordena(AdjList grafo, vector<int> v);
void escolherAB(AdjList graph, int& a, int& b);
vector<int> n2(AdjList grafo, int A, vector<int> vizinhanca);
vector<int> uniao (vector<int> v1, vector<int> v2);
vector<int> interseccao (vector<int> v1, vector<int> v2);
bool estaContido(vector<int> v1, vector<int> v2);
AdjList subgrafo(AdjList grafo, vector<int> vertices);
vector<int> getSmallestComponent (AdjList graph);
bool get_next_connected_component(map<int,bool> & visited, AdjList graph, vector<int> & component);
bool is_connected (AdjList graph);
void bfs(map<int,bool> & visited, AdjList graph, int vertex, vector<int>* c = NULL);

#endif // ROBSON_H
