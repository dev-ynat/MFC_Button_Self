
// MFC_Button_SelfDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC_Button_Self.h"
#include "MFC_Button_SelfDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnDestroy();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCButtonSelfDlg 대화 상자



CMFCButtonSelfDlg::CMFCButtonSelfDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_BUTTON_SELF_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCButtonSelfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCButtonSelfDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDD_MFC_BUTTON_SELF_DIALOG, &CMFCButtonSelfDlg::OnIddMfcButtonSelfDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_TEST, &CMFCButtonSelfDlg::OnBnClickedBtnTest)
END_MESSAGE_MAP()


// CMFCButtonSelfDlg 메시지 처리기

BOOL CMFCButtonSelfDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, 1280, 960);
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_CDlgImage, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(0, 0, 640, 480);
	// UINT nIDTemplate ID는 리소스의 Dlg를 가져오면 된다.
	// CWnd* pParentWnd 윈도우는 this. 현재의 다이아로그를 사용할 것이다
	// 이 포인터를 사용해야지 ( m_pDlgImage ) 자식 다이아로그에서 부모 다이아로그로 접근이 가능하다.
	
	m_pDlgImgResult = new CDlgImage;
	m_pDlgImgResult->Create(IDD_CDlgImage, this);
	m_pDlgImgResult->ShowWindow(SW_SHOW);
	m_pDlgImgResult->MoveWindow(640, 0, 640, 480);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCButtonSelfDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCButtonSelfDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCButtonSelfDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCButtonSelfDlg::OnIddMfcButtonSelfDialog()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

}





void CMFCButtonSelfDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	if(m_pDlgImage) delete m_pDlgImage;
	if(m_pDlgImgResult) delete m_pDlgImgResult;
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CMFCButtonSelfDlg::callFunc(int n)
{
	//int nData = n;
	std::cout << n << std::endl;
}

void CMFCButtonSelfDlg::OnBnClickedBtnTest()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	// GetBits는 void * 이다.
	// void * 는 형태가 정해져 있지 않은 포인터로, 앞에 어떤 형태로 받을지에 대한 설명이 필요하다
	int nWitdh = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();
	memset(fm, 0xff, nWitdh * nHeight);

	int nRand = rand() % 100;
	for (int k = 0; k < nRand; k++) {
		int x = rand() % nWitdh;
		int y = rand() % nHeight;
		fm[y * nPitch + x] = 0;
	}
	int nIndex = 0;
	for (int i = 0; i < nWitdh; i++) {
		for (int j = 0; j < nHeight; j++) {
			if (fm[j * nPitch + i] == 0) {
				if (m_pDlgImgResult->m_nDataCount < 100) {
					m_pDlgImgResult[nIndex].m_ptData[nIndex].x = i;
					m_pDlgImgResult[nIndex].m_ptData[nIndex].y = i;
					m_pDlgImgResult->m_nDataCount = ++nIndex;
				}
			} 
		}
	}
	
	//memset(fm, 0, 640 * 480);
	// 화면을 윈도우 창 밖으로 보내야지 갱신되는건 화면 업데이트가 없었기 때문이다.
	m_pDlgImage->Invalidate();
	m_pDlgImgResult->Invalidate();
}
