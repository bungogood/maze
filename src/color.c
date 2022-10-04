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
  for (int r = 1; r < m->height-1; r++) {
    for (int c = 1; c < m->width-1; c++) {
      // count neighbours
      if (isPath(m, r, c)) {
        int count = 0;
        if (isPath(m, r, c+1)) count++;
        if (isPath(m, r, c-1)) count++;
        if (isPath(m, r+1, c)) count++;
        if (isPath(m, r-1, c)) count++;        
        if (count == 1) {
          m->image[r][c*3]   = 0xff;
          m->image[r][c*3+1] = 0x00;
          m->image[r][c*3+2] = 0x00;
        } else if (count == 2 && isPath(m, r, c+1) != isPath(m, r, c-1)) {
          m->image[r][c*3]   = 0xff;
          m->image[r][c*3+1] = 0x00;
          m->image[r][c*3+2] = 0xff;
        } else if (count == 3) {
          m->image[r][c*3]   = 0x00;
          m->image[r][c*3+1] = 0x00;
          m->image[r][c*3+2] = 0xff;
        } else if (count == 4) {
          m->image[r][c*3]   = 0x00;
          m->image[r][c*3+1] = 0xff;
          m->image[r][c*3+2] = 0x00;
        }
      }
    }
  }
}

void color_decisions(maze* m) {
  for (int r = 1; r < m->height-1; r++) {
    for (int c = 1; c < m->width-1; c++) {
      // count neighbours
      if (isPath(m, r, c)) {
        int count = 0;
        if (isPath(m, r, c+1)) count++;
        if (isPath(m, r, c-1)) count++;
        if (isPath(m, r+1, c)) count++;
        if (isPath(m, r-1, c)) count++;        
        if (count == 1) {
          m->image[r][c*3]   = 0xff;
          m->image[r][c*3+1] = 0x00;
          m->image[r][c*3+2] = 0x00;
        } else if (count == 3) {
          m->image[r][c*3]   = 0x00;
          m->image[r][c*3+1] = 0x00;
          m->image[r][c*3+2] = 0xff;
        } else if (count == 4) {
          m->image[r][c*3]   = 0x00;
          m->image[r][c*3+1] = 0xff;
          m->image[r][c*3+2] = 0x00;
        }
      }
    }
  }
}
