/*-----------------------------------------------------------------------------
/
/
/----------------------------------------------------------------------------*/

#include "OpenCV_util.h"

void cvUtil_create2dArray(Mat* input, uint8_t*** outputPtr)
{
  int imgWidth = input->cols;
  int imgHeight = input->rows;

  (*outputPtr) = new uint8_t*[imgHeight];
  for(int i = 0; i < imgHeight; ++i)
  {
    (*outputPtr)[i] = new uint8_t[imgWidth];
  }
  for(int i=0;i<imgHeight;i++)
  {
    for(int j=0;j<imgWidth;j++)
    {
      (*outputPtr)[i][j] = input->at<uint8_t>(i,j);
    }
  }
}

void cvUtil_filePrint2dArray(char* fileName, uint8_t*** inputPtr, int height, int width)
{
  FILE* fd = NULL;

  fd = fopen(fileName,"w+");
  if(fd == NULL)
    return;

  for(int i=0;i<height;i++)
  {
    for(int j=0;j<width;j++)
    {
      fprintf(fd, "%2X ",(*inputPtr)[i][j]);
    }
    fprintf(fd, "\n");
  }
  
  fclose(fd);
}
