/*!
 * \file houghTranslation.cpp
 *
 * \author ranjiewen
 * \date 2016/12/25 16:31
 *
 * 
 */

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
using namespace std;
using namespace cv;


//ȫ�ֱ�������
Mat g_srcImage, g_dstImage, g_midImage, circleImage;//ԭʼͼ���м�ͼ��Ч��ͼ
vector<Vec4i> g_lines;//����һ��ʸ���ṹg_lines���ڴ�ŵõ����߶�ʸ������
vector<Vec3f> circles;
//�������յ�TrackBarλ�ò���
int g_nthreshold=100;
ofstream text; //�����д�ļ�

//��������
static void on_HoughLines(int, void*);//�ص�����
static void ShowHelpText();
void drawDetectLines(Mat& image, const vector<Vec4i>& lines, Scalar & color);
void drawDetectCircles(Mat& image, const vector<Vec3f> &circles, Scalar & color);


int main(int agrc,char** argv[])
{
	//�ı�console������ɫ
	system("color 4F");  
	ShowHelpText();


	//����ԭʼͼ��Mat��������   
	Mat g_srcImage = imread("CAL_GRAY768_Pro.bmp");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ
	//��ʾԭʼͼ  
	//imshow("��ԭʼͼ��", g_srcImage);  


	//����������
	namedWindow("��Ч��ͼ��",1);
	createTrackbar("ֵ", "��Ч��ͼ��",&g_nthreshold,200,on_HoughLines);
	//createTrackbar("ֵ", "��Ч��ͼ��", &g_nthreshold, 200, on_HoughCircle);


	//���б�Ե����ת��Ϊ�Ҷ�ͼ
	Canny(g_srcImage, g_midImage, 50, 150, 3);//����һ��canny��Ե���
	//imshow("��Եͼ",g_midImage);
	cvtColor(g_midImage,g_dstImage, COLOR_GRAY2BGR);//ת����Ե�����ͼΪ�Ҷ�ͼ
	//����һ�λص�����������һ��HoughLinesP����
	on_HoughLines(g_nthreshold,0);
	HoughLinesP(g_midImage, g_lines, 1, CV_PI/180, 80, 50, 10 );


	cvtColor(g_srcImage, circleImage, COLOR_BGR2GRAY);
	GaussianBlur(circleImage, circleImage, Size(9, 9), 2, 2);
	//���ĵ����ǹؼ���һ��Ҫ֪���������ĵ������ܵ������ʵĲ���,�о���СͶƱ���Խ��Ӱ��ϴ�
	HoughCircles(circleImage, circles, HOUGH_GRADIENT, 1, 5, 100, 25, 0, 50);   


	text.open("textRecord.txt",ios::out);
	drawDetectLines(g_srcImage, g_lines, Scalar(0, 255, 0));
	drawDetectCircles(g_srcImage, circles, Scalar(0, 255, 0));
	text.close();

	//��ʾЧ��ͼ  
	imshow("��Ч��ͼ��", g_dstImage);  
	imshow("Ч��ͼ", g_srcImage);
	imwrite("canny_result.bmp", g_dstImage); //����ͼ
	imwrite("hough_trans.bmp", g_srcImage); //����ͼ

	waitKey(0);  

	return 0;  

}



void drawDetectLines(Mat& image, const vector<Vec4i>& lines, Scalar & color)
{
	text << "��⵽��ֱ������:" << lines.size() <<"��������Ϊһ�顣"<< endl;
	// ����⵽��ֱ����ͼ�ϻ�����
	vector<Vec4i>::const_iterator it = lines.begin();
	while (it != lines.end())
	{
		Point pt1((*it)[0], (*it)[1]);
		Point pt2((*it)[2], (*it)[3]);
		line(image, pt1, pt2, color, 2); //  �����������Ϊ2
		++it;
	}
	for (int i = 0; i < lines.size(); i++)
	{
		char str[_MAX_PATH];
		sprintf_s(str, _MAX_PATH, "��%d��ֱ�������˵����꣺", i + 1);

		text << str << "    (" << (lines.at(i)) << ")" << endl;
	}
	text << endl;
}

void drawDetectCircles(Mat& image, const vector<Vec3f> &circles, Scalar & color)
{
	text << "��⵽��Բ��������" << circles.size() << endl;
	for (size_t i = 0; i < circles.size(); i++)
	{
		//��������
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		char str[_MAX_PATH];
		sprintf_s(str, _MAX_PATH, "��%d��Բ�����꣺   ", i + 1);
		text << str << "   (" << circles[i][0] << "," << circles[i][1] << ")         " << "Բ�İ뾶��" << radius << endl;

		//����Բ��
		circle(image, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//����Բ����
		circle(image, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}

}

static void  on_HoughCircle(int ,void*)
{
	GaussianBlur(g_midImage, g_midImage, Size(9, 9), 2, 2);

	//��4�����л���Բ�任
	vector<Vec3f> circles;
	HoughCircles(g_midImage, circles, HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);

	//��5��������ͼ�л��Ƴ�Բ
	for (size_t i = 0; i < circles.size(); i++)
	{
		//��������
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//����Բ��
		circle(g_srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//����Բ����
		circle(g_srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}
}

//---��on_HoughLines( )������-------------------
//		����������ñ����/��ñ���㡿���ڵĻص�����
//----------------------------------------------
static void on_HoughLines(int, void*)
{
	//����ֲ���������ȫ�ֱ���
	Mat dstImage=g_dstImage.clone();
	Mat midImage=g_midImage.clone();

	//����HoughLinesP����
	vector<Vec4i> mylines;
	HoughLinesP(midImage, mylines, 1, CV_PI/180, g_nthreshold+1, 50, 10 );

	//ѭ����������ÿһ���߶�
	for( size_t i = 0; i < mylines.size(); i++ )
	{
		Vec4i l = mylines[i];
		line( dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23,180,55), 1, LINE_AA);
	}
	//��ʾͼ��
	imshow("��Ч��ͼ��",dstImage);
}

static void ShowHelpText()
{
	//�����ӭ��Ϣ��OpenCV�汾
	
	printf("\n\n\t\t\t   ��ǰʹ�õ�OpenCV�汾Ϊ��" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//���һЩ������Ϣ
	printf("\n\n\n\t������������۲�ͼ��Ч��~\n\n");


}
