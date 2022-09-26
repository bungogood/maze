#include "color.h"

/**
 * draw gradient
 */

// count nodes and cells
// calculate gradient
// draw gradient

void draw_path(maze* m, graph* g) {
  vertex* cur = g->end;
  while (cur != NULL) {
    m->image[cur->r][cur->c*3]   = 0xff;
    m->image[cur->r][cur->c*3+1] = 0x00;
    m->image[cur->r][cur->c*3+2] = 0x00;
    cur = cur->prev;
  }
}

void color_vertices(maze* m) {
  int count;
  for (int r = 1; r < m->height-1; r++) {
    for (int c = 1; c < m->width-1; c++) {
      // count neighbours
      if (m->image[r][c*3] && (m->image[r+1][3*c] != m->image[r-1][3*c] || m->image[r][3*(c+1)] != m->image[r][3*(c-1)] || (m->image[r+1][3*c] && m->image[r-1][3*c] && m->image[r][3*(c+1)] && m->image[r][3*(c-1)]))) {
        m->image[r][c*3]   = 0xff;
        m->image[r][c*3+1] = 0x00;
        m->image[r][c*3+2] = 0x00;
      }
    }
  }
}

void color_decisions(maze* m) {
  int count;
  for (int r = 1; r < m->height-1; r++) {
    for (int c = 1; c < m->width-1; c++) {
      // count neighbours
      if (m->image[r][c*3]) {
        count = 0;
        if (m->image[r][(c+1)*3]) count++;
        if (m->image[r][(c-1)*3]) count++;
        if (m->image[r+1][c*3])   count++;
        if (m->image[r-1][c*3])   count++;
        if (count == 1 || count == 3 || count == 4) {
          m->image[r][c*3]   = 0xff;
          m->image[r][c*3+1] = 0x00;
          m->image[r][c*3+2] = 0x00;
        }
      }
    }
  }
}
