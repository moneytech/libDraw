/* 
 * Simple program to print out a rectangle, circle, and filled circle using libDraw
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
	draw_frect(toPoint(50, 50), 50, 50, red);
        draw_frect(toPoint(100, 50), 50, 50, orange);
        draw_frect(toPoint(150, 50), 50, 50, yellow);
        draw_frect(toPoint(200, 50), 50, 50, brightgreen);
        draw_frect(toPoint(250, 50), 50, 50, dodgerblue);
        draw_frect(toPoint(300, 50), 50, 50, blue);
        draw_frect(toPoint(350, 50), 50, 50, indigo);
        draw_frect(toPoint(400, 50), 50, 50, violet);
        draw_frect(toPoint(450, 50), 50, 50, gold);
	flush_buffer();
	draw_line(toPoint(100, 100), toPoint(100, 200), 2, toColor(255, 255, 255));
        draw_line(toPoint(100, 100), toPoint(150, 100), 2, toColor(255, 255, 255));
        draw_line(toPoint(100, 150), toPoint(140, 150), 2, toColor(255, 255, 255));
        draw_line(toPoint(100, 200), toPoint(150, 200), 2, toColor(255, 255, 255));
	draw_point(toPoint(VideoX/2, VideoY/2), 2, blue);
	flush_buffer();
	draw_polygon(blue, 2, 5, toPoint(300, 300), toPoint(400, 300), toPoint(450, 400), toPoint(375, 450), toPoint(250, 400));
	draw_polygon(pink, 2, 3, toPoint(400, 400), toPoint(500, 500), toPoint(300,500));
	flush_buffer();
}
