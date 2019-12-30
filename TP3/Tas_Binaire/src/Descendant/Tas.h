#ifndef CGI_HEAP_H
#define CGI_HEAP_H

typedef struct
{
    int capacity;
    int size;
    int *tab;
}Heap;

#ifdef __cplusplus
extern "C" {
#endif

Heap* createHeap(void);

void pushNode(Heap *heap, int value);

int popNode(Heap *heap);

void freeHeap(Heap *heap);

#ifdef __cplusplus
}
#endif

#endif //CGI_HEAP_H
