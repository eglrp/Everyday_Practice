
// MFCAppDialog.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCAppDialogApp: 
// �йش����ʵ�֣������ MFCAppDialog.cpp
//

class CMFCAppDialogApp : public CWinApp
{
public:
	CMFCAppDialogApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCAppDialogApp theApp;