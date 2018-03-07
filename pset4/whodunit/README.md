# Questions

## What's `stdint.h`?

This header defines a set of integral type aliases with specific width requirements, along with macros specifying their limits and macro functions to create values of these types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

 to make things easier to understand and focus more on the actual programs rather than the semantics of all data types. Unsigned stores positive values

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

 1, 8, 8, 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

B M

## What's the difference between `bfSize` and `biSize`?

bfSize
The size, in bytes, of the bitmap file.

biSize
The number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount
The number of bits-per-pixel

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

can't open file for reading or file for writing

## Why is the third argument to `fread` always `1` in our code?

to read 1 element of data defined bytes long

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

fseek, however, allows you to change the location of the file pointer.

## What is `SEEK_CUR`?

current position of pointer
