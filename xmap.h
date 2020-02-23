#ifndef XMAPVIEW_H_
#define XMAPVIEW_H_

#include "generationByCubitect/generator.hpp"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

typedef struct xwin_t
{
	Display *dis;
	int screen;
	Window win;
	GC gc;

	unsigned int *colbuf;
	unsigned int sx, sy;

} xwin_t;


void initBiomeColours(unsigned char biomeColours[256][3]);
void initBiomeTypeColours(unsigned char biomeColours[256][3]);


xwin_t init_x(unsigned int sx, unsigned int sy, const char *titel);
void close_x(xwin_t w);

void viewmap(Layer *layer, unsigned char biomeColour[256][3],
			 int areaX, int areaZ, int areaWidth, int areaHeight, unsigned int pixscale,const char* nom);



#endif