#include <stdio.h>
#include <stdlib.h>
typedef struct {
  unsigned short int bfType;
  unsigned int bfSize;
  unsigned short int bfReserved1, bfReserved2;
  unsigned int bfOffBits;
} bmpFileHeader;
typedef struct {
  unsigned int biSize, biWidth, biHeight;
  unsigned short biPlanes, biBitCount;
  unsigned int Compression, biSizeimages;
  int biXPelsPerMeter, biYPelsPerMeter;
  unsigned int biClrUsed, biClrImportant;
} bmpInfoHeader;
bmpFileHeader sourceFileHeader;
bmpFileHeader targetFileHeader;

bmpInfoHeader sourceInfoHeader;
bmpInfoHeader targetInfoHeader;

unsigned int *sourceFilePixels;
unsigned int *targetFilePixels;
void copyBmpFile(char *sourceName, char *targetName) {
  FILE *src;
  FILE *tar;
  src = fopen(sourceName, "rb"); // r for read; b for binary
  tar = fopen(targetName, "wb"); // w for write

  if (src == NULL) {
    printf("Error! can't find source file: %s\n", sourceName);
    return;
  }

  fread(&sourceFileHeader, sizeof(bmpFileHeader), 1, src);
  fread(&sourceInfoHeader, sizeof(bmpInfoHeader), 1, src);
}

void testFunc() {
  printf("%lu\n", sizeof(sourceFileHeader));
  printf("%lu\n", sizeof(bmpInfoHeader));
  printf("%lu\n", sizeof(sourceFileHeader.bfReserved2));
}
int main(int argc, char *argv[]) {
  testFunc();
  copyBmpFile(argv[1], argv[3]);
  return 0;
}
