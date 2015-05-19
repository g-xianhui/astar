#ifndef ASTAR_H
#define ASTAR_H

// f = g + h

// get g score
typedef int (*GScoreFunc)(void *ud, int index);
// get h score
typedef int (*HScoreFunc)(void *ud, int src, int dst);

typedef struct Array {
    int len;
    int cap;
    int *arr;
} Array;
Array* create_array(int cap);
void array_release(Array **parr);
void array_pushback(Array *arr, int index);

// get next adjacency index
typedef Array* (*GetAdjFunc)(void *ud, int pos);

void astar_init(GScoreFunc g, HScoreFunc h, GetAdjFunc n);

// return an array of index as path, or null if path not found
Array* astar_search(void *ud, int src, int dst);

#endif
