#include <stdlib.h>
#include <string.h>
#include "generate.h"
#include "solve.h"
#include "maze.h"
#include "parse.h"
#include "color.h"
#include "data.h"

void generate(int argc, char **argv) {
  // optional seed
  char* filename = argv[0];
  int width = atoi(argv[1]);
  int height = argc == 3 ? atoi(argv[2]) : width;
  printf("generator %d %d\n", width, height);
  maze* m = bin_tree_maze(width, height);
  write_png(filename, m);
}

void solve(int argc, char **argv) {
  char* filename = argv[0];
  printf("loading\n");
  maze* m = read_png(filename);
  printf("parsing\n");
  graph* g = parse(m);
  printf("solving\n");
  if (dfs(g)) {
    printf("drawing\n");
    draw_path(m, g);
    printf("saving\n");
    write_png(filename, m);
  }
}

void show(int argc, char **argv) {
  char* filename = argv[0];
  printf("printing\n");
  maze* m = read_png(filename);
  print_maze(m);
}

void color(int argc, char **argv) {
  char* infile = argv[0];
  char* outfile = argv[1];
  printf("color\n");
  maze* m = read_png(infile);
  // color_decisions(m);
  color_vertices(m);
  write_png(outfile, m);
}

/*
-v --verbose
-q --quite

solve file [options]
-a --algorithm <algorithm>
- a* a-star
- dj dijkstra
- df depth-first
- bf breadth-first

-g --gradient

-o --output <file>

gen file width [height] [options]
-a --algorithm <algorithm>
- bn binary-tree
- pm prim
- kr kruskal

-s --seed <seed>
 */
int quite;

int main(int argc, char** argv) {
  quite = 0;
  if (argc < 3) abort(); // must have command and file

  char* command = argv[1];
  if (!strcmp(command,"solve")) {
    solve(argc-2, argv+2);
  } else if (!strcmp(command,"gen")) {
    generate(argc-2, argv+2);
  } else if (!strcmp(command,"show")) {
    show(argc-2, argv+2);
  } else if (!strcmp(command,"color")) {
    color(argc-2, argv+2);
  }
}
