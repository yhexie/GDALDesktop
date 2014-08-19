
// GDALDesktop.h : GDALDesktop Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "Geometry.h"
using namespace RGeos::Geometry;
// CGDALDesktopApp:
// �йش����ʵ�֣������ GDALDesktop.cpp
//

class CGDALDesktopApp : public CWinAppEx
{
public:
	CGDALDesktopApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileNew();
private :
	bool CreateShapeFile(const char * shpfile,RgPolygon *polygon);
	  ULONG_PTR           gdiplusToken;
};

extern CGDALDesktopApp theApp;
