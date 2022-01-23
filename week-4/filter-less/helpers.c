#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

// ---

int avg_three_ints(int nmb_1, int nmb_2, int nmb_3);
int max_255(float nmb);
RGBTRIPLE sepia_pixel(RGBTRIPLE pixel);
void swap(RGBTRIPLE *a, RGBTRIPLE *b);
RGBTRIPLE blur_pixel(int n, RGBTRIPLE[]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    for each pixel (RGBTRIPLE), example:
    rgbtRed: 50, rgbtGreen: 190, rgbtBlue: 89
    avg: 110 -> make all values 110
    */
    for (int i = 0; i < height; i++)
    {
        for (int y = 0; y < width; y++)
        {
            // printf("red: %i, green: %i, blue: %i\n", image[i][y].rgbtRed, image[i][y].rgbtGreen, image[i][y].rgbtBlue);
            int avg = avg_three_ints(image[i][y].rgbtRed, image[i][y].rgbtGreen, image[i][y].rgbtBlue);
            // printf("avg: %i\n", avg);
            image[i][y].rgbtRed = avg;
            image[i][y].rgbtGreen = avg;
            image[i][y].rgbtBlue = avg;
        }
    };
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    for each pixel (RGBTRIPLE), example:
    rgbtRed: 50, rgbtGreen: 190, rgbtBlue: 90
    use some sepia algorithm on each color..
    rgbtRed: 183, rgbtGreen: 183, rgbtBlue: 127
    */
    for (int i = 0; i < height; i++)
    {
        for (int y = 0; y < width; y++)
        {
            // printf("red: %i, green: %i, blue: %i\n", image[i][y].rgbtRed, image[i][y].rgbtGreen, image[i][y].rgbtBlue);
            image[i][y] = sepia_pixel(image[i][y]);
            // printf("sepia: red: %i, green: %i, blue: %i\n", image[i][y].rgbtRed, image[i][y].rgbtGreen, image[i][y].rgbtBlue);
        }
    };
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // for each row, reverse array
    int half_width_floor = (int) floor(width / 2.0);
    // printf("width: %i, half_width_floor: %i\n", width, half_width_floor);
    for (int i = 0; i < height; i++)
    {
        for (int y = 0; y < half_width_floor; y++)
        {
            // if (i < 5 && y < 5)
            // {
            //     printf("image[%i][%i]: R: %i, G: %i, B: %i\n", i, y, image[i][y].rgbtRed, image[i][y].rgbtGreen, image[i][y].rgbtBlue);
            //     printf("image[%i][%i]: R: %i, G: %i, B: %i\n", i, width - 1 - y, image[i][width - 1 - y].rgbtRed, image[i][width - 1 - y].rgbtGreen, image[i][width - 1 - y].rgbtBlue);
            // }
            swap(&image[i][y], &image[i][width - 1 - y]);
            // if (i < 5 && y < 5)
            // {
            //     printf("after swap: R: %i, G: %i, B: %i\n\n", image[i][y].rgbtRed, image[i][y].rgbtGreen, image[i][y].rgbtBlue);
            // }
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    create a copy of the image, then:
    for each pixel:
    average the max. 8 surrounding pixels plus the pixel itself rgb values
    assign that average for rgb
    */

    // allocate memory for image copy
    RGBTRIPLE(*image_copy)[width];
    image_copy = malloc(sizeof(int[height][width])); // or malloc(sizeof(*image_copy) * height);
    
    // copy image
    for (int i = 0; i < height; i++)
    {
        for (int y = 0; y < width; y++)
        {
            image_copy[i][y] = image[i][y];
        }
    };

    // blur each pixel in original image
    for (int i = 0; i < height; i++)
    {
        for (int y = 0; y < width; y++)
        {
            RGBTRIPLE blurred_pixel;
            if (i == 0 && y == 0) // top left
            {
                RGBTRIPLE pixels[] = {image_copy[i][y], image_copy[i][y + 1], image_copy[i + 1][y], image_copy[i + 1][y + 1]};
                blurred_pixel = blur_pixel(4, pixels);
            }
            else if (i == 0 && y == width - 1) // top right
            {
                RGBTRIPLE pixels[] = {image_copy[i][y], image_copy[i][y - 1], image_copy[i + 1][y], image_copy[i + 1][y - 1]};
                blurred_pixel = blur_pixel(4, pixels);
            }
            else if (i == height - 1 && y == width - 1) // bottom right
            {
                RGBTRIPLE pixels[] = {image_copy[i][y], image_copy[i][y - 1], image_copy[i - 1][y], image_copy[i - 1][y - 1]};
                blurred_pixel = blur_pixel(4, pixels);
            }
            else if (i == height - 1 && y == 0) // bottom left
            {
                RGBTRIPLE pixels[] = {image_copy[i][y], image_copy[i][y + 1], image_copy[i - 1][y], image_copy[i - 1][y + 1]};
                blurred_pixel = blur_pixel(4, pixels);
            }
            else if (i == 0) // top row
            {
                RGBTRIPLE pixels[] = {image_copy[i][y - 1], image_copy[i + 1][y - 1], image_copy[i][y], image_copy[i][y + 1], image_copy[i + 1][y], image_copy[i + 1][y + 1]};
                blurred_pixel = blur_pixel(6, pixels);
            }
            else if (y == width - 1) // right border
            {
                RGBTRIPLE pixels[] = {image_copy[i - 1][y], image_copy[i - 1][y - 1], image_copy[i][y], image_copy[i][y - 1], image_copy[i + 1][y], image_copy[i + 1][y - 1]};
                blurred_pixel = blur_pixel(6, pixels);
            }
            else if (i == height - 1) // bottom row
            {
                RGBTRIPLE pixels[] = {image_copy[i][y], image_copy[i][y - 1], image_copy[i - 1][y], image_copy[i - 1][y - 1], image_copy[i - 1][y + 1], image_copy[i][y + 1]};
                blurred_pixel = blur_pixel(6, pixels);
            }
            else if (y == 0) // left border
            {
                RGBTRIPLE pixels[] = {image_copy[i - 1][y], image_copy[i - 1][y + 1], image_copy[i][y], image_copy[i][y + 1], image_copy[i + 1][y], image_copy[i + 1][y + 1]};
                blurred_pixel = blur_pixel(6, pixels);
            }
            else
            {
                RGBTRIPLE pixels[] = {image_copy[i - 1][y - 1], image_copy[i - 1][y], image_copy[i - 1][y + 1], image_copy[i][y - 1], image_copy[i][y], image_copy[i][y + 1], image_copy[i + 1][y - 1], image_copy[i + 1][y], image_copy[i + 1][y + 1]};
                blurred_pixel = blur_pixel(9, pixels);
            }
            image[i][y] = blurred_pixel;
        }
    };

    // free allocated memory for image copy
    free(image_copy);
}

// general helpers

int avg_three_ints(int nmb_1, int nmb_2, int nmb_3)
{
    int sum = nmb_1 + nmb_2 + nmb_3;
    float avg = sum / 3.0;
    return (int) round(avg);
}

RGBTRIPLE sepia_pixel(RGBTRIPLE pixel)
{
    RGBTRIPLE new_pixel;
    new_pixel.rgbtRed = max_255(pixel.rgbtRed * 0.393 + pixel.rgbtGreen * 0.769 + pixel.rgbtBlue * 0.189);
    new_pixel.rgbtGreen = max_255(pixel.rgbtRed * 0.349 + pixel.rgbtGreen * 0.686 + pixel.rgbtBlue * 0.168);
    new_pixel.rgbtBlue = max_255(pixel.rgbtRed * 0.272 + pixel.rgbtGreen * 0.534 + pixel.rgbtBlue * 0.131);
    return new_pixel;
}

int max_255(float nmb)
{
    return (int) fmin(255, round(nmb));
}

void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE tmp = *a;
    *a = *b;
    *b = tmp;
}

RGBTRIPLE blur_pixel(int n, RGBTRIPLE pixels[])
{
    int redSum = 0, greenSum = 0, blueSum = 0;
    for (int i = 0; i < n; i++)
    {
        redSum += pixels[i].rgbtRed;
        greenSum += pixels[i].rgbtGreen;
        blueSum += pixels[i].rgbtBlue;
    }
    RGBTRIPLE blurred_pixel;
    blurred_pixel.rgbtRed = (int) round(redSum / (float) n);
    blurred_pixel.rgbtGreen = (int) round(greenSum / (float) n);
    blurred_pixel.rgbtBlue = (int) round(blueSum / (float) n);
    return blurred_pixel;
}