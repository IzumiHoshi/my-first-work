
// ChnTranslateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChnTranslate.h"
#include "ChnTranslateDlg.h"
#include "afxdialogex.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CChnTranslateDlg 对话框



CChnTranslateDlg::CChnTranslateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChnTranslateDlg::IDD, pParent)
	, m_csInput(_T(""))
	, m_csOutput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChnTranslateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_editInput);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_editOutput);
	DDX_Control(pDX, IDC_BUTTON_UNICODE, m_btnUnicode);
	DDX_Control(pDX, IDC_BUTTON_UTF8, m_btnUtf8);
	DDX_Control(pDX, IDC_BUTTON_GBK, m_btnGBK);
	DDX_Control(pDX, IDC_BUTTON_GB2312, m_btnGB2312);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_csInput);
	DDX_Text(pDX, IDC_EDIT_OUTPUT, m_csOutput);
}

BEGIN_MESSAGE_MAP(CChnTranslateDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_UNICODE, &CChnTranslateDlg::OnBnClickedButtonUnicode)
	ON_BN_CLICKED(IDC_BUTTON_UTF8, &CChnTranslateDlg::OnBnClickedButtonUtf8)
END_MESSAGE_MAP()


// CChnTranslateDlg 消息处理程序

BOOL CChnTranslateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChnTranslateDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChnTranslateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChnTranslateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChnTranslateDlg::OnBnClickedButtonUnicode()
{
	UpdateData(TRUE);
	int nLenth = m_csInput.GetLength();
	m_csOutput.Empty();
	CString csTemp;

	for (int i = 0; i < nLenth; i++)
	{
		csTemp.Format(_T("\\u%04X"), m_csInput.GetAt(i));
		m_csOutput.Append(csTemp);
	}

	UpdateData(FALSE);
}

DWORD _utf8_One_Byte_Range = 0x7f;
DWORD _utf8_Two_Bytes_Range = 0x7ff;
DWORD _utf8_Three_Bytes_Range = 0xffff;
DWORD _utf8_Four_Bytes_Range = 0x10ffff;

void ConvertUnicodeToUTF8(char &cUnicode)
{

}

void CChnTranslateDlg::OnBnClickedButtonUtf8()
{
	UpdateData(TRUE);
	int nLenth = m_csInput.GetLength();
	m_csOutput.Empty();

	for (int i = 0; i < nLenth; i++)
	{
		TRACE("a%d\n", m_csInput.GetAt(i));
	}
}
