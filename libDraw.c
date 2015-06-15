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
#include "font.h"

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

//Character spacing
float libDraw_text_character_spacing = 1.2;

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
	VideoMemSize = VideoX * VideoY * (VideoBPP / 4);
	VideoBuffer = (char *) malloc(VideoMemSize);
	clear_buffer();
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
void clear_buffer()
{
	memset(VideoBuffer, 0x00, VideoMemSize);
}
void flush_buffer()
{
	memcpy(VideoMemory, VideoBuffer, VideoMemSize);
	//Alternatively, you could clear the buffer, but I'm going to leave that to clear_screen to do.
	//memset(VideoBuffer, 0x00, VideoMemSize);
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
			VideoBuffer[offset] = c.blue;
			VideoBuffer[offset+1] = c.green;
			VideoBuffer[offset+2] = c.red;
		}
		else if (VideoBPP == 32)
		{
			offset = offset * 4;
			VideoBuffer[offset] = 0x00;
			VideoBuffer[offset+1] = c.red;
			VideoBuffer[offset+2] = c.blue;
			VideoBuffer[offset+3] = c.green;
		}
	}
}

color get_pixel(unsigned int x, unsigned int y)
{
	color c;
	int offset = y * VideoX + x;
	if (VideoBPP == 24)
	{
		offset = offset * 3;
		c.blue = VideoMemory[offset];
		c.green = VideoMemory[offset+1];
		c.red = VideoMemory[offset+2];
	}
	else if (VideoBPP == 32)
	{
		offset = offset * 4;
		c.blue = VideoMemory[offset];
		c.green = VideoMemory[offset+1];
		c.red = VideoMemory[offset+2];
	}
	return c;
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
//Bresenham algorithm for lines - could go with Xiaolin Wu's, but this is easier ^.^
void draw_line(point s, point e, color c) {
    /*if(s.x=e.x) {
      int i=0;
      int d = abs(s.y-e.y);
      for(; i<d; i++) {
	put_pixel(s.x,s.y+i,c);
      }
      return;
    }
    if(s.y=e.y) {
      int i=0;
      int d = abs(s.x-e.x);
      for(; i<d; i++) {
	put_pixel(s.x+i,s.y,c);
      }
      return;
    }*/
    int x = s.x;
    int y = s.y;
    int x2 = e.x;
    int y2 = e.y;
    int w = x2 - x;
    int h = y2 - y;
    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0, i = 0;
    if (w<0) dx1 = -1; else if (w>0) dx1 = 1;
    if (h<0) dy1 = -1; else if (h>0) dy1 = 1;
    if (w<0) dx2 = -1; else if (w>0) dx2 = 1;
    int longest = abs(w);
    int shortest = abs(h);
    if (!(longest>shortest)) {
        longest = abs(h);
        shortest = abs(w);
        if (h<0) dy2 = -1; else if (h>0) dy2 = 1;
        dx2 = 0 ;
    }
    int numerator = longest >> 1;
    for (i=0;i<=longest;i++) {
	put_pixel(x,y,c);
        numerator += shortest;
        if (!(numerator<longest)) {
            numerator -= longest;
            x += dx1;
            y += dy1;
        } else {
            x += dx2;
            y += dy2;
        }
    }
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

void draw_polygon(color c, int points, ...)
{
    int i;
    point start;
    point tempPoint1;
    point tempPoint2;
    va_list args;
    if(points>=3) {
        va_start(args, points);
        start = va_arg(args, point);
        tempPoint1 = start;
        points--;
        for ( i=0; i< points; i++ ) {
            tempPoint2=va_arg(args, point);
            draw_line(tempPoint1, tempPoint2, c);
            tempPoint1=tempPoint2;
        }
        draw_line(start, tempPoint2, c);
        //printf("Line between points %d, %d and %d, %d\n", tempPoint2.x, tempPoint2.y, start.x, start.y);
        va_end(args);
    }
}

void draw_text(char* text, int length, point start, int size, color c)
{
	int i=0;
	int len=length;
	if(size==1) {
	  	for(;i<len;i++) {
	  		draw_schar(*(text+i), toPoint(start.x+i*7+2, start.y), c);
		}
		return;
	}
	draw_char(*text, toPoint(start.x+i*7*size, start.y), size, c);
	for(i=1;i<len;i++) {
	  draw_char(*(text+i), toPoint(start.x+i*7*size*libDraw_text_character_spacing, start.y), size, c);
	}
}

void draw_schar(char to, point where, color c)
{
	char *bitmap = font[to];
	int x,y,set;
	for (y=12; y >= 0; y--) {
		for (x=7; x >= 0; x--) {
			set = bitmap[y] & 1 << x;
			if(set) put_pixel(where.x+(12-x), where.y+(7-y), c);
		}
	}
}

void draw_char(char to, point where, int size, color c)
{
	char *bitmap = font[to];
	int x,y,set,xe,ye;
	for (y=12; y >= 0; y--) {
		for (x=7; x >= 0; x--) {
			set = bitmap[y] & 1 << x;
			if(set)
			  	for(xe=0;xe<size;xe++)
				  	for(ye=0;ye<size;ye++)
						put_pixel(where.x+size*(12-x)+xe, where.y+size*(7-y)+ye, c);
		}
	}
}

/*typedef struct {
     int xsize, ysize;
     color *data;
} image;


//Todo: change to different file format

image *readPPM(const char *filename)
{
         char buff[16];
         image *img;
         FILE *fp;
         int c, rgb_comp_color;
         //open PPM file for reading
         fp = fopen(filename, "rb");
         if (!fp) {
              fprintf(stderr, "Unable to open file '%s'\n", filename);
              exit(1);
         }

         //read image format
         if (!fgets(buff, sizeof(buff), fp)) {
              return null;
         }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6') {
         return null;
    }

    //alloc memory form image
    img = (image *)malloc(sizeof(image));
    if (!img) {
         return null;
    }

    //check for comments
    c = getc(fp);
    while (c == '#') {
    while (getc(fp) != '\n') ;
         c = getc(fp);
    }

    ungetc(c, fp);
    //read image size information
    if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
         return null;
    }

    //read rgb component
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
         return null;
    }

    //check rgb component depth
    if (rgb_comp_color!= 255) {
         fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
         exit(1);
    }

    while (fgetc(fp) != '\n') ;
    //memory allocation for pixel data
    img->data = (color*)malloc(img->x * img->y * sizeof(color));

    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    //read pixel data from file
    if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
         fprintf(stderr, "Error loading image '%s'\n", filename);
         exit(1);
    }

    fclose(fp);
    return img;
}*/