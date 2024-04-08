#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include "mathfunc.h"
#include "detectfunc.h"

using namespace std;
using namespace cv;

// 预处理，通过颜色阈值将图像过滤
Mat imgPre (Mat img)
{
    int mycolor[6] = {10,77,99,33,248,255};
    Mat imgHSV, mask;
    Scalar lower (mycolor[0],mycolor[1],mycolor[2]), upper (mycolor[3],mycolor[4],mycolor[5]);
    
    cvtColor (img,imgHSV,COLOR_BGR2HSV);
    inRange (imgHSV,lower,upper,mask);

    return mask;
}

// 获取灯条的最小外接矩形
vector <RotatedRect> getContours (Mat imgPp,Mat img)
{
    vector <vector <Point>> contours;
    findContours (imgPp,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);

    // 筛选，用灯条长宽比和面积筛选
    vector <RotatedRect> armorRect;
    for (int i = 0; i < contours.size (); i++)
    {
        float area;
        area = contourArea (contours[i]);

        RotatedRect roRect = minAreaRect (contours[i]);
        float aspectRatio;
        aspectRatio = max (roRect.size.width,roRect.size.height) / min (roRect.size.width,roRect.size.height);
        if (aspectRatio > 3.0 and area > 100.0 )
        {
            armorRect.push_back (roRect);
        }
    }

    // 绘制旋转矩形
    for (int i = 0; i < armorRect.size (); i++)
    {
        Point2f points[4];
        armorRect[i].points (points);
        for (int j = 0; j < 4; j++)
        {
            // cout << points[j] << endl;
            line (img,points[j],points[(j + 1) % 4],Scalar (0,255,0),3);
            // circle (img,points[j],10,Scalar (0,0,255),FILLED);
            // putText (img,to_string (j),points[j],FONT_HERSHEY_DUPLEX,1,Scalar (255,255,255),1);
        }
        // putText(img,to_string (i),points[i],FONT_HERSHEY_DUPLEX,1,Scalar (255,0,255),1);
    }

    return armorRect;
}

vector <vector <RotatedRect>> getLights (vector <RotatedRect> armorRect, Mat img)
{
    vector <vector<RotatedRect>> light_assem;

    // 将灯条匹配
    for (int i = 0; i < armorRect.size (); i++)
    {
        for (int j = i + 1; j < armorRect.size (); j++)
        {   
            auto angle1 = armorRect[i].angle, angle2 = armorRect[j].angle;
            
            if (abs (angle1) > 60)
            {
                angle1 = abs (angle1 - 90);
            }
            if (abs (angle2) > 60)
            {
                angle2 = abs (angle2 - 90);
            }
            cout << angle1 << '\t' << angle2 << abs (angle1 - angle2) << endl;
            if (abs (angle1 - angle2) < 6 )
            {
                double dratio_wl =  min (armorRect[i].size.width,armorRect[i].size.height) / max (armorRect[i].size.width,armorRect[i].size.height) - \
                    min (armorRect[j].size.width,armorRect[j].size.height) / max (armorRect[j].size.width,armorRect[j].size.height);
                if (abs (dratio_wl) < 0.5)
                {
                // if (max (armorRect[i].size.width,armorRect[i].size.height) - max (armorRect[j].size.width,armorRect[j].size.height) < 10)
                // {
                // if (abs (armorRect[i].size.height - armorRect[j].size.height) < 120)
                // {
                //     if (abs (armorRect[i].size.width - armorRect[j].size.width) < 120)
                //     {
                    double d = getDistance (armorRect[i].center,armorRect[j].center);
                    double ratio_dl = d / max (armorRect[i].size.width,armorRect[i].size.height);
                    // double ratio2 = d / max (armorRect[j].size.width,armorRect[j].size.height);
                    if (ratio_dl > 2 and ratio_dl < 3 )
                    {
                        vector <RotatedRect> armor;
                        armor.push_back (armorRect[i]);
                        armor.push_back (armorRect[j]);
                        light_assem.push_back (armor);

                    }
                //     }
                // }
                // }
                }
            }
        }
    }

    return light_assem;
}

void getArmor (vector <vector <RotatedRect>> light_assem,Mat img)
{   
    Point2f c_b1;
    Point2f c_t1;
    Point2f c_b2;
    Point2f c_t2;

    for (auto lights : light_assem)
    {
        RotatedRect rect1 = lights[0], rect2 = lights[1];
        Point2f center1 = rect1.center, center2 = rect2.center;
        Point2f points1[4], points2[4];
        rect1.points (points1);
        rect2.points (points2);
        Point center;

        vector <Point2f> high, down;
        for (int i = 0; i < 4; i++)
        {
            if (points1[i].y > center1.y)
            {
                high.push_back (points1[i]);
            }
            else
            {
                down.push_back (points1[i]);
            }
        }

        
        c_t1 = getCenter (high[0],high[1]);
        
        c_b1 = getCenter (down[0],down[1]);

        high.clear ();
        down.clear ();

        for (int i = 0; i < 4; i++)
        {
            if (points2[i].y > center2.y)
            {
                high.push_back (points2[i]);
            }
            else
            {
                down.push_back (points2[i]);
            }
        }
        c_t2 = getCenter (high[0],high[1]);
        c_b2 = getCenter (down[0],down[1]);

        high.clear ();
        down.clear ();
        
        center = getArmorCenter (c_b1,c_t1,c_t2,c_b2);

        line (img,c_b1,c_t2,Scalar (255,255,0),2);
        line (img,c_b2,c_t1,Scalar (255,255,0),2);
        circle (img,center,5,Scalar (0,255,0),FILLED);
        circle (img,c_b1,5,Scalar (0,0,255),FILLED);
        circle (img,c_b2,5,Scalar (0,0,255),FILLED);
        circle (img,c_t1,5,Scalar (0,0,255),FILLED);
        circle (img,c_t2,5,Scalar (0,0,255),FILLED);




    }
}