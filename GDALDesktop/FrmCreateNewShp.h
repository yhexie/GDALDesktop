#pragma once
#include "afxwin.h"


// FrmCreateNewShp 对话框

class FrmCreateNewShp : public CDialogEx
{
	DECLARE_DYNAMIC(FrmCreateNewShp)

public:
	FrmCreateNewShp(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FrmCreateNewShp();

// 对话框数据
	enum { IDD = IDD_DLG_CREATEFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit FileName;
	afx_msg void OnBnClickedOk();
};
