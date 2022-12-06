#include <stdio.h>
#include <stdlib.h>
#include "Struct/image.h"
#include "Struct/pixel.h"

void write_sudoku_image(char filename[], unsigned char grid[9][9], unsigned char initial[9][9])
{
	// Import Texte for Number
	Image** list_image = malloc(sizeof(struct Image*)*10);
	for(int i = 0; i < 10; i++)
	{
		char* s = malloc(sizeof(char)* 50);
		sprintf(s, "assets/Template/%d.png",i);
		list_image[i] = importImage(s);
	}

	Image* image = createEmptyImage(700,700);
	// Draw the number
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			for(int x = 0; x < 68; x++)
			{
				for(int y = 0; y < 68; y++)
				{
					if (initial[i][j] != grid[i][j])
					{
						image->pixels[(j*70+35)+x][(i*70+35)+y] = list_image[grid[i][j]]->pixels[x][y];
						image->pixels[(j*70+35)+x][(i*70+35)+y].red = 255;
					}
					else 
						image->pixels[(j*70+35)+x][(i*70+35)+y] = list_image[grid[i][j]]->pixels[x][y];
				}
			}
		}
	}

	// Draw the line 
	for(int i = 35; i < image->width; i+=70)
	{
		for(int z = (i % 210 == 35 ? -2 : -1); z < (i % 210 == 35 ? 3 : 2); z++)
		{
			for(int j = 35; j < image->height-35; j++)
			{
				image->pixels[i+z][j].red = 0;
				image->pixels[i+z][j].blue = 0;
				image->pixels[i+z][j].green = 0;
				image->pixels[j][i+z].red = 0;
				image->pixels[j][i+z].blue = 0;
				image->pixels[j][i+z].green = 0;
			}
		}
	}
	saveImage(image, filename);
	free(image);
	free(list_image);
}