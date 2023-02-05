#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stdio.h>
#include <time.h>

#include "Image.h"

#define WIDTH 800
#define HEIGHT 800

#define MAX_VELOCITY_COMPONENT 3

#define PADDING 10

#define NUM_BALLS 100

#define NUM_FRAMES 250

struct Ball
{
    int x, y;
    int dx, dy;
    int color;
};

void initialize_random_balls(struct Ball *balls)
{
    for (int i = 0; i < NUM_BALLS; i++)
    {
        balls[i].x = (rand() % (WIDTH - PADDING * 2)) + PADDING;
        balls[i].y = (rand() % (HEIGHT - PADDING * 2)) + PADDING;
        balls[i].dx = (rand() % (MAX_VELOCITY_COMPONENT * 2)) - MAX_VELOCITY_COMPONENT;
        balls[i].dy = (rand() % (MAX_VELOCITY_COMPONENT * 2)) - MAX_VELOCITY_COMPONENT;
        balls[i].color = rand() & 0xFFFFFF;
    }
}

int dist_sq(int x1, int y1, int x2, int y2)
{
    return ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2));
}

void produce_voronoi(struct Image *img, struct Ball *balls)
{
    for (int x = 0; x < img->width; x++)
    {
        for (int y = 0; y < img->height; y++)
        {
            struct Ball *closest_ball = NULL;
            int closest_ball_dist_sq = -1;
            for (int i = 0; i < NUM_BALLS; i++)
            {
                int current_dist_sq = dist_sq(balls[i].x, balls[i].y, x, y);
                if (closest_ball == NULL || current_dist_sq < closest_ball_dist_sq)
                {
                    closest_ball = &balls[i];
                    closest_ball_dist_sq = current_dist_sq;
                }
            }
            ImagePixel(img, x, y, closest_ball->color);
        }
    }
}

void bounce_balls(struct Ball *balls)
{
    for (int i = 0; i < NUM_BALLS; i++)
    {
        struct Ball *b = &balls[i];
        b->x += b->dx;
        b->y += b->dy;
        if (b->x < 0)
        {
            b->x = 0;
            b->dx *= -1;
        }
        if (b->y < 0)
        {
            b->y = 0;
            b->dy *= -1;
        }
        if (b->x >= WIDTH)
        {
            b->x = WIDTH - 1;
            b->dx *= -1;
        }
        if (b->y >= HEIGHT)
        {
            b->y = HEIGHT - 1;
            b->dy *= -1;
        }
    }
}

int main(void)
{
    // Randomly seed based on the current time
    srand(time(0));

    // Initialize the Image struct
    struct Image img;
    ImageCreate(&img, WIDTH, HEIGHT, 3);

    // Initialize the balls
    struct Ball balls[NUM_BALLS];
    initialize_random_balls(balls);

    for (int i = 0; i < NUM_FRAMES; i++)
    {
        // Produce the voronoi diagram for the current balls
        produce_voronoi(&img, balls);
        char filename[21];
        sprintf(filename, "frames/frame%03d.png", i);
        printf("Saving File: %s\n", filename);
        ImageSave(&img, filename);
        bounce_balls(balls);
    }

    ImageFree(&img);
}