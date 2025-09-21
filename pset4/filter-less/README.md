# Problem Set 4: Filter-Less

This project is a C program that applies various image filters to 24-bit uncompressed BMP files.  
The available filters include blur, greyscale, refection, and sepia.

## Compilation

Use GCC to compile:

```bash
gcc -o filter filter.c helpers.c -lm
```

How to Run:

```bash
./filter -[flag] infile.bmp outfile.bmp
```