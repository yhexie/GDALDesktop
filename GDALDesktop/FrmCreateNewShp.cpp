// FrmCreateNewShp.cpp : 实现文件
//

#include "stdafx.h"
#include "GDALDesktop.h"
#include "FrmCreateNewShp.h"
#include "afxdialogex.h"


// FrmCreateNewShp 对话框

IMPLEMENT_DYNAMIC(FrmCreateNewShp, CDialogEx)

FrmCreateNewShp::FrmCreateNewShp(CWnd* pParent /*=NULL*/)
	: CDialogEx(FrmCreateNewShp::IDD, pParent)
{

}

FrmCreateNewShp::~FrmCreateNewShp()
{
}

void FrmCreateNewShp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, FileName);
}


BEGIN_MESSAGE_MAP(FrmCreateNewShp, CDialogEx)
	ON_BN_CLICKED(IDOK, &FrmCreateNewShp::OnBnClickedOk)
END_MESSAGE_MAP()


// FrmCreateNewShp 消息处理程序


void FrmCreateNewShp::OnBnClickedOk()
{
	 CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("IMG影像文件(*.img)|*.img|TIFF影像文件(*.tif)|*.tif||"),AfxGetMainWnd());
	 if	(dlg.DoModal()==IDOK)
	 {

	 }
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
