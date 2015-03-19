# libDraw
About
--------------
libDraw is a library that lets you draw some simple 2D shapes in BareMetal-OS.
To use, first compile by running 
```
gcc -c -m64 -nostdlib -nostartfiles -nodefaultlibs -fomit-frame-pointer -mno-red-zone -o libDraw.o libDraw.c
```
Then, when linking files, add libDraw.o. eg:
```
ld -T app.ld -o $1.app crt0.o $1.o libBareMetal.o libDraw.o libc.a libm.a
```

It is important that you have the app.ld, crt0.o, libc.a and libm.a files. If you don't try using the script `newlib.sh` in the BareMetal scripts to get them.

As well, it is **very** important that you have video mode enabled in Pure64.
Go into the Pure64/src directory and edit the file `sysvar.asm`
Line 11 should read
```
cfg_vesa:               db 0    ; By default VESA is disabled. Set to 1 to enable.
```
Change the value to 1:
```
cfg_vesa:               db 1    ; By default VESA is disabled. Set to 1 to enable.
```
and rebuild Pure64 (run ./build.sh if you're using BareMetal scripts)

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
 - `int init_libDraw()` - Initialize libDraw. Returns 1 if video mode is not enabled, and 0 if everything works out fine. **You must run this prior to using any of the other functions, or they will not work!**
 - `clear_screen()` Clears the screen
 - `put_pixel(unsigned int x, unsigned int y, color c)` - Draws a pixel at the location x,y with the color c
 - `draw_line(point p1, point p2, unsigned int thickness, color c)` - Draws a line with the specified thickness from p1 to p2 with color c
 - `draw_frect(point p, unsigned int l, unsigned int w, color c)` - Draws a filled rectangle starting at point p and going l out on the x axis and w out on the y axis with color c
 - `draw_circle(point center, int radius, color c)` - Draws a circle (not filled in!) at point center with specified radius and color c
 - `void draw_fcircle(point center, int radius, color c)` - Draws a filled circle at point center with specified radius and color c
 

**Variables** 
 - `unsigned long VideoX` - Size of the screen on the X axis
 - `unsigned long VideoY` - Size of the screen on the Y axis
 - `unsigned long VideoBBP` - BBP of the screen (color resolution)
 - `char* VideoMemory` - Video memory, **mainly used internally, it is not recommended you play with this unless you know what you're doing!**
