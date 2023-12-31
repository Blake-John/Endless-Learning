#include "mathfunc.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>

using namespace std;
using namespace cv;

// 计算两个点之间的距离
double getDistance (Point2f pt1,Point2f pt2)
{
    double dxs, dys,d;
    dxs = pow ((pt1.x - pt2.x),2);
    dys = pow ((pt1.y - pt2.y),2);

    d = sqrt (dxs + dys);

    return d;
}

// 计算两个点的中点
Point2f getCenter (Point2f pt1, Point2f pt2)
{
    double x, y;
    x = (pt1.x + pt2.x) / 2;
    y = (pt1.y + pt2.y) / 2;

    return Point2f (x,y);
}

// 计算装甲板中点
Point2f getArmorCenter (Point2f pt0, Point2f pt1, Point2f pt2, Point2f pt3)
{
    double h1, h2, ratio, d1, d2, x, y;

    // d = getDistance (pt1,pt3);
    d1 = getDistance (pt0,pt1);
    d2 = getDistance (pt2,pt3);
    ratio = d1 / d2;

    x = (ratio*pt3.x + pt1.x) / (1 + ratio);
    y = (ratio*pt3.y + pt1.y) / (1 + ratio);

    return Point (x,y);

}