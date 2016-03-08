/*-----------------------------------------------------------------------------
/
/
/----------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include "DebugPrintf.h"
#include "OpenCV_util.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
/*---------------------------------------------------------------------------*/
using namespace std;
using namespace cv;
/*---------------------------------------------------------------------------*/
uint8_t saturated_add(uint8_t val1, int8_t val2);
/*---------------------------------------------------------------------------*/
int main( int argc, char** argv )
{    
  Mat rawImg;
  Mat dithImg;
  int imgWidth;
  int imgHeight;
  uint8_t** imgPtr;

  if(argc != 2)
  {
    printf("> Usage: ./dithering [path_to_image]\n");
    return -1;
  }

  /* Load the image and convert to grayscale first */
  rawImg = imread(argv[1]);    
  cvtColor(rawImg, dithImg, CV_BGR2GRAY);  

  /* Get the size info */
  imgWidth = dithImg.cols;
  imgHeight = dithImg.rows;
  dbg("> Image width: %d\r\n",imgWidth);
  dbg("> Image height: %d\r\n",imgHeight);

  /* Run the 'Floyd-Steinberg' dithering algorithm ... */  
  int err;
  int8_t a,b,c,d;
  
  for(int i=0; i<imgHeight; i++)
  {      
    for(int j=0; j<imgWidth; j++)
    {
      if(dithImg.at<uint8_t>(i,j) > 127)
      {
        err = dithImg.at<uint8_t>(i,j) - 255;
        dithImg.at<uint8_t>(i,j) = 255;
      }
      else
      {
        err = dithImg.at<uint8_t>(i,j) - 0;
        dithImg.at<uint8_t>(i,j) = 0;
      }

      a = (err * 7) / 16;
      b = (err * 1) / 16;
      c = (err * 5) / 16;
      d = (err * 3) / 16;
      
      if((i != (imgHeight-1)) && (j != 0) && (j != (imgWidth - 1)))
      {
        dithImg.at<uint8_t>(i+0,j+1) = saturated_add(dithImg.at<uint8_t>(i+0,j+1),a);
        dithImg.at<uint8_t>(i+1,j+1) = saturated_add(dithImg.at<uint8_t>(i+1,j+1),b);
        dithImg.at<uint8_t>(i+1,j+0) = saturated_add(dithImg.at<uint8_t>(i+1,j+0),c);
        dithImg.at<uint8_t>(i+1,j-1) = saturated_add(dithImg.at<uint8_t>(i+1,j-1),d);
      }
    } 
  }
      
  /* Show results. */
  imshow("Raw Image",rawImg);
  imshow("Dithered Image",dithImg);   
  printf("> Press any key to exit ...\n");

  waitKey(0);  
  return 0;
}
/*---------------------------------------------------------------------------*/
uint8_t saturated_add(uint8_t val1, int8_t val2)
{
  int16_t val1_int = val1;
  int16_t val2_int = val2;
  int16_t tmp = val1_int + val2_int;

  if(tmp > 255)
  {
    return 255;
  }
  else if(tmp < 0)
  {   
    return 0;
  }
  else
  {
    return tmp;
  }
}
/*---------------------------------------------------------------------------*/