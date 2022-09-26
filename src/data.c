#include "data.h"

/**
 * Vertex
 */
vertex* createVertex (int r, int c) {
  vertex* v = malloc(sizeof (vertex));
  v->r = r;
  v->c = c;
  for (int i=0; i<4; i++) v->edges[i] = NULL;
  v->prev = NULL;
  v->dist = INT_MAX;
  v->seen = false;
  return v;
}

int distance (vertex* a, vertex* b) {
  return abs((a->r - b->r) + (a->c - b->c));
}

/**
 * Graph
 */
graph* createGraph (vertex* start, vertex* end) {
  graph* g = malloc(sizeof (graph));
  g->start = start;
  g->end = end;
  return g;
}

/**
 * queue
 * 
 * enque
 * deque
 */
queue* createQueue() {
  queue* q = malloc(sizeof(queue));
  q->head = NULL;
  q->tail = NULL;
  q->size = 0;
}

void enqueue (queue* q, void* data) {
  queueItem* n = malloc(sizeof(queueItem));
  n->next = NULL;
  n->prev = q->tail;
  if (n->prev != NULL) n->prev->next = n;
  n->data = data;
  q->tail = n;
  if (q->head == NULL) q->head = n;
  q->size++;
}

void* dequeue(queue* q) {
  if (q->head == NULL) return NULL;
  queueItem* h = q->head;
  void* data = h->data;
  q->head = q->head->next;
  q->size--;
  if (q->tail == h) q->tail == NULL; // last elem
  else q->head->prev = NULL;
  free(h);
  return data;
}

/**
 * stack
 * 
 * push
 * pop
 */
stack* createStack() {
  stack* q = malloc(sizeof(stack));
  q->head = NULL;
  q->size = 0;
}

void spush(stack* s, void* data) {
  stackItem* n = malloc(sizeof(stackItem));
  n->next = s->head;
  n->data = data;
  s->head = n;
  s->size++;
}

void* spop(stack* s) {
  if (s->head == NULL) return NULL;
  stackItem* h = s->head;
  void* data = h->data;
  s->head = s->head->next;
  s->size--;
  free(h);
  return data;
}

// pqueue (heap)

// vertex
// graph
