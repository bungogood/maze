#include "solve.h"
#include "options.h"

bool dfs(graph* g) {
  stack* q = createStack();
  vertex* v;

  spush(q, g->start);
  g->start->seen = true;

  int nodes = 0;
  while (q->head != NULL) {
    v = spop(q);
    nodes++;
    
    if (v == g->end) {
      if (!quite) printf("searched: %d\n", nodes);
      return true;
    }
    
    for (int i = 0; i < 4; i++) {
      if (v->edges[i] != NULL && !v->edges[i]->seen) {
        v->edges[i]->seen = true;
        v->edges[i]->prev = v;
        spush(q, v->edges[i]);
      }
    }
  }

  return false;
}

bool bfs(graph* g) {
  queue* q = createQueue();
  vertex* v;

  enqueue(q, g->start);
  g->start->seen = true;

  int nodes = 0;
  while (q->head != NULL) {
    v = dequeue(q);
    nodes++;
    
    if (v == g->end) {
      if (!quite) printf("searched: %d\n", nodes);
      return true;
    }
    
    for (int i = 0; i < 4; i++) {
      if (v->edges[i] != NULL && !v->edges[i]->seen) {
        v->edges[i]->seen = true;
        v->edges[i]->prev = v;
        enqueue(q, v->edges[i]);
      }
    }
  }

  return false;
}
