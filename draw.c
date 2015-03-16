/* 
 * Simple program to print out some shapes using libDraw
 * Written by ohnx.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libBareMetal.h"
#include <time.h>
#include "libDraw.h"
//Demo main
int main()
{
	int n, running=1;
	init_libDraw();
	clear_screen();
	draw_frect(toPoint(0, 0), VideoX, VideoY, toColor(166, 7, 7));
	draw_circle(toPoint(VideoX/2, VideoY/2), 350, toColor(255, 255, 255));
	draw_fcircle(toPoint(VideoX/2, VideoY/2), 100, toColor(7, 166, 166));
	draw_frect(toPoint(VideoX/2-25, VideoY/2-25), 50, 50, toColor(0, 255, 0));
	draw_frect(toPoint(50, 50), 200, 200, toColor(69, 236, 166));
	draw_line(toPoint(80, 90), toPoint(500, 600), 2, toColor(69, 105, 166));
}
