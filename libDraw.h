/* 
 * libDraw library header file
 * libDraw is a library for BareMetal-OS to draw things.
 * Written by ohnx.
*/
#ifndef LIBDRAW_INC
#define LIBDRAW_INC
//Struct definitions (to avoid having like "unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int thickness, color c")
typedef struct {
	unsigned int x, y;
} point;
typedef struct {
	unsigned char red, green, blue;
} color; //Going with the American spelling for colour here

//Math
typedef double real;
//Functions
real f(real x, real n);
real sqrt(real n);
real floor(real x);
color toColor(unsigned char red, unsigned char green, unsigned char blue);
point toPoint(unsigned int x, unsigned int y);
int init_libDraw();
void clear_screen();
//Keeping original put_pixel for coords because I'm lazy.
void put_pixel(unsigned int x, unsigned int y, color c);
void draw_line(point p1, point p2, unsigned int thickness, color c);
void draw_frect(point p, unsigned int l, unsigned int w, color c);
//American spelling for centre, too
void draw_circle(point center, int radius, color c);
void draw_fcircle(point center, int radius, color c);
//Variables
unsigned long VideoX, VideoY, VideoBPP;
char* VideoMemory;

extern color red;
extern color orange;
extern color yellow;
extern color limegreen;
extern color brightgreen;
extern color blue;
extern color dodgerblue;
extern color indigo;
extern color violet;
extern color aqua;
extern color black;
extern color white;
extern color brown;
extern color cyan;
extern color gold;
extern color crimson;

#endif
