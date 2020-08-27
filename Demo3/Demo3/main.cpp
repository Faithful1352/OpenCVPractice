#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;
Mat g_scrImage, g_scrImagecopy, g_dstImage, g_midImage;
vector<Vec3f>circles;
static void on_HoughCircles(int, void*);


int main() {
	g_scrImage = imread("4.png");
	g_scrImagecopy = imread("4.png");
	imshow("SourceImage", g_scrImage);


	namedWindow("Design Sketch");
	//createTrackbar("yuzhi", "Design Sketch", &g_nthreshold, 30, on_HoughCircles);
	on_HoughCircles(1.5, 0);
	while (char(waitKey()) != 'q') {}
	return 0;
}
static void on_HoughCircles(int, void*) {
	cvtColor(g_scrImage, g_midImage, COLOR_BGR2GRAY);
	GaussianBlur(g_midImage, g_midImage, Size(9, 9), 2, 2);//必须要用高斯blur。
	double g_nthresholdcopy = (double)12 / 10;
	HoughCircles(g_midImage, circles, HOUGH_GRADIENT, g_nthresholdcopy, g_midImage.rows / 20, 100, 60, 0, 0);//输入图像为灰度图
	for (size_t i = 0; i < circles.size(); i++) {
		//提取出圆心坐标
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		//提取出圆半径
		int radius = cvRound(circles[i][2]);
		//圆心
		circle(g_scrImage, center, 3, Scalar(0, 0, 0), -1, 8, 0);
		//圆
		circle(g_scrImage, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}
	imshow("Design Sketch", g_scrImage);
	g_scrImage = g_scrImagecopy.clone();
}
