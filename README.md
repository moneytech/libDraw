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
