
// ChnTranslateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChnTranslate.h"
#include "ChnTranslateDlg.h"
#include "afxdialogex.h"
#include <string>

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


// CChnTranslateDlg �Ի���



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


// CChnTranslateDlg ��Ϣ�������

BOOL CChnTranslateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChnTranslateDlg::OnPaint()
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

void ConvertUnicodeToUTF8(int &nUnicode)
{
	TRACE("%d\n", nUnicode);
	CString str;
	int nUTF8 = 0;
	if (nUnicode <= 0x7f)
	{
		return;
	}
	else if (nUnicode <= 0x7ff)
	{
		for (int i = 0; i < 11; i++)
		{
			str.AppendFormat(_T("%s%d "), (nUnicode >> i) & 1);
		}
	}
	else if (nUnicode <= 0xffff)
	{
		int nPreUtf8[3] = { 0x80, 0x80, 0xe0 };
		int nMaskUni[3] = { 0x3f, 0x3f, 0xf };
		for (size_t i = 0; i < 3; i++)
		{
			int nTemp = (nPreUtf8[i] + (nUnicode & nMaskUni[i]));
			nUTF8 = (nTemp << (i * 8)) + nUTF8;
			nUnicode >>= 6;
		}
		//int nPreUtf8[3] = { 0xe00000, 0x8000, 0x80 };
		//int nMaskUnicode[3] = { 0xf000, 0xfc0, 0x3f };

		//for (int i = 0; i < 3; i++)
		//{
		//	nUTF8 += (nPreUtf8[i] + (nMaskUnicode[i] & nUnicode));
		//}

		
		//int i = 0;
		//int j = 0;
		//for (; i < 6; i++, j++)
		//{
		//	nUTF8 = nUTF8 << 1 + ((nUnicode >> i) & 1);
		//}

		//nUTF8 <<= 1 + 1;
		//nUTF8 <<= 1;

		//for (; i < 12; i++)
		//{
		//	nUTF8 += ((nUnicode >> i) & 1);
		//	nUTF8 <<= 1;
		//}

		//nUTF8 <<= 1 + 1;
		//nUTF8 <<= 1;

		//for (; i < 16; i++)
		//{
		//	nUTF8 += ((nUnicode >> i) & 1);
		//	nUTF8 <<= 1;
		//}

		//nUTF8 <<= 1 + 1;
		//nUTF8 <<= 1 + 1;
		//nUTF8 <<= 1 + 1;
	}
	else if (nUnicode <= 0x10ffff)
	{
		for (int i = 0; i < 21; i++)
		{
			str.AppendFormat(_T("%s%d "), (nUnicode >> i) & 1);
		}
	}

	nUnicode = nUTF8;
}

void CChnTranslateDlg::OnBnClickedButtonUtf8()
{
	UpdateData(TRUE);
	int nLenth = m_csInput.GetLength();
	m_csOutput.Empty();

	for (int i = 0; i < nLenth; i++)
	{
		TRACE("a%d\n", m_csInput.GetAt(i));
		int n = m_csInput.GetAt(i);
		ConvertUnicodeToUTF8(n);
		m_csOutput.Format(_T("%X"), n);
	}

	UpdateData(FALSE);
}
