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

void ImageRect(struct Image *img, int x, int y, int w, int h, int color)
{
    for (int x_ = x; x_ < x + w; x_++)
    {
        for (int y_ = y; y_ < y + h; y_++)
        {
            for (int i = 0, c = color; i < img->channels; i++, c >>= 8)
            {
                img->data[img->channels * (y_ * img->width + x_) + (img->channels - 1 - i)] = c & 0xFF;
            }
        }
    }
}

void ImageSquare(struct Image *img, int x, int y, int s, int color)
{
    ImageRect(img, x, y, s, s, color);
}

void ImagePixel(struct Image *img, int x, int y, int color)
{
    for (int i = 0; i < img->channels; i++, color >>= 8)
    {
        img->data[img->channels * (y * img->width + x) + (img->channels - 1 - i)] = color & 0xFF;
    }
}
