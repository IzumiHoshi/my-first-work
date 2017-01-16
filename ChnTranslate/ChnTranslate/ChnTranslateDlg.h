
// ChnTranslateDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CChnTranslateDlg 对话框
class CChnTranslateDlg : public CDialogEx
{
// 构造
public:
	CChnTranslateDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHNTRANSLATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
