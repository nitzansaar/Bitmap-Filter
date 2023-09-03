#include "helpers.h"

void setNewValues(int height, int width, RGBTRIPLE image[height][width], int newValue);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // go through each pixel in the image
    // calculate the average for that pixel (int)(R + G + B) / 3
    // set the new value for that pixel to the average
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
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Set new values
void setNewValues(int height, int width, RGBTRIPLE image[height][width], int newValue)
{
    image[height][width].rgbtBlue = newValue;
    image[height][width].rgbtGreen = newValue;
    image[height][width].rgbtRed = newValue;
}