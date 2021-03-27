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

  int size = sourceInfoHeader.biHeight * sourceInfoHeader.biWidth;
  printf("%d\n%d", sourceInfoHeader.biHeight, sourceInfoHeader.biWidth);

  sourceFilePixels = (unsigned int *)malloc(sizeof(unsigned int) * size);

  int height = (int)(sourceInfoHeader.biHeight);
  int width = (int)(sourceInfoHeader.biWidth);
  int newsize = height * width;

  targetFilePixels = (unsigned int *)malloc(sizeof(unsigned int) * newsize);

  targetFileHeader = sourceFileHeader;
  targetInfoHeader = sourceInfoHeader;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int m = (int)sourceInfoHeader.biHeight + j;
      targetFilePixels[i * height + j] = sourceFilePixels[m];
    }
  }

  fwrite(&targetFileHeader, sizeof(bmpFileHeader), 1, tar);
  fwrite(&targetInfoHeader, sizeof(bmpInfoHeader), 1, tar);

  fwrite(targetFilePixels, newsize, sizeof(int), tar);
  fclose(src);
  /* fclose(tar); */
}

void testFunc() {
  /* printf("%lu\n", sizeof(sourceFileHeader)); */
  /* printf("%lu\n", sizeof(bmpInfoHeader)); */
  /* printf("%lu\n", sizeof(sourceFileHeader.bfReserved2)); */
}
int main(int argc, char *argv[]) {
  testFunc();
  copyBmpFile(argv[1], argv[2]);
  return 0;
}
