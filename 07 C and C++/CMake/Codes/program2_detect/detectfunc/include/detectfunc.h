#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

Mat imgPre (Mat);
vector <RotatedRect> getContours (Mat, Mat);
vector <vector <RotatedRect>> getLights (vector <RotatedRect>, Mat);
void getArmor (vector <vector <RotatedRect>>, Mat);
