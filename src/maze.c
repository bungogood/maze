#include "maze.h"

maze* create_maze_gray(int width, int height) {
  maze* m = malloc(sizeof(maze));
  m->width = width;
  m->height = height;
  m->bit_depth = 8;
  m->color_type = PNG_COLOR_TYPE_GRAY;
  m->image = malloc(height * sizeof(png_byte*));
  for (int r = 0; r < height; r++) m->image[r] = malloc(width * sizeof(png_byte));
  return m;
}

maze* create_maze_rgb(int width, int height) {
  maze* m = malloc(sizeof(maze));
  m->width = width;
  m->height = height;
  m->bit_depth = 8;
  m->color_type = PNG_COLOR_TYPE_RGB;
  m->image = malloc(height * sizeof(png_byte*));
  for (int r = 0; r < height; r++) m->image[r] = malloc(3 * width * sizeof(png_byte));
  return m;
}

maze* maze_to_rgb(maze* g) {
  maze* m = create_maze_rgb(g->width, g->height);
  for (int r = 0; r < g->height; r++) {
    for (int c = 0; c < g->width; c++) {
      m->image[r][3*c]   = g->image[r][c];
      m->image[r][3*c+1] = g->image[r][c];
      m->image[r][3*c+2] = g->image[r][c];
    }
  }
  return m;
}

maze* maze_to_gray(maze* m) {
  maze* g = create_maze_gray(m->width, m->height);
  for (int r = 0; r < m->height; r++) {
    for (int c = 0; c < m->width; c++) {
      g->image[r][c] = m->image[r][3*c];
    }
  }
  return g;
}

maze* read_png(const char* filename) {
  FILE *fp = fopen(filename, "rb");

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) abort();

  png_infop info = png_create_info_struct(png);
  if(!info) abort();

  if(setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  png_read_info(png, info);

  int width      = png_get_image_width(png, info);
  int height     = png_get_image_height(png, info);
  int color_type = png_get_color_type(png, info);
  int bit_depth  = png_get_bit_depth(png, info);

  if(bit_depth == 16)
    png_set_strip_16(png);
  
  if(color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);

  if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);
  
  
  if(color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);
  
  // somehow get rid of alpha chanel
  
  // These color_type don't have an alpha channel then fill it with 0xff.
  // if(color_type == PNG_COLOR_TYPE_RGB ||
  //    color_type == PNG_COLOR_TYPE_GRAY ||
  //    color_type == PNG_COLOR_TYPE_PALETTE)
  //   png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
  /*
  maze* m;
  if (color_type == PNG_COLOR_TYPE_GRAY) {
    m = create_maze_gray(width, height);
  } else if (color_type == PNG_COLOR_TYPE_RGB) {
    m = create_maze_rgb(width, height);
  } else {
    abort();
  }
  */
  maze* m = create_maze_rgb(width, height);
  
  png_read_update_info(png, info);

  png_read_image(png, m->image);

  fclose(fp);
  
  png_destroy_read_struct(&png, &info, NULL);

  return m;
}

void write_png(const char* filename, maze* m) {
  FILE *fp = fopen(filename, "wb");
  if(!fp) abort();

  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) abort();

  png_infop info = png_create_info_struct(png);
  if (!info) abort();

  if (setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  png_set_IHDR(
    png,
    info,
    m->width, m->height,
    m->bit_depth,
    m->color_type,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_BASE,
    PNG_FILTER_TYPE_BASE
  );

  png_write_info(png, info);

  png_write_image(png, m->image);

  png_write_end(png, NULL);
  
  fclose(fp);
  png_destroy_write_struct(&png, &info);
}
