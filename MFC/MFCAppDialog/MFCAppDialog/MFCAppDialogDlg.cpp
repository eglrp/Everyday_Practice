
// MFCAppDialogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCAppDialog.h"
#include "MFCAppDialogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCAppDialogDlg �Ի���



CMFCAppDialogDlg::CMFCAppDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCAppDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCAppDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Control(pDX, IDC_CHECK2, m_check2);
	DDX_Control(pDX, IDC_CHECK3, m_check3);
	DDX_Control(pDX, IDC_CHECK4, m_check4);
	DDX_Control(pDX, IDC_CHECK5, m_check5);
	DDX_Control(pDX, IDC_CHECK6, m_check6);
}

BEGIN_MESSAGE_MAP(CMFCAppDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PORTAL_RADIO, &CMFCAppDialogDlg::OnBnClickedPortalRadio)
	ON_BN_CLICKED(IDC_FORUM_RADIO, &CMFCAppDialogDlg::OnBnClickedForumRadio)
	ON_BN_CLICKED(IDC_BLOG_RADIO, &CMFCAppDialogDlg::OnBnClickedBlogRadio)
	ON_BN_CLICKED(IDOK, &CMFCAppDialogDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCAppDialogDlg ��Ϣ��������

BOOL CMFCAppDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ����Ӷ���ĳ�ʼ������
	// Ĭ��ѡ�С��Ż�����ѡ��ť
	CheckDlgButton(IDC_PORTAL_RADIO, 1);
	OnBnClickedPortalRadio();

	////�˴�����  ����Ӧ���ڴ�С�ĵ��ǲ��Բ�ͨ��
	//CRect rect;
	//GetClientRect(&rect);     //ȡ�ͻ�����С    
	//old.x = rect.right - rect.left;
	//old.y = rect.bottom - rect.top;
	//int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	//int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	//CRect rt;
	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);
	//cy = rt.bottom;
	//MoveWindow(0, 0, cx, cy);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CMFCAppDialogDlg::ReSize()
{
	float fsp[2];
	POINT Newp; //��ȡ���ڶԻ���Ĵ�С  
	CRect recta;
	GetClientRect(&recta);     //ȡ�ͻ�����С    
	Newp.x = recta.right - recta.left;
	Newp.y = recta.bottom - recta.top;
	fsp[0] = (float)Newp.x / old.x;
	fsp[1] = (float)Newp.y / old.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint; //���Ͻ�  
	CPoint OldBRPoint, BRPoint; //���½�  
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //�г����пؼ�    
	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID  
		GetDlgItem(woc)->GetWindowRect(Rect);
		ScreenToClient(Rect);
		OldTLPoint = Rect.TopLeft();
		TLPoint.x = long(OldTLPoint.x*fsp[0]);
		TLPoint.y = long(OldTLPoint.y*fsp[1]);
		OldBRPoint = Rect.BottomRight();
		BRPoint.x = long(OldBRPoint.x *fsp[0]);
		BRPoint.y = long(OldBRPoint.y *fsp[1]);
		Rect.SetRect(TLPoint, BRPoint);
		GetDlgItem(woc)->MoveWindow(Rect, TRUE);
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	old = Newp;
}


void CMFCAppDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

//  �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCAppDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCAppDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCAppDialogDlg::InitAllCheckBoxStatus()
{
	m_check1.EnableWindow(FALSE);
	m_check2.EnableWindow(FALSE);
	m_check3.EnableWindow(FALSE);
	m_check4.EnableWindow(FALSE);
	m_check5.EnableWindow(FALSE);
	m_check6.EnableWindow(FALSE);

	m_check1.SetCheck(0);
	m_check2.SetCheck(0);
	m_check3.SetCheck(0);
	m_check4.SetCheck(0);
	m_check5.SetCheck(0);
	m_check6.SetCheck(0);
}

void CMFCAppDialogDlg::OnBnClickedPortalRadio()
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	InitAllCheckBoxStatus();
	m_check2.EnableWindow(TRUE);
	m_check5.EnableWindow(TRUE);
}


void CMFCAppDialogDlg::OnBnClickedForumRadio()
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	InitAllCheckBoxStatus();
	m_check3.EnableWindow(TRUE);
	m_check6.EnableWindow(TRUE);
}


void CMFCAppDialogDlg::OnBnClickedBlogRadio()
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	InitAllCheckBoxStatus();
	m_check1.EnableWindow(TRUE);
	m_check4.EnableWindow(TRUE);
}


void CMFCAppDialogDlg::OnBnClickedOk()
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	CString strWebsiteSel;//ѡ����վ
	if (1==m_check1.GetCheck())
	{
		strWebsiteSel += _T("�Ʊ�");
	}
	if (1==m_check2.GetCheck())
	{
		strWebsiteSel += _T("����");
	}
	// ��ѡ�С�������̳������������ַ���
	if (1 == m_check3.GetCheck())
	{
		strWebsiteSel += _T("������̳ ");
	}
	// ��ѡ�С��������͡�����������ַ���
	if (1 == m_check4.GetCheck())
	{
		strWebsiteSel += _T("�������� ");
	}
	// ��ѡ�С����ס�����������ַ���
	if (1 == m_check5.GetCheck())
	{
		strWebsiteSel += _T("���� ");
	}
	// ��ѡ�С��������̳������������ַ���
	if (1 == m_check6.GetCheck())
	{
		strWebsiteSel += _T("�������̳ ");
	}
	SetDlgItemText(IDC_WEBSITE_EDIT, strWebsiteSel);

	// ������ַ�����ʾ�ڡ�ѡ�����վ����ı༭����
	//CDialogEx::OnOK();
}