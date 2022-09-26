#include "data.h"
#include "maze.h"

void print_maze (maze* m) {
  for (int r = 0; r < m->height; r++) {
    for (int c = 0; c < m->width; c++) {
      if (m->image[r][3*c]) printf("██");
      else printf("  ");
    }
    printf("\n");
  }
}

graph* parse (maze* m) {
  int r, c;
  int count = 0;
  vertex* start = NULL;
  vertex* end = NULL;
  vertex* prev;
  vertex* cur;
  vertex* prevline[m->width];

  for (c = 1; c < m->width-1; c++) {
    if (m->image[0][3*c]) {
      start = createVertex(0, c);
      count++;
      prevline[c] = start;
    } else {
      prevline[c] = NULL;
    }
  }

  for (r = 1; r < m->height-1; r++) {
    prev = NULL;
    for (c = 1; c < m->width-1; c++) {
      if (m->image[r][3*c]) {
        if (m->image[r+1][3*c] != m->image[r-1][3*c] || m->image[r][3*(c+1)] != m->image[r][3*(c-1)] || (m->image[r+1][3*c] && m->image[r-1][3*c] && m->image[r][3*(c+1)] && m->image[r][3*(c-1)])) {
          cur = createVertex(r, c);
          count++;
          if (prev != NULL) {
            cur->edges[3] = prev;
            prev->edges[1] = cur;
          }
          if (prevline[c] != NULL) {
            cur->edges[2] = prevline[c];
            prevline[c]->edges[0] = cur;
          }
          prev = cur;
          prevline[c] = cur;
        }
      } else {
        prev = NULL;
        prevline[c] = NULL;
      }
    }
  }

  for (c = 1; c < m->width-1; c++) {
    if (m->image[m->height-1][3*c]) {
      end = createVertex(m->height-1, c);
      count++;
      end->edges[2] = prevline[c];
      prevline[c]->edges[0] = end;
      break;
    }
  }
  // if not -q
  printf("vertex count: %d\n", count);
  return createGraph(start, end);
}
