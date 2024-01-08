#include "dijkstra.h"

void add(int u, bool S[]) {
    if (S[u]) return;
    S[u] = true;
    Scount++;
}

bool remain() {
    return Scount < N;    
}

int select_min() {
    int target = M;
    int target_index = -1;
    for (int index = 0; index < N; index++) {
        if (!S[index] && d[index] < target) {
            target = d[index];
            target_index = index;
        }
    } 
    return target_index;
}

bool member(int u, int x) {
    return w[u][x] != M;
}

void dijkstra(int p) {
    add(p, S);

    for (int i = 0; i < N; i++) {
        d[i] = w[p][i];
        parent[i] = p;
    }

    while (remain()) {
        int u = select_min();
        if (u == -1) {
            break;
        } else {
            add(u, S);
        }

        for (int x = 0; x < N; x++) {
            if (member(u, x)) {
                int k = d[u] + w[u][x];
                if (d[x] == M) {
                    d[x] = k;
                    parent[x] = u;
                } else if (k < d[x]) {
                    d[x] = k;
                    parent[x] = u;
                }
            }
        }
    }
}

void display(char* name, int* ary, int length) {
    printf("%s: [", name);
    for (int i = 0; i < length; i++) {
        if (ary[i] == M) {
            printf(" M");
        } else {
            printf(" %d", ary[i]);
        }
    }
    printf(" ]\n");
}

void get_shortest_path(int *parent, int p, int q, char *result) {
    if (parent[q] == p && !member(p, q)) {
        strcpy(result, "Nothing");
        return;
    }

    if (q == p) {
        sprintf(result, "%d", p);
        return;
    }

    char temp[1000];
    get_shortest_path(parent, p, parent[q], temp);
    sprintf(result, "%s %d", temp, q);
}
