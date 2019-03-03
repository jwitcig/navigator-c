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

void getTime(struct timespec *time) {
    clock_gettime(CLOCK_MONOTONIC_RAW, &time);
}

uint64_t elapsedTime(struct timespec *start, struct timespec *end) {
    return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
}

int main(int argc, char** argv){
    struct timespec start, end;
    getTime(&start);

    Image *image = read_png_file("../map-resources/loz.png");

    int blueCount = 0;
    for (int i=0; i<(image->width)*(image->height); i+=1) {
      Pixel pixel = *image->pixels[i];
      if (pixel.r == 185 && pixel.g == 185 && pixel.b == 185 && pixel.a == 255
          && calculateLocationX(pixel.index, image->width) % skipCount == 0 && calculateLocationY(pixel.index, image->width) % skipCount == 0)
        blueCount++;
    }

    printf("blues: %d / %d total\n", blueCount, image->width * image->height);

    getTime(&end); 
    printf("%f seconds\n", (float)elapsedTime(&start, &end) / 1000 / 1000);
    return 0;
}