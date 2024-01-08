#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define N 6
#define M INT_MAX

extern int w[N][N];
extern bool S[N];
extern int Scount;
extern int d[N];
extern int parent[N];

void add(int u, bool S[]);

bool remain();

int select_min();

bool member(int u, int x);

void dijkstra(int p);

void display(char* name, int* ary, int length);

void get_shortest_path(int* parent, int p, int q, char* result);
