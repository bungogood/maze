#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <png.h>

#define BLACK 0x00
#define WHITE 0xff

typedef struct {
  int width;
  int height;
  int bit_depth;
  int color_type;
  png_byte** image;
} maze;

maze* create_maze_gray(int width, int height);
maze* create_maze_rgb(int width, int height);

void print_maze (maze* m);
bool isPath(maze* m , int r, int c);

maze* maze_to_rgb(maze* g);
maze* maze_to_gray(maze* m);

maze* read_png(const char* filename);
maze* read_maze(const char* filename);
void write_png(const char* filename, maze* m);
