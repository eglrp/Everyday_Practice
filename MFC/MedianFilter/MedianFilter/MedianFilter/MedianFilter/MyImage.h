#ifndef __MYIMAGE_H__
#define __MYIMAGE_H__

/*!
 * \file MyImage.h
 * \date 2016/07/23 19:30
 *
 * \author ranjiewen
 * \contact: ranjiewen@outlook.com
 *
 * \brief ͼ�ദ����ֵ�˲�
 *
 * TODO: long description
 *
 * \note
*/

#include <iostream>
#include <string>
#include "BmpInfo.h"

class MyImage
{
public:
	MyImage(std::string &readfile, std::string &loadfile);
	~MyImage();

	void LoadImage();//��ȡͼ��
	void SaveImage();//���ͼ��
	void Convert();//��RGBͼת���ɻҶ�ͼ
	void MedianFilterOper();//��ͼ�������ֵ�˲�����

private:
	static int compa(const void *a, const void *b) //�����еıȽϺ���
	{
		return *(char *)a - *(char *)b;
	}
private:
	std::string m_readfile; //ԭʼͼƬ·��
	std::string m_loadfile; //���ͼƬ·��
	BITMAPFILEHEADER m_bmpHead; 
	RGBQUAD m_bmpPla[256];
	BITMAPINFOHEADER m_bmpInfo;
	unsigned char *m_imagedata;
};

#endif