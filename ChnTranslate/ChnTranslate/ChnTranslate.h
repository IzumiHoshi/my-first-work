
// ChnTranslate.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CChnTranslateApp: 
// �йش����ʵ�֣������ ChnTranslate.cpp
//

class CChnTranslateApp : public CWinApp
{
public:
	CChnTranslateApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CChnTranslateApp theApp;