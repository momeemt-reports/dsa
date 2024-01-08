#include "floyd.h"

void floyd(int **input, int **output, unsigned int length, int ***path) {
    int **path_result = (int **)malloc(sizeof(int *) * length);
    *path = (int **)malloc(sizeof(int *) * length);
    for (unsigned int i = 0; i < length; i++) {
        path_result[i] = (int *)malloc(sizeof(int) * length);
        (*path)[i] = (int *)malloc(sizeof(int) * length);
        for (unsigned int j = 0; j < length; j++) {
            path_result[i][j] = input[i][j];
            if (i == j || input[i][j] == INT_MAX) {
                (*path)[i][j] = -1;
            } else {
                (*path)[i][j] = i;
            }
        }
    }

    for (unsigned int k = 0; k < length; k++) {
        for (unsigned int i = 0; i < length; i++) {
            for (unsigned int j = 0; j < length; j++) {
                if (path_result[i][k] == INT_MAX || path_result[k][j] == INT_MAX) continue;

                if ((path_result[i][k] + path_result[k][j]) < path_result[i][j]) {
                    path_result[i][j] = path_result[i][k] + path_result[k][j];
                    (*path)[i][j] = (*path)[k][j];
                }
            }
        }
    }

    for (unsigned int i = 0; i < length; i++) {
        for (unsigned int j = 0; j < length; j++) {
            output[i][j] = path_result[i][j];
        }
    }

    for (unsigned int i = 0; i < length; i++) {
        free(path_result[i]);
    }
    free(path_result);
}

void build_path(int **path, int start, int end, char *output) {
    if (start == end) {
        sprintf(output + strlen(output), "%d", start);
    } else if (path[start][end] == -1) {
        strcat(output, "Nothing");
    } else {
        build_path(path, start, path[start][end], output);
        sprintf(output + strlen(output), " %d", end);
    }
}

void path_to_string(int **path, int start, int end, char *output) {
    output[0] = '\0';
    build_path(path, start, end, output);
}
