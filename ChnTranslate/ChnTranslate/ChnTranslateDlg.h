
// ChnTranslateDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CChnTranslateDlg �Ի���
class CChnTranslateDlg : public CDialogEx
{
// ����
public:
	CChnTranslateDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHNTRANSLATE_DIALOG };

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
	CEdit m_editInput;
	CEdit m_editOutput;
	CButton m_btnUnicode;
	CButton m_btnUtf8;
	CButton m_btnGBK;
	CButton m_btnGB2312;
	afx_msg void OnBnClickedButtonUnicode();
	CString m_csInput;
	CString m_csOutput;
	afx_msg void OnBnClickedButtonUtf8();
};
