# libDraw

About
--------------
libDraw is a library that lets you draw some simple 2D shapes in [BareMetal-OS](https://github.com/ReturnInfinity/BareMetal-OS).
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
See [this article](https://github.com/ohnx/libDraw/wiki/Enabling-Video-Mode-in-BareMetal-OS) for more info.

Need help?
---------------------
Check out the [wiki](https://github.com/ohnx/libDraw/wiki)
