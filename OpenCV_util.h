/*-----------------------------------------------------------------------------
/
/
/----------------------------------------------------------------------------*/

#include <stdint.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

void cvUtil_create2dArray(Mat* input, uint8_t*** outputPtr);

void cvUtil_filePrint2dArray(char* fileName, uint8_t*** inputPtr, int height, int width);
