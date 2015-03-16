# libDraw
Drawing library in C for BareMetal-OS
About
--------------
It's a drawing library for BareMetal-OS.
To use, first compile by running 
```
gcc -c -m64 -nostdlib -nostartfiles -nodefaultlibs -fomit-frame-pointer -mno-red-zone -o libDraw.o libDraw.c
```
Then, when linking files, add libDraw.o. eg:
```
ld -T app.ld -o $1.app crt0.o $1.o libc.a libBareMetal.o libDraw.o
```
-------------------------------------------------------------------------------------

Documentation
-----------------
**New types added**
 - Points - have an x value and a y value (unsigned int)
 - Colors - have a red, green and blue (unsigned char)

**Functions**

**The following functions are mainly used internally, but are still accessible to users:**
 - `double sqrt(double n)` - Square root
 - `double floor(double n)` - Floor function

**Main functions:**
 - `point toPoint(unsigned int x, unsigned int y)` - converts from x and y value to point
 - `color toColor(unsigned char red, unsigned char green, unsigned char blue)` - converts from RGB values to color
 - `clear_screen()` Clears the screen
 - `put_pixel(unsigned int x, unsigned int y, color c)` - Draws a pixel at the location x,y with the color c
 - `draw_line(point p1, point p2, unsigned int thickness, color c)` - Draws a line with the specified thickness from p1 to p2 with color c
 - `draw_frect(point p, unsigned int l, unsigned int w, color c)` - Draws a filled rectangle starting at point p and going l out on the x axis and w out on the y axis with color c
 - `draw_circle(point center, int radius, color c)` - Draws a circle (not filled in!) at point center with specified radius and color c
 - `void draw_fcircle(point center, int radius, color c)` - Draws a filled circle at point center with specified radius and color c
 

**Variables** 
 - `VideoX` - Size of the screen on the X axis
 - `VideoY` - Size of the screen on the Y axis
 - `VideoBBP` - BBP of the screen (color resolution)
 - `VideoMemory` - Video memory, **mainly used internally, it is not recommended you play with this unless you know what you're doing!**
