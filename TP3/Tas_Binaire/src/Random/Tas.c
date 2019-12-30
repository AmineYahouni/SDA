#include <stdlib.h>
#include "Tas.h"
#include "math.h"

static void HeapRealloc(Heap *heap);
static void reorganizeHeap(Heap *heap);

Heap* createHeap(void)
{
    Heap *heap = malloc(sizeof(Heap));
    if(!heap) return NULL;
    heap->tab = malloc(5*sizeof(int));   /* Prévoir l'échec de malloc */
    heap->capacity = 5;
    heap->size = 0;
    return heap;
}

/***************************************************************************/
static void HeapRealloc(Heap *heap)
{
    int new_size = 2*heap->capacity;
    heap->tab = realloc(heap->tab, new_size*sizeof(int));
                                         /* Prévoir l'échec de realloc */
    heap->capacity = new_size;
}

/***************************************************************************/
static void reorganizeHeap(Heap *heap)
{
    int tmp;
    int size = heap->size;
    int index = size/2;
    while(heap->tab[index] < heap->tab[size] && size>1)
    {
        tmp = heap->tab[size];
        heap->tab[size] = heap->tab[index];
        heap->tab[index] = tmp;

        index/=2;
        size/=2;
    }
}

/***************************************************************************/
void pushNode(Heap *heap, int value)
{
    if(heap->size >= heap->capacity-1) HeapRealloc(heap);
    heap->size++;
    heap->tab[heap->size] = value;
    reorganizeHeap(heap);
}

/***************************************************************************/
int popNode(Heap *heap)
{
    int tmp;
    int indexUp = 1;
    int indexDn = 2;

    if(heap->size==0) return -1;

    int value = heap->tab[1];
    heap->tab[1] = heap->tab[heap->size];
    heap->size--;

    while(indexDn<=heap->size)
    {
        if(indexDn+1 <= heap->size && heap->tab[indexDn] < heap->tab[indexDn+1])
        {
            indexDn++;
        }
        if(heap->tab[indexDn] > heap->tab[indexUp])
        {
            tmp = heap->tab[indexDn];
            heap->tab[indexDn] = heap->tab[indexUp];
            heap->tab[indexUp] = tmp;
        }
        indexUp = indexDn;
        indexDn *= 2;
    }
    return value;
}

/***************************************************************************/
void freeHeap(Heap *heap)
{
    free(heap->tab);
    free(heap);
}
/***************************************************************************/
double minHeap(Heap *heap)
{
double min;
int x=floor((heap->size-1)/2);
min=min=heap->tab[x];
int i=1;
while(i<=heap->size-1){
int tmp=floor((heap->size-1)/2)+i;
if(min>heap->tab[tmp])min=heap->tab[tmp];
i++;
}
return min;
}

