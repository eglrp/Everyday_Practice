#ifndef __BMPINFO_H__
#define __BMPINFO_H__

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef long LONG;

//λͼ�ļ�ͷBITMAGFILEHEADER
typedef struct tagBITMAPFILEHEADER
{
    //WORD bfType; //λͼ�ļ����ͣ�����ΪBM
	DWORD bfSize; //λͼ�ļ��Ĵ�С���ֽڵ�λ
	WORD bfReserved1; //λͼ�ļ������֣�����Ϊ0
	WORD bfReserved2; //λͼ�ļ������֣�����Ϊ0
	DWORD bfOffBits; //λͼ�ļ�ͷ�����ݵ�ƫ��
}BITMAPFILEHEADER;

//λͼ��ϢͷBITMAPINFOHEADER
typedef struct tagBITMAPINFOHEADER
{
	DWORD biSize; //�ýṹ��ռ�ֽ���
	LONG biWidth; //λͼ�Ŀ�ȣ����ص�λ
	LONG biHeight; //λͼ�ĸ߶ȣ����ص�λ
	WORD biPlanes; //Ŀ���豸��λ����������Ϊ1
	WORD biBitCount; //��ɫ��ȣ���ÿ��������ռ��λ��
	DWORD biCompression; //λͼ��ѹ������
	DWORD biSizeImage; //λͼ�Ĵ�С���ֽڵ�λ
	LONG biXPelsPerMeter; //λͼ��ˮƽ�ֱ���
	LONG biYPelsPerMeter; //λͼ�Ĵ�ֱ�ֱ���
	DWORD biClrUsed; //λͼʵ��ʹ�õ���ɫ������ɫ��
	DWORD biClrImportant; //λͼ��ʾ�бȽ���Ҫ����ɫ��
}BITMAPINFOHEADER;

//��ɫ��RGBQUAD
typedef struct tagRGBQUAD
{
	BYTE rgbBlue; //����ɫ����ɫ����
	BYTE rgbGreen; //����ɫ����ɫ����
	BYTE rgbRed; //����ɫ�ĺ�ɫ����
	BYTE rgbReserved; //����ֵ
}RGBQUAD;

//������ϢIMAGEDATA
typedef struct tagIMAGEDATA
{
	BYTE blue;
	BYTE green;
	BYTE red;
}IMAGEDATA;

#endif