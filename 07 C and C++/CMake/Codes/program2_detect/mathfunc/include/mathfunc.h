#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>

using namespace std;
using namespace cv;

double getDistance (Point2f, Point2f);
Point2f getCenter (Point2f, Point2f);
Point2f getArmorCenter (Point2f, Point2f, Point2f, Point2f);
