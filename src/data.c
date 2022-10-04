#include "datastructs.h"

#define EARRAY_MIN 1000

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
  return q;
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
  if (q->tail == h) q->tail = NULL; // last elem
  else q->head->prev = NULL;
  free(h);
  return data;
}

void qfree(queue* q) {
  queueItem* cur = q->head;
  queueItem* next;
  while (cur != NULL) {
    next = cur->next;
    free(cur);
    cur = next;
  }
  free(q);
}

/**
 * stack
 * 
 * push
 * pop
 */
stack* createStack() {
  stack* s = malloc(sizeof(stack));
  s->head = NULL;
  s->size = 0;
  return s;
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

void sfree(stack* s) {
  stackItem* cur = s->head;
  stackItem* next;
  while (cur != NULL) {
    next = cur->next;
    free(cur);
    cur = next;
  }
  free(s);
}

// pqueue (heap)

// vertex
// graph

earray* createEarray() {
  earray* e = malloc(sizeof(earray));
  e->maxLen = EARRAY_MIN;
  e->length = 0;
  e->array = malloc(e->maxLen * sizeof(void*));
  return e;
}

void* eget(earray* e, int index) {
  if (index > e->length) abort();
  if (index < 0) abort();
  return e->array[index];
}

void eset(earray* e, int index, void* item) {
  if (index > e->length) abort();
  if (index < 0) abort();
  e->array[index] = item;
}

void eadd(earray* e, void* item) {
  if (e->length == e->maxLen) {
    void** oarr = e->array;
    int olen = e->maxLen;
    e->maxLen *= 2;
    e->array = malloc(e->maxLen * sizeof(void*));
    memcpy(e->array, oarr, olen * sizeof(void*));
    free(oarr);
  }
  e->array[e->length++] = item;
}

void* epop(earray* e) {
  void* item = e->array[-1+e->length--];
  if (e->length < e->maxLen / 4 && e->maxLen > EARRAY_MIN) {
    void** oarr = e->array;
    int olen = e->maxLen;
    e->maxLen /= 2;
    e->array = malloc(e->maxLen * sizeof(void*));
    memcpy(e->array, oarr, olen / 4 * sizeof(void*));
    free(oarr);
  }
  return item;
}

void efree(earray* e) {
  free(e->array);
  free(e);
}
