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

maze* gen_prim(int width, int height) {
  long pw = 2*width+1;
  long ph = 2*height+1;
  
  earray* frontier = createEarray();

  maze* m = create_maze_gray(pw, ph);

  for (int c = 0; c < pw; c++) {
    m->image[0][c] = BLACK;
  }
  m->image[0][1]    = WHITE;
  m->image[1][1]    = WHITE;

  eadd(frontier, (void*)     pw+3);
  eadd(frontier, (void*) (2*pw+1));

  while (frontier->length > 0) {
    printf("frontier: %d\n", frontier->length);
    // choose random
    int ri = rand() % frontier->length;
    long loc = (long) eget(frontier, ri);
    long tmp = (long) eget(frontier, frontier->length-1);
    eset(frontier, ri, (void*) tmp);
    epop(frontier);
    
    printf("okay\n");
    // go though random
    int randn = 1 + rand() % 4;
    int r = loc / pw;
    int c = loc % pw;
    int rn[4];
    int cn[4];
    
    if (r > 1) {
      rn[0] = r - 2;
      cn[0] = c;
    } else rn[0] = INT_MIN;
    if (r < ph-2) {
      rn[1] = r + 2;
      cn[1] = c;
    } else rn[1] = INT_MIN;
    if (c > 1) {
      rn[2] = r;
      cn[2] = c - 2;
    } else rn[2] = INT_MIN;
    if (c < pw-2) {
      rn[3] = r;
      cn[3] = c + 2;
    } else rn[3] = INT_MIN;
    int i;
    for (i = 0; randn > 0; i++) {
      if (rn[i%4] != INT_MIN && m->image[rn[i%4]][cn[i%4]]) {
        randn--;
        printf("%d %d\n", rn[i%4], i--);
      }
    }
    printf("%d %d\n", rn[i%4], i);
    
    m->image[r][c] = WHITE;
    printf("%d %d %d\n",r,rn[i%4],c);
    r = (r + rn[i%4]) / 2;
    c = (c + cn[i%4]) / 2;
    printf("shit %d %d\n",r,c);
    m->image[r][c] = WHITE;
    printf("shit\n");
    
    for (i = 0; i < 4; i++) {
      if (rn[i] != INT_MIN && !m->image[rn[i]][cn[i]]) {
        eadd(frontier, (void*) (rn[i]*pw+cn[i]));
      }
    }
  }

  for (int c = 0; c < pw; c++) {
    m->image[ph-1][c] = BLACK;
  }
  m->image[ph-1][pw-2] = WHITE;
  
  return m;
}