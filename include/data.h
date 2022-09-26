#pragma once

#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

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
