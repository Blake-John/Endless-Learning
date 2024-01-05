> In this chapter, we are going to learn how to
> Read the Images, Videos, and Get the Images from Webcams

# 1.1 How to Import the Packages ?

## 1.1.1 A `CMakeLists.txt` File

In C++, we need to write a `CMakeLists.txt` to **find the packages of OpenCV** , you can see [[CMake of OpenCV]] .

## 1.1.2 Proprocess Statement

Than, we can wirte the **preprocess statement** to import the packages : 

```
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
```

In the codes above : 
- `imgcodecs.hpp` is the head file which includes **the function to encode the imgs** 
- `imgproc.hpp` is the head file which includes **the function to process the imgs** 
- `highgui.hpp` is the head file which includes **the function to use the GUI Windows to show what we want** 

## 1.1.3 Namespace

We need to declare **the namespace of `cv`** when we want to use the function or class in OpenCV Package

1. declare on the head : `using namespace cv;`
2. declare when needed : `cv::Mat img;`

# 1.2 Read the Images

We will use the **`cv::Mat` class** to declare a **variable with matrix type** to store the information of an image.

```C++
int main ()
{
	std::string path = "test.jpg"; // the path to the img
	cv::Mat img;
	img = cv::imread (path); // read the img from the path

	cv::imshow ("Img", img); // show the img
	if (cv::waitKey (0) == 27)
	{
		std::exit (0);
	}
	// if press the esc button, exit
	// 0 means wait forever, other numbers are in ms
}
```

In the code above : 
- `cv::imread ()` is the function we use to **read the img from the path** 
- `cv::imshow ()` is the function to **show the img we want** 
- `cv::watiKey ()` will **wait the particular $ms$ for the keys being press**
- `27` is the **ASCII code of `esc`**

# 1.3 Read the Videos

We will use the **`cv::VideoCapture` class** to declare a videocapture to read the video.But all the videos are **stored as a set of imgs** , so we need to **read every img** from the capture and **show them one by one** . That is, we will show the video **in a loop**

```C++
int main ()
{
	std::string path = "test_video.mp4";
	cv::VideoCapture cap (path); // a video capture to store the video
	cv::Mat img;

	while (true)
	{
		cap.read (img); 
		// get one img from the capture, and remove it from the capture

		cv::imshow ("Video", img);
		if (cv::waitKey (20) == 27)
		{// after showing one img, we will stop for 20 ms
			break;
		}
	}
}
```

In the codes above : 
- `cv::VideoCapture` is the class to **deal with the videos** , we use this class to declare an instance `cap` 
- `cap.read (img);` will **get the img from the capture** 
- `cv::waitKey (20)` : a video should have the fps

# 1.4 Webcams

We will also use the `cv::VideoCapture` class to deal with a camera. It is like the video, but we will **set the port of camera to the instance instead of the path** 

```C++
int main ()
{
	cv::VideoCapture cap (0) // 0 is the port of the default camera
	cv::Mat img;

	while (true)
	{
		cap.read (img);

		cv::imshow ("Cam", img);
		if (cv::waitKey (20) == 27)
		{
			break;
		}
	}
}
```


# 1.5 The Detals of the Functions and Classes

All the images will be stored as a matrix whose shape is **height $\times$ weight** or **\[weight $\times$ height\]** 