#include "generate.h"

maze* bin_tree_maze(int width, int height) {
  int pw = 2*width+1;
  int ph = 2*height+1;

  maze* m = create_maze_gray(pw, ph);

  for (int c = 0; c < pw; c++) {
    m->image[0][c] = BLACK;
    m->image[1][c] = WHITE;
  }
  m->image[0][1]    = WHITE;
  m->image[1][0]    = BLACK;
  m->image[1][pw-1] = BLACK;

  for (int r = 2; r < 2*height; r+=2) {
    m->image[r][0]   = BLACK;
    m->image[r][1]   = WHITE;
    m->image[r+1][0] = BLACK;
    m->image[r+1][1] = WHITE;
    
    for (int c = 2; c < 2*width; c+=2) {
      if (rand() & 1) {
        m->image[r][c]     = BLACK;
        m->image[r][c+1]   = WHITE;
        m->image[r+1][c]   = BLACK;
        m->image[r+1][c+1] = WHITE;
      } else {
        
        m->image[r][c]     = BLACK;
        m->image[r][c+1]   = BLACK;
        m->image[r+1][c]   = WHITE;
        m->image[r+1][c+1] = WHITE;
      }
    }
    
    m->image[r][pw-1]   = BLACK;
    m->image[r+1][pw-1] = BLACK;
  }

  for (int c = 0; c < pw; c++) {
    m->image[ph-1][c] = BLACK;
  }
  m->image[ph-1][pw-2] = WHITE;
  
  return m;
}
