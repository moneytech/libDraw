#include <stdio.h>
#include "font.h"

void render(char *bitmap, int xreal, int yreal, int/*color*/ c) {
    int x,y,set;
    for (x=12; x >= 0; x--) {
        for (y=7; y >= 0; y--) {
            //Replace with set pixel later on
	    set = bitmap[x] & 1 << y;
            if(set)
		printf("X");//put_pixel(X, Y, color)
	    else
		printf(" ");//put_pixel(X, Y, color)
	    xreal++;
	    yreal++;
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    int ord;
    ord = atoi(argv[1]);
    char *bitmap = font8x8_basic[ord];
    render(bitmap, 0, 0, 0);
}
