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

	//������Ҫ����ͼƬ
	g_scrImage = imread("test.png");
	g_scrImagecopy = imread("test.png");
	//��ʾδ����ͼƬ
	imshow("SourceImage", g_scrImage);

	
	namedWindow("Design Sketch");
	//createTrackbar("yuzhi", "Design Sketch", &g_nthreshold, 30, on_HoughCircles);
	//���л���Բ���
	on_HoughCircles(1.5, 0);
	//��q��������
	while (char(waitKey()) != 'q') {}
	return 0;
}
static void on_HoughCircles(int, void*) {
	//ת���ɻ�ɫͼ��
	cvtColor(g_scrImage, g_midImage, COLOR_BGR2GRAY);
	//���и�˹�˲�
	GaussianBlur(g_midImage, g_midImage, Size(9, 9), 2, 2);
	double g_nthresholdcopy = (double)12 / 10;
	//����Բ���
	HoughCircles(g_midImage, circles, HOUGH_GRADIENT, g_nthresholdcopy, g_midImage.rows / 20, 100, 60, 0, 0);//����ͼ��Ϊ�Ҷ�ͼ
	for (size_t i = 0; i < circles.size(); i++) {
		//��ȡ��Բ������
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		//��ȡ��Բ�뾶
		int radius = cvRound(circles[i][2]);
		//Բ��
		circle(g_scrImage, center, 3, Scalar(0, 0, 0), -1, 8, 0);
		//Բ
		circle(g_scrImage, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}
	//��ʾ����Բ�����ͼƬ
	imshow("Design Sketch", g_scrImage);
	g_scrImage = g_scrImagecopy.clone();
}
