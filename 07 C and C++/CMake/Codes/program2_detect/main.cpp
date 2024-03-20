#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include "detectfunc.h"
#include "mathfunc.h"

using namespace std;
using namespace cv;

// 预处理，通过颜色阈值将图像过滤


int main()
{
    Mat img, mask;
    string path = "/home/blake/桌面/华工机器人实验室/正式批任务及相关资料/装甲板/装甲板.avi";
    VideoCapture cap (path);

    while (true)
    {   
        if (!cap.read (img))
        {
            break;
        }

        if (waitKey (20) >= 0)
        {
            break;
        }

        // cap.read (img);

        mask = imgPre (img);
        getArmor (getLights (getContours (mask,img),img),img);

        
        imshow ("Image",img);
        imshow ("Mask",mask);

        // waitKey (20);
    }
}

// int main ()
// {
//     string path = "/home/blake/桌面/detector/20231006-130844.png";
//     Mat img = imread (path), mask;

//     mask = imgPre (img);
//     getArmor (getLights (getContours (mask,img),img),img);

//     imshow ("mask", mask);
//     imshow ("Image",img);
//     waitKey (0);


//     return 0;
// }