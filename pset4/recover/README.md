# Problem Set 4 - Recover

This project is a C program that recovers JPEG images from a forensic image of a memory card.  
The program scans the memory card for JPEG signatures and writes each recovered image to a separate file.

## How to Compile

Use GCC to compile:

```bash
gcc -o recover recover.c -lm
```

How to Run:
```bash
./recover card.raw
```