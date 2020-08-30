#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

static void on_HoughCircles(int, void*);

void findSquares(const Mat& image, Mat &out);
static double angle(Point pt1, Point pt2, Point pt0);
void findAngle(const Mat& image, Mat &out);

Mat src_input, src_output, g_midImage;
vector<Vec3f>circles;

int main() {
	src_input = imread("test.png");
	src_output = imread("test.png");


	string s;
	cin >> s;

	int i = (s == "circle") ? 0 : (s == "rectangle") ? 1 : 2;
	switch (i)
	{
	case 0:
		on_HoughCircles(1.5, 0);
		break;
	case 1:
		findSquares(src_input, src_output);
		break;
	case 2:
		findAngle(src_input, src_output);
	default:
		break;
	}



	waitKey(0);
	return 0;
}




static void on_HoughCircles(int, void*) {
	cvtColor(src_input, g_midImage, COLOR_BGR2GRAY);
	GaussianBlur(g_midImage, g_midImage, Size(9, 9), 2, 2);//必须要用高斯blur。
	double g_nthresholdcopy = (double)12 / 10;
	HoughCircles(g_midImage, circles, HOUGH_GRADIENT, g_nthresholdcopy, g_midImage.rows / 20, 100, 60, 0, 0);//输入图像为灰度图
	for (size_t i = 0; i < circles.size(); i++) {
		//提取出圆心坐标
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		//提取出圆半径
		int radius = cvRound(circles[i][2]);
		//圆心
		//circle(src_output, center, 3, Scalar(0, 0, 0), -1, 8, 0);
		//圆
		circle(src_output, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}
	imshow("Design Sketch", src_output);
}







//第一个参数是传入的原始图像，第二是输出的图像。
void findSquares(const Mat& image, Mat &out)
{
	int thresh = 100, N = 5;
	vector<vector<Point> > squares;
	squares.clear();

	Mat src, dst, gray_one, gray;

	src = image.clone();
	out = image.clone();
	gray_one = Mat(src.size(), CV_8U);
	//滤波增强边缘检测
	medianBlur(src, dst, 3);

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//在图像的每个颜色通道中查找矩形
	for (int c = 0; c < image.channels(); c++)
	{
		int ch[] = { c, 0 };

		//通道分离
		mixChannels(&dst, 1, &gray_one, 1, ch, 1);

		// 尝试几个阈值
		for (int l = 0; l < N; l++)
		{
			// 用canny()提取边缘
			if (l == 0)
			{
				//检测边缘
				Canny(gray_one, gray, 5, thresh, 5);
				//膨胀
				dilate(gray, gray, Mat(), Point(-1, -1));
			}
			else
			{
				gray = gray_one >= (l + 1) * 255 / N;
			}

			// 轮廓查找
			//findContours(gray, contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
			findContours(gray, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

			vector<Point> approx;

			// 检测所找到的轮廓
			for (size_t i = 0; i < contours.size(); i++)
			{
				//使用图像轮廓点进行多边形拟合
				approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

				//计算轮廓面积后，得到矩形4个顶点
				if (approx.size() == 4 && fabs(contourArea(Mat(approx))) > 1000 && isContourConvex(Mat(approx)))
				{
					double maxCosine = 0;

					for (int j = 2; j < 5; j++)
					{
						// 求轮廓边缘之间角度的最大余弦
						double cosine = fabs(angle(approx[j % 4], approx[j - 2], approx[j - 1]));
						maxCosine = MAX(maxCosine, cosine);
					}

					if (maxCosine < 0.3)
					{
						squares.push_back(approx);
					}
				}
			}
		}
	}


	for (size_t i = 0; i < squares.size(); i++)
	{
		const Point* p = &squares[i][0];

		int n = (int)squares[i].size();
		if (p->x > 3 && p->y > 3)
		{
			polylines(out, &p, &n, 1, true, Scalar(0, 0, 0), 3, LINE_AA);
		}
	}
	imshow("result", out);
}

static double angle(Point pt1, Point pt2, Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1 * dy2) / sqrt((dx1*dx1 + dy1 * dy1)*(dx2*dx2 + dy2 * dy2) + 1e-10);
}

//检测矩形
//参数(源图像,输出图像)
void findAngle(const Mat& image, Mat &out)
{
	int thresh = 500, N = 5;
	vector<vector<Point> > pictures;
	pictures.clear();

	Mat src, dst, gray_one, gray;

	src = image.clone();
	out = image.clone();
	gray_one = Mat(src.size(), CV_8U);
	//滤波增强边缘检测
	medianBlur(src, dst, 3);

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//在图像的每个颜色通道中查找矩形
	for (int c = 0; c < image.channels(); c++)
	{
		int ch[] = { c, 0 };

		//通道分离
		mixChannels(&dst, 1, &gray_one, 1, ch, 1);

		// 测试阈值
		for (int l = 0; l < N; l++)
		{
			// 用canny()提取边缘
			if (l == 0)
			{
				//检测边缘
				Canny(gray_one, gray, 5, thresh, 5);
				//膨胀
				dilate(gray, gray, Mat(), Point(-1, -1));
			}
			else
			{
				gray = gray_one >= (l + 1) * 255 / N;
			}

			// 轮廓查找
			findContours(gray, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

			vector<Point> approx;

			// 检测所找到的轮廓
			for (size_t i = 0; i < contours.size(); i++)
			{
				//使用图像轮廓点进行多边形拟合
				approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

				//计算轮廓面积后，得到矩形4个顶点
				if (approx.size() == 3 && fabs(contourArea(Mat(approx))) > 1000 && isContourConvex(Mat(approx)))
				{
					double minDist = 1e10;

					for (int i = 0; i < 3; i++)
					{
						Point side = approx[i] - approx[(i + 1) % 3];
						double squaredSideLength = side.dot(side);
						minDist = min(minDist, squaredSideLength);
					}
					if (minDist < 50)
						break;
					for (int i = 0; i < 3; i++)
						pictures.push_back(approx);
				}
			}
		}
	}


	for (size_t i = 0; i < pictures.size(); i++)
	{
		const Point* p = &pictures[i][0];

		int n = (int)pictures[i].size();
		if (p->x > 3 && p->y > 3)
		{
			polylines(out, &p, &n, 1, true, Scalar(0, 0, 0), 3, LINE_AA);
		}
	}
	imshow("result", out);
}