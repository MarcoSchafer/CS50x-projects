# Problem Set 4: Filter-More 

This project is a C program that applies various image filters to 24-bit uncompressed BMP files.  
The available filters include grayscale, reflect, blur, and edge detection.

## Compilation

Use GCC to compile:

```bash
gcc -o filter filter.c helpers.c -lm
```

How to Run:

```bash
./filter -[flag] infile.bmp outfile.bmp
```

