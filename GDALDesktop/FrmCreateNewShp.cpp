// FrmCreateNewShp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GDALDesktop.h"
#include "FrmCreateNewShp.h"
#include "afxdialogex.h"


// FrmCreateNewShp �Ի���

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


// FrmCreateNewShp ��Ϣ�������


void FrmCreateNewShp::OnBnClickedOk()
{
	 CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("IMGӰ���ļ�(*.img)|*.img|TIFFӰ���ļ�(*.tif)|*.tif||"),AfxGetMainWnd());
	 if	(dlg.DoModal()==IDOK)
	 {

	 }
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
