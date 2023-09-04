#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = (int)(image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int left = 0;
        int right = width - 1;
        while (left < right)
        {
            RGBTRIPLE temp = image[i][left];
            image[i][left] = image[i][right];
            image[i][right] = temp;
            left++;
            right--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int count = 0;

            // Iterate over neighboring pixels within a 3x3 grid
            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    int newRow = i + row;
                    int newCol = j + col;

                    // Check if the neighboring pixel is within bounds
                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        totalRed += image[newRow][newCol].rgbtRed;
                        totalGreen += image[newRow][newCol].rgbtGreen;
                        totalBlue += image[newRow][newCol].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average color values and round
            copy[i][j].rgbtRed = round((float)totalRed / count);
            copy[i][j].rgbtGreen = round((float)totalGreen / count);
            copy[i][j].rgbtBlue = round((float)totalBlue / count);
        }
    }

    // Copy the blurred image back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Define the Sobel operators for edge detection
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Gx_red = 0, Gx_green = 0, Gx_blue = 0;
            int Gy_red = 0, Gy_green = 0, Gy_blue = 0;

            // Apply Sobel operator to calculate Gx and Gy values
            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    int newRow = i + row;
                    int newCol = j + col;

                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        Gx_red += Gx[row + 1][col + 1] * image[newRow][newCol].rgbtRed;
                        Gx_green += Gx[row + 1][col + 1] * image[newRow][newCol].rgbtGreen;
                        Gx_blue += Gx[row + 1][col + 1] * image[newRow][newCol].rgbtBlue;

                        Gy_red += Gy[row + 1][col + 1] * image[newRow][newCol].rgbtRed;
                        Gy_green += Gy[row + 1][col + 1] * image[newRow][newCol].rgbtGreen;
                        Gy_blue += Gy[row + 1][col + 1] * image[newRow][newCol].rgbtBlue;
                    }
                }
            }

            // Calculate edge strength using magnitude of Gx and Gy
            int red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));

            // Cap the color values at 255
            copy[i][j].rgbtRed = (red > 255) ? 255 : red;
            copy[i][j].rgbtGreen = (green > 255) ? 255 : green;
            copy[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
        }
    }

    // Copy the edge-detected image back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}