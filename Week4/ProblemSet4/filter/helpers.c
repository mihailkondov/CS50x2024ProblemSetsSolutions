#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double blue = image[i][j].rgbtBlue;
            double green = image[i][j].rgbtGreen;
            double red = image[i][j].rgbtRed;
            double average = (blue + green + red) / 3;
            int result = round(average);
            image[i][j].rgbtBlue = result;
            image[i][j].rgbtGreen = result;
            image[i][j].rgbtRed = result;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            double originalBlue = image[i][j].rgbtBlue;
            double originalGreen = image[i][j].rgbtGreen;
            double originalRed = image[i][j].rgbtRed;
            double sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            double sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            double sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            int resultR = round(sepiaRed);
            int resultG = round(sepiaGreen);
            int resultB = round(sepiaBlue);

            if (resultR > 255)
            {
                resultR = 255;
            }

            if (resultG > 255)
            {
                resultG = 255;
            }

            if (resultB > 255)
            {
                resultB = 255;
            }

            // Update pixel with sepia values
            image[i][j].rgbtBlue = resultB;
            image[i][j].rgbtGreen = resultG;
            image[i][j].rgbtRed = resultR;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][width - j - 1];
        }
    }
    free(copy);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // set default value for out of bound edges so they don't change the average
    RGBTRIPLE black;
    black.rgbtBlue = 0;
    black.rgbtGreen = 0;
    black.rgbtRed = 0;
    RGBTRIPLE box[9];

    // Take relevant pixels (inbound edges)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // set default values for pixels out of bounds
            // such that they do not affect the average
            for (int k = 0; k < 9; k++)
            {
                box[k] = black;
            }

            // Calculate average (blur)
            double count = 0; // number of inbound edges used to calculate average
            double red = 0;
            double blue = 0;
            double green = 0;

            // taking into account only pixel positions inside the image
            if (i != 0 && j != 0) // top left
            {
                box[0] = copy[i - 1][j - 1];
                count++;
            }

            if (i != 0) // top center
            {
                box[1] = copy[i - 1][j];
                count++;
            }

            if (i != 0 && j != width - 1) // top right
            {
                box[2] = copy[i - 1][j + 1];
                count++;
            }

            if (j != 0) // middle left
            {
                box[3] = copy[i][j - 1];
                count++;
            }

            // middle center
            box[4] = copy[i][j];
            count++;

            if (j != width - 1) // middle right
            {
                box[5] = copy[i][j + 1];
                count++;
            }

            if (i != height - 1 && j != 0) // bottom left
            {
                box[6] = copy[i + 1][j - 1];
                count++;
            }

            if (i != height - 1) // bottom center
            {
                box[7] = copy[i + 1][j];
                count++;
            }

            if (i != height - 1 && j != width - 1) // bottom right
            {
                box[8] = copy[i + 1][j + 1];
                count++;
            }

            // add values
            for (int k = 0; k < 9; k++)
            {
                blue += (double) box[k].rgbtBlue;
                green += (double) box[k].rgbtGreen;
                red += (double) box[k].rgbtRed;
            }

            // take average
            blue = blue / count;
            green = green / count;
            red = red / count;

            int blue_r = round(blue);
            int green_r = round(green);
            int red_r = round(red);

            if (blue_r > 255)
            {
                blue_r = 255;
            }
            if (green_r > 255)
            {
                green_r = 255;
            }
            if (red_r > 255)
            {
                red_r = 255;
            }

            BYTE blue_b = (BYTE) blue_r;
            BYTE green_b = (BYTE) green_r;
            BYTE red_b = (BYTE) red_r;

            // alter image
            image[i][j].rgbtBlue = blue_b;
            image[i][j].rgbtGreen = green_b;
            image[i][j].rgbtRed = red_b;
        }
    }
    return;
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // set default value for out of bound edges so they don't change the average
    RGBTRIPLE black;
    black.rgbtBlue = 0;
    black.rgbtGreen = 0;
    black.rgbtRed = 0;
    RGBTRIPLE box[9];

    // Take relevant pixels (inbound edges)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // set default values for pixels out of bounds to black
            for (int k = 0; k < 9; k++)
            {
                box[k] = black;
            }

            // pixels inside are assigned real values
            // pixels outside stay unchaged (black)
            if (i != 0 && j != 0) // top left
            {
                box[0] = copy[i - 1][j - 1];
            }

            if (i != 0) // top center
            {
                box[1] = copy[i - 1][j];
            }

            if (i != 0 && j != width - 1) // top right
            {
                box[2] = copy[i - 1][j + 1];
            }

            if (j != 0) // middle left
            {
                box[3] = copy[i][j - 1];
            }

            // middle center
            box[4] = copy[i][j];

            if (j != width - 1) // middle right
            {
                box[5] = copy[i][j + 1];
            }

            if (i != height - 1 && j != 0) // bottom left
            {
                box[6] = copy[i + 1][j - 1];
            }

            if (i != height - 1) // bottom center
            {
                box[7] = copy[i + 1][j];
            }

            if (i != height - 1 && j != width - 1) // bottom right
            {
                box[8] = copy[i + 1][j + 1];
            }

            // calculate Gx
            double gx_b = box[0].rgbtBlue - box[2].rgbtBlue + 2 * box[3].rgbtBlue -
                          2 * box[5].rgbtBlue + box[6].rgbtBlue - box[8].rgbtBlue;
            double gx_g = box[0].rgbtGreen - box[2].rgbtGreen + 2 * box[3].rgbtGreen -
                          2 * box[5].rgbtGreen + box[6].rgbtGreen - box[8].rgbtGreen;
            double gx_r = box[0].rgbtRed - box[2].rgbtRed + 2 * box[3].rgbtRed -
                          2 * box[5].rgbtRed + box[6].rgbtRed - box[8].rgbtRed;
            // calculate Gy
            double gy_b = box[0].rgbtBlue + 2 * box[1].rgbtBlue + box[2].rgbtBlue -
                          box[6].rgbtBlue - 2 * box[7].rgbtBlue - box[8].rgbtBlue;
            double gy_g = box[0].rgbtGreen + 2 * box[1].rgbtGreen + box[2].rgbtGreen -
                          box[6].rgbtGreen - 2 * box[7].rgbtGreen - box[8].rgbtGreen;
            double gy_r = box[0].rgbtRed + 2 * box[1].rgbtRed + box[2].rgbtRed - box[6].rgbtRed -
                          2 * box[7].rgbtRed - box[8].rgbtRed;

            // calculate Sobel values
            double blue = sqrt(pow(gx_b, 2) + pow(gy_b, 2));
            double green = sqrt(pow(gx_g, 2) + pow(gy_g, 2));
            double red = sqrt(pow(gx_r, 2) + pow(gy_r, 2));

            // round and convert rgb values
            int blue_r = round(blue);
            int green_r = round(green);
            int red_r = round(red);

            if (blue_r > 255)
            {
                blue_r = 255;
            }
            if (green_r > 255)
            {
                green_r = 255;
            }
            if (red_r > 255)
            {
                red_r = 255;
            }

            BYTE blue_b = (BYTE) blue_r;
            BYTE green_b = (BYTE) green_r;
            BYTE red_b = (BYTE) red_r;

            // alter image
            image[i][j].rgbtBlue = blue_b;
            image[i][j].rgbtGreen = green_b;
            image[i][j].rgbtRed = red_b;
        }
    }
    return;
}
