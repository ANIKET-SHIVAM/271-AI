#ifndef OPENCV_HPP
#define OPENCV_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <opencv2/core/utility.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include <sstream>
#include <queue>
#include <ostream>
#include <vector>
#pragma comment(lib, "vfw32.lib")
#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace cv;
using namespace std;
void MatchingMethod( int, void* );
void thisMouseCallBack(int event, int x, int y, int flags, void *param);
void maxLocs(const Mat& src, queue<Point>& dst, size_t size);
//Global vars
Mat img;
Mat templ;
Mat result;
char* image_window = "Source Image";
char* result_window = "Result window";
int match_method;
int max_Trackbar = 5;
int lowT;
queue<Point> locations;
char L;
Mat mx;
string ADB_DIR("C:/adt/sdk/platform-tools/");
class _RGB {
  public:
    uchar R;
    uchar G;
    uchar B;
    _RGB(uchar R,uchar G, uchar B) : R(R), G(G), B(B) {}
};

#endif