/* 
 * libDraw library source file
 * libDraw is a library for BareMetal-OS to draw things.
 * Written by ohnx.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libBareMetal.h"
#include <time.h>
#include "libDraw.h"

//Including custom math functions because, well, math.h doesn't like to work >.>
typedef double real; // change to float for single precision
//Square root function from http://www.alejandrosegovia.net/2012/01/23/implementing-sqrt/
//No copyright was found on the page, so I'm guessing it's fine to use.
real f(real x, real n) {return x*x - n;}
real sqrt(real n){
    real err = 0.00000000001f;
    real h = 0.01f;
    real x = 1.0f; // seed
    real xant = 0.0f;
    do {
        xant = x;
        real df = (f(x+h, n) - f(x, n))/h;
        x = x - f(x, n)/df;
    }
    while (abs(x - xant) > err);
    return x;
}
//Floor from http://codegolf.stackexchange.com/a/293
//I could have implemented this myself, but I wanted to get everything working ASAP
real floor(real x){int i=x-2;while(++i<=x-1);return i;}

//Conversion tool from rgb color to color
color toColor(unsigned char red, unsigned char green, unsigned char blue){color t={red,green,blue};return t;}
//Conversion tool from x, y to point
point toPoint(unsigned int x, unsigned int y){point t={x,y};return t;}

int init_libDraw(){
        VideoMemory = (char*)b_system_config(20, 0);
        if (VideoMemory == 0)
        {
                return 1;
        }
        VideoX = b_system_config(21, 0);
        VideoY = b_system_config(22, 0);
        VideoBPP = b_system_config(23, 0);
}
//Found from 3dstars.c
void clear_screen()
{
	int bytes = VideoX * VideoY;

	if (VideoBPP == 24)
		bytes = bytes * 3;
	else if (VideoBPP == 32)
		bytes = bytes * 4;

	memset(VideoMemory, 0x00, bytes);
}
//Just going to leave the x y coordinates here
void put_pixel(unsigned int x, unsigned int y, color c)
{
	int offset = 0;
	if (x >= 0 && x < VideoX && y >= 0 && y < VideoY) // Sanity check
	{
		offset = y * VideoX + x;
		if (VideoBPP == 24)
		{
			offset = offset * 3;
			VideoMemory[offset] = c.blue;
			VideoMemory[offset+1] = c.green;
			VideoMemory[offset+2] = c.red;
		}
		else if (VideoBPP == 32)
		{
			offset = offset * 4;
			VideoMemory[offset] = 0x00;
			VideoMemory[offset+1] = c.blue;
			VideoMemory[offset+3] = c.green;
			VideoMemory[offset+4] = c.red;
		}
	}
}

//Custom draw line based on DDA line algorithm
void draw_line(point p1, point p2, unsigned int thickness, color c)
{
    float pixel, dx, dy, curx, cury;
    int i,gd,gm,thick,thickstart,thickend;
    dx=abs(p2.x-p1.x);
    dy=abs(p2.y-p1.y);
    if(dx>=dy) pixel=dx;
    else pixel=dy;

    dx=dx/pixel;//increment required each time
    dy=dy/pixel;
    curx=p1.x;
    cury=p1.y;
    i=1;
    thickstart=0-thickness/2;
    thickend=0-thickstart;
    while(i<=pixel)
    {
	  for(thick=thickstart;thick<=thickend;thick++){		//Crude method of thickness for lines
          	put_pixel(curx+thick,cury,c);
	  }
          curx=curx+dx;
          cury=cury+dy;
          i=i+1;
    }
    //TODO: Smooth the lines
}
//Draw a filled rectangle
void draw_frect(point p, unsigned int l, unsigned int w, color c)
{
	int i, j;
	for(i=0; i<l; i++)
	{
		for(j=0; j<w; j++)
		{
			put_pixel(p.x+i, p.y+j, c);
		}
	}
}
//Algorithm found from http://groups.csail.mit.edu/graphics/classes/6.837/F98/Lecture6/circle.html
//Implementation in C by ohnx
    void draw_circle(point center, int radius, color c)
    {
		point e;
        int r2;

        r2 = radius * radius;
        put_pixel(center.x, center.y + radius, c);
        put_pixel(center.x, center.y - radius, c);
        put_pixel(center.x + radius, center.y, c);
        put_pixel(center.x - radius, center.y, c);

        e.y = radius;
        e.x = 1;
        e.y = sqrt(r2 - 1)+ 0.5;
        while (e.x < e.y) {
            put_pixel(center.x + e.x, center.y + e.y, c);
            put_pixel(center.x + e.x, center.y - e.y, c);
            put_pixel(center.x - e.x, center.y + e.y, c);
            put_pixel(center.x - e.x, center.y - e.y, c);
            put_pixel(center.x + e.y, center.y + e.x, c);
            put_pixel(center.x + e.y, center.y - e.x, c);
            put_pixel(center.x - e.y, center.y + e.x, c);
            put_pixel(center.x - e.y, center.y - e.x, c);
            e.x += 1;
            e.y = sqrt(r2 - e.x*e.x);
        }
        if (e.x == e.y) {
            put_pixel(center.x + e.x, center.y + e.y, c);
            put_pixel(center.x + e.x, center.y - e.y, c);
            put_pixel(center.x - e.x, center.y + e.y, c);
            put_pixel(center.x - e.x, center.y - e.y, c);
        }
    }
//Found from http://stackoverflow.com/a/1237519
//Adapted for BareMetal-OS by ohnx
void draw_fcircle(point center, int radius, color c)
{
point e;
for(e.y=-radius; e.y<=radius; e.y++)
    for(e.x=-radius; e.x<=radius; e.x++)
        if(e.x*e.x+e.y*e.y <= radius*radius)
            put_pixel(center.x+e.x, center.y+e.y, c);
}
