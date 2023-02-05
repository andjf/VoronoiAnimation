#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"

#define WHITE 0xFFFFFF
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define BLACK 0x000000

struct Image
{
    int width;
    int height;
    int channels;
    size_t size;
    uint8_t *data;
};

void ImageCreate(struct Image *img, int w, int h, int c);
void ImageSave(const struct Image *img, const char *filename);
void ImageFree(struct Image *img);

void ImageRect(struct Image *img, int x, int y, int w, int h, int color);
void ImageSquare(struct Image *img, int x, int y, int s, int color);
void ImagePixel(struct Image *img, int x, int y, int color);

#endif