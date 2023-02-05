#include "Image.h"

void ImageCreate(struct Image *img, int w, int h, int c)
{
    size_t size = w * h * c;
    img->data = calloc(size, 1);
    assert(img->data != NULL);
    img->width = w;
    img->height = h;
    img->channels = c;
    img->size = size;
}

void ImageSave(const struct Image *img, const char *filename)
{
    stbi_write_png(filename, img->width, img->height, img->channels, img->data, img->width * img->channels);
}

void ImageFree(struct Image *img)
{
    free(img->data);
}

void ImagePixel(struct Image *img, int x, int y, int color)
{
    for (int i = 0; i < img->channels; i++, color >>= 8)
    {
        img->data[img->channels * (y * img->width + x) + (img->channels - 1 - i)] = color & 0xFF;
    }
}
