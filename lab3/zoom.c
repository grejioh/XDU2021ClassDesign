#include <stdio.h>
#include <stdlib.h>
#pragma pack(1)
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

  if (tar == NULL) {
    printf("Somethings wrong!!");
    return;
  }

  fread(&sourceFileHeader, sizeof(bmpFileHeader), 1, src);
  fread(&sourceInfoHeader, sizeof(bmpInfoHeader), 1, src);
  if (sourceFileHeader.bfType != 0x4D42) {
    fclose(src);
    printf("%x FUCK oOFF", sourceFileHeader.bfType);
    return;
  }
  int size = sourceInfoHeader.biHeight * sourceInfoHeader.biWidth;
  int bytesPerLine =
      ((sourceInfoHeader.biWidth * sourceInfoHeader.biBitCount + 31) >> 5) << 2;
  size = bytesPerLine * sourceInfoHeader.biHeight;
  printf("%d\n%d", sourceInfoHeader.biHeight, sourceInfoHeader.biWidth);

  sourceFilePixels = (unsigned int *)malloc(sizeof(unsigned int) * size);
  fread(sourceFilePixels, sizeof(int), size, src);
  int height = (int)(sourceInfoHeader.biHeight);
  int width = (int)(sourceInfoHeader.biWidth);
  int newsize = height * width;

  targetFilePixels = (unsigned int *)malloc(sizeof(unsigned int) * newsize);

  targetFileHeader = sourceFileHeader;
  targetInfoHeader = sourceInfoHeader;
  targetFilePixels = sourceFilePixels;
  /*  */
  /* for (int i = 0; i < height; i++) { */
  /*   for (int j = 0; j < width; j++) { */
  /*     int m = (int)sourceInfoHeader.biHeight + j; */
  /*     targetFilePixels[i * height + j] = sourceFilePixels[m]; */
  /*   } */
  /* } */

  fwrite(&sourceFileHeader, sizeof(bmpFileHeader), 1, tar);
  fwrite(&sourceInfoHeader, sizeof(bmpInfoHeader), 1, tar);

  fwrite(sourceFilePixels, sizeof(int), size, tar);
  fclose(src);
  fclose(tar);
}

void testFunc() {
  /* printf("%lu\n", sizeof(sourceFileHeader)); */
  /* printf("%lu\n", sizeof(bmpInfoHeader)); */
  printf("%u\n", sourceInfoHeader.biBitCount);
}
int main(int argc, char *argv[]) {
  copyBmpFile(argv[1], argv[2]);
  testFunc();
  return 0;
}
