
// MFCAppDialogDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMFCAppDialogDlg �Ի���
class CMFCAppDialogDlg : public CDialogEx
{
// ����
public:
	CMFCAppDialogDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCAPPDIALOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_check1;
	CButton m_check2;
	CButton m_check3;
	CButton m_check4;
	CButton m_check5;
	CButton m_check6;
	void InitAllCheckBoxStatus();
	afx_msg void OnBnClickedPortalRadio();
	afx_msg void OnBnClickedForumRadio();
	afx_msg void OnBnClickedBlogRadio();
	afx_msg void OnBnClickedOk();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ReSize(void);
	POINT old;
};
