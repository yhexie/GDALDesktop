#pragma once
#include "afxwin.h"


// FrmCreateNewShp �Ի���

class FrmCreateNewShp : public CDialogEx
{
	DECLARE_DYNAMIC(FrmCreateNewShp)

public:
	FrmCreateNewShp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FrmCreateNewShp();

// �Ի�������
	enum { IDD = IDD_DLG_CREATEFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit FileName;
	afx_msg void OnBnClickedOk();
};
