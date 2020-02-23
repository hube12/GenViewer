#include "xmap.h"
#include <string.h>
#include <stdio.h>

#include <math.h>
#include <malloc.h>
#include <png.h>
#include <iostream>


// This takes the float value 'val', converts it to red, green & blue values, then
// sets those values into the image memory buffer location pointed to by 'ptr'
inline void setRGB(png_byte *ptr, float val);

// This function actually writes out the PNG image file. The string 'title' is
// also written into the image file
int writeImage(const char* filename, int width, int height, unsigned int *buffer, char* title);
/* Global biome colour table. */


void setBiomeColour(unsigned char biomeColour[256][3], int biome,
					unsigned char r, unsigned char g, unsigned char b)
{
	biomeColour[biome][0] = r;
	biomeColour[biome][1] = g;
	biomeColour[biome][2] = b;
}

void initBiomeColours(unsigned char biomeColours[256][3])
{
	// This colouring scheme is taken from the AMIDST program:
	// https://github.com/toolbox4minecraft/amidst
	// https://sourceforge.net/projects/amidst.mirror/

	memset(biomeColours, 0, 256*3);

	setBiomeColour(biomeColours, ocean, 0, 0, 112);
	setBiomeColour(biomeColours, plains,141, 179, 96);
	setBiomeColour(biomeColours, desert, 250, 148, 24);
	setBiomeColour(biomeColours, extremeHills, 96, 96, 96);
	setBiomeColour(biomeColours, forest, 5, 102, 33);
	setBiomeColour(biomeColours, taiga, 11, 102, 89);
	setBiomeColour(biomeColours, swampland, 7, 249, 178);
	setBiomeColour(biomeColours, river, 0, 0, 255);
	setBiomeColour(biomeColours, hell, 255, 0, 0);
	setBiomeColour(biomeColours, sky, 128, 128, 255);
	setBiomeColour(biomeColours, frozenOcean, 112, 112, 214);
	setBiomeColour(biomeColours, frozenRiver, 160, 160, 255);
	setBiomeColour(biomeColours, icePlains, 255, 255, 255);
	setBiomeColour(biomeColours, iceMountains, 160, 160, 160);
	setBiomeColour(biomeColours, mushroomIsland, 255, 0, 255);
	setBiomeColour(biomeColours, mushroomIslandShore, 160, 0, 255);
	setBiomeColour(biomeColours, beach, 250, 222, 85);
	setBiomeColour(biomeColours, desertHills, 210, 95, 18);
	setBiomeColour(biomeColours, forestHills, 34, 85, 28);
	setBiomeColour(biomeColours, taigaHills, 22, 57, 51);
	setBiomeColour(biomeColours, extremeHillsEdge, 114, 120, 154);
	setBiomeColour(biomeColours, jungle, 83, 123, 9);
	setBiomeColour(biomeColours, jungleHills, 44, 66, 5);
	setBiomeColour(biomeColours, jungleEdge, 98, 139, 23);
	setBiomeColour(biomeColours, deepOcean, 0, 0, 48);
	setBiomeColour(biomeColours, stoneBeach, 162, 162, 132);
	setBiomeColour(biomeColours, coldBeach, 250, 240, 192);
	setBiomeColour(biomeColours, birchForest, 48, 116, 68);
	setBiomeColour(biomeColours, birchForestHills, 31, 95, 50);
	setBiomeColour(biomeColours, roofedForest, 64, 81, 26);
	setBiomeColour(biomeColours, coldTaiga, 49, 85, 74);
	setBiomeColour(biomeColours, coldTaigaHills, 36, 63, 54);
	setBiomeColour(biomeColours, megaTaiga, 89, 102, 81);
	setBiomeColour(biomeColours, megaTaigaHills, 69, 79, 62);
	setBiomeColour(biomeColours, extremeHillsPlus, 80, 112, 80);
	setBiomeColour(biomeColours, savanna, 189, 178, 95);
	setBiomeColour(biomeColours, savannaPlateau, 167, 157, 100);
	setBiomeColour(biomeColours, mesa, 217, 69, 21);
	setBiomeColour(biomeColours, mesaPlateau_F, 176, 151, 101);
	setBiomeColour(biomeColours, mesaPlateau, 202, 140, 101);

	setBiomeColour(biomeColours, warmOcean, 0, 0, 172);
	setBiomeColour(biomeColours, lukewarmOcean, 0, 0, 144);
	setBiomeColour(biomeColours, coldOcean, 32, 32, 112);
	setBiomeColour(biomeColours, warmDeepOcean, 0, 0, 80);
	setBiomeColour(biomeColours, lukewarmDeepOcean, 0, 0, 64);
	setBiomeColour(biomeColours, coldDeepOcean, 32, 32, 56);
	setBiomeColour(biomeColours, frozenDeepOcean, 64, 64, 144);

	setBiomeColour(biomeColours, ocean+128, 0, 0, 112);
	setBiomeColour(biomeColours, plains+128, 141, 179, 96);
	setBiomeColour(biomeColours, desert+128, 250, 148, 24);
	setBiomeColour(biomeColours, extremeHills+128, 96, 96, 96);
	setBiomeColour(biomeColours, forest+128, 5, 102, 33);
	setBiomeColour(biomeColours, taiga+128, 11, 102, 89);
	setBiomeColour(biomeColours, swampland+128, 7, 249, 178);
	setBiomeColour(biomeColours, river+128, 0, 0, 255);
	setBiomeColour(biomeColours, hell+128, 255, 0, 0);
	setBiomeColour(biomeColours, sky+128, 128, 128, 255);
	setBiomeColour(biomeColours, frozenOcean+128, 144, 144, 160);
	setBiomeColour(biomeColours, frozenRiver+128, 160, 160, 255);
	setBiomeColour(biomeColours, icePlains+128, 140, 180, 180);
	setBiomeColour(biomeColours, iceMountains+128, 160, 160, 160);
	setBiomeColour(biomeColours, mushroomIsland+128, 255, 0, 255);
	setBiomeColour(biomeColours, mushroomIslandShore+128, 160, 0, 255);
	setBiomeColour(biomeColours, beach+128, 250, 222, 85);
	setBiomeColour(biomeColours, desertHills+128, 210, 95, 18);
	setBiomeColour(biomeColours, forestHills+128, 34, 85, 28);
	setBiomeColour(biomeColours, taigaHills+128, 22, 57, 51);
	setBiomeColour(biomeColours, extremeHillsEdge+128, 114, 120, 154);
	setBiomeColour(biomeColours, jungle+128, 83, 123, 9);
	setBiomeColour(biomeColours, jungleHills+128, 44, 66, 5);
	setBiomeColour(biomeColours, jungleEdge+128, 98, 139, 23);
	setBiomeColour(biomeColours, deepOcean+128, 0, 0, 48);
	setBiomeColour(biomeColours, stoneBeach+128, 162, 162, 132);
	setBiomeColour(biomeColours, coldBeach+128, 250, 240, 192);
	setBiomeColour(biomeColours, birchForest+128, 48, 116, 68);
	setBiomeColour(biomeColours, birchForestHills+128, 31, 95, 50);
	setBiomeColour(biomeColours, roofedForest+128, 64, 81, 26);
	setBiomeColour(biomeColours, coldTaiga+128, 49, 85, 74);
	setBiomeColour(biomeColours, coldTaigaHills+128, 36, 63, 54);
	setBiomeColour(biomeColours, megaTaiga+128, 89, 102, 81);
	setBiomeColour(biomeColours, megaTaigaHills+128, 69, 79, 62);
	setBiomeColour(biomeColours, extremeHillsPlus+128, 80, 112, 80);
	setBiomeColour(biomeColours, savanna+128, 189, 178, 95);
	setBiomeColour(biomeColours, savannaPlateau+128, 167, 157, 100);
	setBiomeColour(biomeColours, mesa+128, 217, 69, 21);
	setBiomeColour(biomeColours, mesaPlateau_F+128, 176, 151, 101);
	setBiomeColour(biomeColours, mesaPlateau+128, 202, 140, 101);
}

void initBiomeTypeColours(unsigned char biomeColours[256][3])
{
	setBiomeColour(biomeColours, Oceanic+44,  0x00, 0x00, 0xa0);
	setBiomeColour(biomeColours, Warm+44,     0xff, 0xc0, 0x00);
	setBiomeColour(biomeColours, Lush+44,     0x00, 0xa0, 0x00);
	setBiomeColour(biomeColours, Cold+44,     0x60, 0x60, 0x60);
	setBiomeColour(biomeColours, Freezing+44, 0xff, 0xff, 0xff);
}





void getBiomeColourMap(unsigned int *colbuf, const unsigned char biomeColour[256][3],
					   const int *ints, const unsigned int sx, const unsigned int sy, const unsigned int pixscale)
{
	unsigned int i, j;
	int containsInvalidBiomes = 0;

	for(j = 0; j < sy; j++)
	{
		for(i = 0; i < sx; i++)
		{
			int id = ints[i*sx+j];

			unsigned int r, g, b;
			if(id < 0 || id >= 256)
			{
				// This may happen for some intermediate layers
				containsInvalidBiomes = 1;
				r = biomeColour[id&0x7f][0]-40; r = (r>0xff) ? 0x00 : r&0xff;
				g = biomeColour[id&0x7f][1]-40; g = (g>0xff) ? 0x00 : g&0xff;
				b = biomeColour[id&0x7f][2]-40; b = (b>0xff) ? 0x00 : b&0xff;
			}
			else
			{
				if(id < 128) {
					r = biomeColour[id][0];
					g = biomeColour[id][1];
					b = biomeColour[id][2];
				} else {
					r = biomeColour[id][0]+40; r = (r>0xff) ? 0xff : r&0xff;
					g = biomeColour[id][1]+40; g = (g>0xff) ? 0xff : g&0xff;
					b = biomeColour[id][2]+40; b = (b>0xff) ? 0xff : b&0xff;
				}
			}

			unsigned int m, n;
			for(m = 0; m < pixscale; m++){
				for(n = 0; n < pixscale; n++){
					colbuf[(j*pixscale+n) + sy*pixscale*(i*pixscale+m)] =
							((r&0xff) << 16) + ((g&0xff) << 8) + (b&0xff);
				}
			}
		}
	}

	if(containsInvalidBiomes)
	{
		printf("Warning: Ints contain invalid Biome IDs (Is this an intermediate layer?)\n");
	}
}


void viewmap(Layer *layer, unsigned char biomeColour[256][3], int areaX, int areaZ,  int areaWidth,  int areaHeight, unsigned int pixscale,const char* nom)
{
	int *ints = allocCache(layer, areaWidth, areaHeight);
	// generate the biome ints

	genArea(layer, ints, areaX, areaZ, areaWidth, areaHeight);

	// Calculate a hash for the area (useful to verify the accuracy of the map)
	unsigned int i, hash = 0;
	for(i = 0; i < areaWidth*areaHeight; i++) hash = hash ^ (i*(ints[i]+1));
	printf("Hash:%3X\n", hash&0xfff);

	// construct the X11 window




	// convert the biome ints to a colour image
	auto *colbuf = (unsigned int *) malloc(sizeof(unsigned int) *
								   areaWidth*areaHeight*pixscale*pixscale);

	getBiomeColourMap(colbuf, biomeColour, ints, areaWidth, areaHeight, pixscale);
	int width = areaWidth;
	int height = areaHeight;

	// Create a test image - in this case a Mandelbrot Set fractal
	// The output is a 1D array of floats, length: width * height
	printf("Creating Image\n");


	printf("Saving PNG\n");
	writeImage(nom, width, height, colbuf, "This is my test image");

}






inline void setRGB(png_byte *ptr, unsigned int val)
{
	ptr[0] = (val&0xFF0000u)>>16u; ptr[1] = (val&0xFF00u)>>8u; ptr[2] =  val&0xFFu;
}

int writeImage(const char* filename, int width, int height, unsigned int *buffer, char* title)
{
	int code = 0;
	FILE *fp = NULL;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep row = NULL;

	// Open file for writing (binary mode)
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file %s for writing\n", filename);
		code = 1;
		goto finalise;
	}

	// Initialize write structure
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fprintf(stderr, "Could not allocate write struct\n");
		code = 1;
		goto finalise;
	}

	// Initialize info structure
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fprintf(stderr, "Could not allocate info struct\n");
		code = 1;
		goto finalise;
	}

	// Setup Exception handling
	if (setjmp(png_jmpbuf(png_ptr))) {
		fprintf(stderr, "Error during png creation\n");
		code = 1;
		goto finalise;
	}

	png_init_io(png_ptr, fp);

	// Write header (8 bit colour depth)
	png_set_IHDR(png_ptr, info_ptr, width, height,
				 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
				 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	// Set title
	if (title != NULL) {
		png_text title_text;
		title_text.compression = PNG_TEXT_COMPRESSION_NONE;
		title_text.key = "Title";
		title_text.text = title;
		png_set_text(png_ptr, info_ptr, &title_text, 1);
	}

	png_write_info(png_ptr, info_ptr);

	// Allocate memory for one row (3 bytes per pixel - RGB)
	row = (png_bytep) malloc(3 * width * sizeof(png_byte));

	// Write image data
	int x, y;
	for (y=0 ; y<height ; y++) {
		for (x=0 ; x<width ; x++) {
			setRGB(&(row[x*3]), buffer[y*width + x]);
		}
		png_write_row(png_ptr, row);
	}

	// End write
	png_write_end(png_ptr, NULL);

	finalise:
	if (fp != NULL) fclose(fp);
	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	if (row != NULL) free(row);

	return code;
}









