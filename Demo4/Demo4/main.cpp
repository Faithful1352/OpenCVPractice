#include<opencv2/opencv.hpp>
#include<vector>
using namespace cv;
using namespace std;


int main() {
	Mat srcImg, tempImg;
	srcImg = imread("test.png");
	if (!srcImg.data)
	{
		cout << "no Img" << endl;
		return -1;
	}



	int i;
	cin >> i;

	Mat gray;
	resize(srcImg, tempImg, Size(srcImg.cols / 2, srcImg.rows / 2), 0, 0);
	cvtColor(tempImg, gray, COLOR_RGB2GRAY);
	medianBlur(gray, gray, 3);

	vector<Vec3f>circles;//Ô²

	//¶þÖµ»¯Í¼Ïñ£¬Í¹ÏÔÂÖÀª
	Mat thresh;
	threshold(gray, thresh, 0, 255, THRESH_OTSU);

	vector<Point>sanjiao;

	vector<Point>approx;
	vector<Point>squares;

	Mat srcImg1;
	srcImg1 = thresh.clone();
	vector<vector<Point>>contours;
	findContours(srcImg1, contours, RETR_TREE, CHAIN_APPROX_NONE);
	Mat dstImg(srcImg1.rows, srcImg1.cols, CV_8UC3, Scalar(255, 255, 255));




	switch (i)
	{
	case 0:
		HoughCircles(gray, circles, HOUGH_GRADIENT, 1.2, srcImg.rows / 20, 100, 60, 0, 0);

		for (size_t i = 0; i < circles.size(); i++)//»­Ô²
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			circle(dstImg, center, radius, Scalar(0, 255, 0), 5, 8, 0);
			circle(dstImg, center, 3, Scalar(0, 255, 0), -1);
			cout << "Ô²ÐÄ" << i + 1 << center << endl;
		}
		break;
	case 1:
		drawContours(dstImg, contours, 0, Scalar(0, 0, 255), 3);
		break;
	case 2:
		drawContours(dstImg, contours, 2, Scalar(0, 0, 255), 3);

		break;
	default:
		cout << "ÊäÈë´íÎó";
		break;
	}

	imshow("123", dstImg);
	waitKey(0);
	return 0;


}