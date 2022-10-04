#pragma once

#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * Implements
 * - Graphs
 * - Queue
 * - Stack
 * - Heap *
 * - Priority Queue *
 * - Hashtable *
 * - Extendable Array *
 */

/**
 * Vertex
 */
typedef struct vertex {
  int r;
  int c;
  struct vertex* edges[4];
  struct vertex* prev;
  int dist;
  bool seen;
} vertex;

vertex* createVertex (int r, int c);
int distance (vertex* a, vertex* b);

/**
 * Graph
 */
typedef struct graph {
  vertex* start;
  vertex* end;
} graph;

graph* createGraph (vertex* start, vertex* end);

/**
 * queue
 * 
 * enque
 * deque
 */
typedef struct queueItem {
  struct queueItem* next;
  struct queueItem* prev;
  void* data;
} queueItem;

typedef struct queue {
  queueItem* head;
  queueItem* tail;
  int size;
} queue;

queue* createQueue();
void enqueue (queue* q, void* data);
void* dequeue (queue* q);
void qfree(queue* q);

/**
 * stack
 * 
 * push
 * pop
 */
typedef struct stackItem {
  struct stackItem* next;
  void* data;
} stackItem;

typedef struct stack {
  stackItem* head;
  int size;
} stack;

stack* createStack();
void spush(stack* s, void* data);
void* spop(stack* s);
void sfree(stack* s);

/**
 * Extenible Array
 * 
 * get
 * set
 * add
 * pop
 */
typedef struct earray {
  void** array;
  int maxLen;
  int length;
} earray;

earray* createEarray();
void* eget(earray* e, int index);
void eset(earray* e, int index, void* item);
void eadd(earray* e, void* item);
void* epop(earray* e);
void efree(earray* e);

/**
 * heap
 * 
 * enque
 * deque
 */
typedef struct heapItem {
  struct heapItem* next;
  struct heapItem* prev;
  void* data;
} heapItem;

typedef struct heap {
  heapItem* head;
  heapItem* tail;
  int size;
} heap;

heap* createHeap();
void heapAdd (heap* q, void* data);
void* heapGet (heap* q);
void hfree(earray* e);

/**
 * Priority Queue
 * 
 * penqueue
 * pdequeue
 */
typedef heap pqueue;

pqueue* createPqueue();
void penqueue (heap* q, void* data, int priority);
void pqmove (heap* q, void* data, int priority);
void* pdequeue (heap* q);
