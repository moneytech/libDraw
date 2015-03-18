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
#include <stdarg.h>

//Colors
color red = {255, 0, 0};
color orange = {255, 140, 0};
color yellow = {255, 255, 0};
color limegreen = {50, 205, 0};
color brightgreen = {0, 255, 0};
color blue = {0, 0, 255};
color dodgerblue = {30, 144, 255};
color indigo = {199, 21, 133};
color violet = {75, 0, 130};
color aqua = {0, 200, 200};
color black = {0, 0, 0};
color white = {255, 255, 255};
color brown = {139, 69, 19};
color cyan = {0, 139, 139};
color gold = {255, 215, 0};
color crimson = {220, 20, 60};
color pink = {255, 205, 180};
color purple = {153, 50, 204};
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
	//VideoBuffer = (char *) malloc(VideoX * VideoY * (VideoBPP / 4));
}
void flush_buffer(){
	memset(VideoMemory, 0x00, VideoBuffer);
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
			VideoMemory[offset+1] = c.red;
			VideoMemory[offset+2] = c.blue;
			VideoMemory[offset+3] = c.green;
		}
	}
}
//Draw point
void draw_point(point p, unsigned int thickness, color c)
{
	int i,j,thick;
	thick=thickness/2;
	for(i=-thick;i<thick;i++)
		for(j=-thick;j<thick;j++)
			put_pixel(p.x+i, p.y+j, c);
}

//Custom draw line based on DDA line algorithm
void draw_line(point p1, point p2, unsigned int thickness, color c)
{
    float pixel, dx, dy, curx, cury;
    int i,gd,gm,thickx,thicky,thickstart,thickend;
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
	  for(thickx=thickstart;thickx<=thickend;thickx++){		//Crude method of thickness for lines
          	put_pixel(curx+thickx,cury,c);
	  }
	  for(thicky=thickstart;thicky<=thickend;thicky++){
		put_pixel(curx,cury+thicky,c);
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
int x, y;
for(y=-radius; y<=radius; y++)
    for(x=-radius; x<=radius; x++)
        if(x*x+y*y <= radius*radius)
            put_pixel(center.x+x, center.y+y, c);
}
void draw_polygon(color c, unsigned int thickness, int points, ...)
{
	int i;
	point tempPoint1={0,0};
	point tempPoint2={0,0};
	va_list arguments;
	if(points>=3)
	{
		va_start(arguments, points);
		tempPoint1 = va_arg(arguments, point);
		for ( i=0; i< points; i++ )
		{
			tempPoint2=va_arg(arguments, point);
			draw_line(tempPoint2, tempPoint1, thickness, c);
			tempPoint1=tempPoint2;
		}
		va_end (arguments);
	}
}
