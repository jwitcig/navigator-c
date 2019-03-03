typedef struct pixelstruct {
  int r, g, b, a, index;
} Pixel;

typedef struct imagestruct {
    int width, height;
    Pixel **pixels;
} Image;

Image* read_png_file(char *filename);