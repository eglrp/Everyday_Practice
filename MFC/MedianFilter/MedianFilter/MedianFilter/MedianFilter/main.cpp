#include <iostream>
#include "MyImage.h"

int main()
{
	MyImage mybmp(std::string("Image\\init.bmp"), std::string("Image\\result.bmp"));
	mybmp.LoadImage(); //��ȡRGBͼƬ
	mybmp.Convert(); //ת���ɻҶ�ͼƬ
	mybmp.MedianFilterOper(); //��ֵ����
	mybmp.SaveImage(); //����ͼƬ
}