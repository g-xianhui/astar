#include "astar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 0
#define N 16

typedef struct Node {
    int index;
    int cost;
    int x, y;
} Node;

typedef struct Map {
    Node nodes[N * N];
} Map;

int gscore(void *ud, int index) {
    Map *map = (Map *)ud;
    return map->nodes[index].cost;
}

int hscore(void *ud, int src, int dst) {
    Map *map = (Map *)ud;
    int x1 = map->nodes[src].x;
    int y1 = map->nodes[src].y;
    int x2 = map->nodes[dst].x;
    int y2 = map->nodes[dst].y;
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

Array* adjacency(void *ud, int pos) {
    Map *map = (Map *)ud;
    Array *arr = create_array(8);
    int index = pos - 4;
    int i;
    for (i = 0; i < 9; i++, index++) {
        if (index < 0 || index >= N * N || index == pos)
            continue;
        if (map->nodes[index].cost == MAX)
            continue;
        array_pushback(arr, index);
    }
    return arr;
}

int main(int argc, char **argv) {
    if (argc < 3)
        exit(1);

    srand(time(NULL));
    Map *map = (Map *)malloc(sizeof(*map));
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            int index = i * N + j;
            map->nodes[index].x = i;
            map->nodes[index].y = j;
            map->nodes[index].cost = rand() % 10;
            map->nodes[index].index = index;
        }
    }

    astar_init(gscore, hscore, adjacency);

    int src = atoi(argv[1]);
    int dst = atoi(argv[2]);
    Array *path = astar_search(map, src, dst);
    if (!path) {
        printf("path not found!\n");
        exit(1);
    }

    int pos = path->len;
    while (pos > 0) {
        printf("%d", path->arr[--pos]);
        if (pos > 0)
            printf(" -> ");
    }
    printf("\n");
    exit(0);
}
