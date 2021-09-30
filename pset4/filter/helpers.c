#include "helpers.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // printf("%i\n", image[h][w].rgbtBlue);
            int average = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);
            // printf("%i\n", average);
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int sepiaRed = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            int sepiaGreen = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            int sepiaBlue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);
            // printf("%i\n", sepiaRed);
            // printf("%i\n", image[h][w].rgbtRed);
            image[h][w].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
            image[h][w].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[h][w].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            RGBTRIPLE buffer = image[h][w];
            image[h][w] = image[h][width - 1 - w];
            image[h][width - 1 - w] = buffer;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE buffer[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            buffer[h][w] = image[h][w];
        }
    }


    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float totalPixels = 0.0;
            int blueTotal = 0;
            int greenTotal = 0;
            int redTotal = 0;
            // Step 1.
            // Starting from the left top corner of the pixel we are checking via loops "vertical index/horizontal index relative to current pixel".
            // We have to calculate the position of the pixels around our pixel.
            // -1/-1 | -1/0 | -1/1
            //  0/-1 |   P  |  0/1
            //  1/-1 |  1/0 |  1/1
            // The smallest index will be -1 for horizontal and vertical blocks and the highest index 1. I will need one normal loop and one nested loop
            // which will start at -1(row)/-1(column) and the normal loop should loop throught either rows or columns first and the nested one should loop throught the opposite axis.
            // Like this I should cover all the pixels around.
            // Step 2.
            // If, after the calculation, we will get index of the pixel less than zero(row or column), it will mean that
            // the index is outside the box, therefore not valid.
            // If it's not valid, I will continue iteration.
            // Step 3.
            // If it's valid I will add it to the total for each color and add 1 to the counter so I know how many pixels are around and can calculate average.

            // starting index for vertical check set to -1. It will loop 3 times from the top to the bottom.
            for (int vertical = -1; vertical < 2; vertical++)
            {
                // starting index for horizontal check set to -1. It will loop 3 times from left(corner) to right(corner).
                for (int horizontal = -1; horizontal < 2; horizontal++)
                {

                    if (h + vertical < 0 || h + vertical >= height || w + horizontal < 0 || w + horizontal >= width)
                    {
                        continue;
                    }

                    totalPixels++;
                    blueTotal += buffer[h + vertical][w + horizontal].rgbtBlue;
                    greenTotal += buffer[h + vertical][w + horizontal].rgbtGreen;
                    redTotal += buffer[h + vertical][w + horizontal].rgbtRed;
                    // printf("%i\n", blueTotal);
                    // printf("%i\n", greenTotal);
                    // printf("%i\n", redTotal);
                }
            }

            image[h][w].rgbtBlue = round(blueTotal / totalPixels);
            image[h][w].rgbtGreen = round(greenTotal / totalPixels);
            image[h][w].rgbtRed = round(redTotal / totalPixels);
        }
    }
}
