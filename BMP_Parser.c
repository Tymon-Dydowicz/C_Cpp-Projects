#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#pragma pack(1)

typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
typedef struct tagBITMAPFILEHEADER {
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
} BMPFILEHEADER;

// https://docs.microsoft.com/pl-pl/previous-versions/dd183376(v=vs.85)
typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BMPINFOHEADER;

void no_changes(FILE* f_out, unsigned char * PIXELS, int size, int height, int width){
  unsigned char *arr_gray;
  arr_gray = (unsigned char*)malloc(size);
  printf("%i, %i", height, width);
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width * 3; j+=3){
      arr_gray[i * width * 3 + j] = PIXELS[i * width * 3 + j];
      arr_gray[i * width * 3 + j + 1] = PIXELS[i * width * 3 + j + 1];
      arr_gray[i * width * 3 + j + 2] = PIXELS[i * width * 3 + j + 2];
    }
  }
  fwrite(arr_gray, size, 1, f_out);
  fclose(f_out);
}

void gray_scale(FILE* f_out, unsigned char * PIXELS, int size, int height, int width, int floor){
  unsigned char *arr_gray;
  arr_gray = (unsigned char*)malloc(floor * height);
  printf("%i, %i", height, width);
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width * 3; j+=3){
      if( j + 2 < width * 3){
        int gray_value = (PIXELS[i * width * 3 + j] + PIXELS[i * width * 3 + j + 1] + PIXELS[i * width * 3 + j + 2])/3;

        arr_gray[i * width * 3 + j] = gray_value;
        arr_gray[i * width * 3 + j + 1] = gray_value;
        arr_gray[i * width * 3 + j + 2] = gray_value;
      }
    }
  }
  fwrite(arr_gray, size, 1, f_out);
  fclose(f_out);
}


int main(int argc, char *argv[]){
  const char * path = argv[1];
  BMPFILEHEADER head;
  BMPINFOHEADER info;
  FILE* f_in = fopen(path, "rb");
  
  if (f_in == NULL){
    printf("Could't open file");
    return 0;
  }
  
  fread(&head, sizeof(BMPFILEHEADER), 1, f_in);
  fread(&info, sizeof(BMPINFOHEADER), 1, f_in);
  
  printf("\nBITMAPFILEHEADER:\n");
  printf("  bfType:          0x%X\n", head.bfType);
  printf("  bfSize:          %d\n", head.bfSize);
  printf("  bfReserved1:     0x%X\n", head.bfReserved1);
  printf("  bfReserved2:     0x%X\n", head.bfReserved2);
  printf("  bfOffBits:       %d\n", head.bfOffBits);
  
  printf("\nBITMAPINFOHEADER:\n");
  printf("  biSize:          %d\n", info.biSize);
  printf("  biWidth:         %d\n", info.biWidth);
  printf("  biHeight:        %d\n", info.biHeight);
  printf("  biPlanes:        %d\n", info.biPlanes);
  printf("  biBitCount:      %d\n", info.biBitCount);
  printf("  biCompression:   %d\n", info.biCompression);
  printf("  biSizeImage:     %d\n", info.biSizeImage);
  printf("  biXPelsPerMeter: %d\n", info.biXPelsPerMeter);
  printf("  biYPelsPerMeter: %d\n", info.biYPelsPerMeter);
  printf("  biClrUsed:       %d\n", info.biClrUsed);
  printf("  biClrImportant:  %d\n", info.biClrImportant);

  if (info.biBitCount != 24 || info.biCompression != 0){
    printf("histogram calculation is unsupported");
    return 0;
  }
 
  int blue[16] = {};
  int green[16] = {};
  int red[16] = {};
  
  int floor = ((info.biBitCount * info.biWidth + 31) / 32) * 4;

  unsigned char *PIXELS;
  PIXELS = (unsigned char*)malloc(floor * info.biHeight);
  fread(PIXELS, floor * info.biHeight, 1, f_in);
  fclose(f_in);
  

  for (int i = 0; i < (int)info.biHeight; i++){
    for (int j = 0; j < floor ; j+=3){
      blue[PIXELS[i * floor + j] / 16] += 1;
      green[PIXELS[i * floor + j + 1] / 16] += 1;
      red[PIXELS[i * floor + j + 2] / 16] += 1;
    }
  }
  
  printf("\nBlue:\n");
  for (int i = 0; i < 16; i++) {
    printf("  %d-%d: %.2f%%\n", i*16, i*16+15, (float)blue[i]/((float)info.biWidth*(float)info.biHeight)*100);
  }

  printf("\nGreen:\n");
  for (int i = 0; i < 16; i++) {
    printf("  %d-%d: %.2f%%\n", i*16, i*16+15, (float)green[i]/((float)info.biWidth*(float)info.biHeight)*100);
  }

  printf("\nRed:\n");
  for (int i = 0; i < 16; i++) {
    printf("  %d-%d: %.2f%%\n", i*16, i*16+15, (float)red[i]/((float)info.biWidth*(float)info.biHeight)*100);
  }
  
  if (argv[2] == NULL){
    printf("No output file to create grayscaled image\n");
    return 0;
  }
  FILE *f_out = fopen(argv[2], "wb+");

  fwrite(&head, sizeof(BMPFILEHEADER), 1, f_out);
  fwrite(&info, sizeof(BMPINFOHEADER), 1, f_out);

  gray_scale(f_out, PIXELS, (int)info.biSizeImage, (int)info.biHeight, (int)info.biWidth, floor);
  //no_changes(f_out, PIXELS, (int)info.biSizeImage, (int)info.biHeight, (int)info.biWidth);


  /*
  if (argv[3] == NULL){
    printf("No message to encode\n Decode steganography? [Y/N]\n");
    char answer;
    scanf("%c", &answer);
    if (answer[0] == 'N'){
      printf("Exiting");
      return 0;
    }
    decode(PIXELS);
    return 0;
  }
  */
  
  return 0;
}