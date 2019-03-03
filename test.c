#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <png.h>
#include <unistd.h>

#include "image-to-pixels.h"

Image* read_png_file(char *filename);

int skipCount = 10;

int calculateLocationX(int index, int gridWidth) {
  return index % gridWidth;
}

int calculateLocationY(int index, int gridWidth) {
  return index / gridWidth;
}

int main(int argc, char** argv){
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);




    Image *image = read_png_file("../map-resources/loz.png");

    int blueCount = 0;
    for (int i=0; i<(image->width)*(image->height); i+=1) {
      Pixel pixel = *image->pixels[i];
      if (pixel.r == 185 && pixel.g == 185 && pixel.b == 185 && pixel.a == 255
          && calculateLocationX(pixel.index, image->width) % skipCount == 0 && calculateLocationY(pixel.index, image->width) % skipCount == 0)
        blueCount++;
    }

    printf("blues: %d / %d total\n", blueCount, image->width * image->height);




    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    printf("%f seconds\n", (float)delta_us / 1000 / 1000);

    return 0;
}