
// GDALDesktop.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "GDALDesktop.h"
#include "MainFrm.h"

#include "GDALDesktopDoc.h"
#include "GDALDesktopView.h"
#include "FrmCreateNewShp.h"
#include "Geometry.h"
#include "ShapeLib.h"
using namespace RGeos::Geometry;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
bool DeleteShapeFile(const char * shpfile);

// CGDALDesktopApp

BEGIN_MESSAGE_MAP(CGDALDesktopApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CGDALDesktopApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_NEW, &CGDALDesktopApp::OnFileNew)
END_MESSAGE_MAP()


// CGDALDesktopApp ����

CGDALDesktopApp::CGDALDesktopApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("GDALDesktop.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CGDALDesktopApp ����

CGDALDesktopApp theApp;


// CGDALDesktopApp ��ʼ��

BOOL CGDALDesktopApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGDALDesktopDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CGDALDesktopView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	 GdiplusStartupInput gdiplusStartupInput;
   
	 GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	return TRUE;
}

int CGDALDesktopApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);
	 GdiplusShutdown(gdiplusToken);
	return CWinAppEx::ExitInstance();
}

// CGDALDesktopApp ��Ϣ�������


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
#define LOG(S,L) _Log(S,L)

// �������жԻ����Ӧ�ó�������
void CGDALDesktopApp::OnAppAbout()
{
	/*CAboutDlg aboutDlg;
	aboutDlg.DoModal();*/

	//FrmCreateNewShp frm;
	//frm.SetWindowTextW(L"Hello");
	//frm.DoModal();

	const char* shpfile="d:\\test.shp";
	RgPolygon * polygon=new RgPolygon();

	RgPointF * point1=new RgPointF();
	point1->SetX(112.131809830557);
	point1->SetY(32.0483506612508);
	polygon->AddTail(*point1);

	RgPointF * point2=new RgPointF();
	point2->SetX(112.138161906485);
	point2->SetY(32.0483506612508);
	polygon->AddTail(*point2);

	RgPointF * point3=new RgPointF();
	point3->SetX(112.138161906485);
	point3->SetY(32.0425415853617);
	polygon->AddTail(*point3);

	RgPointF * point4=new RgPointF();
	point4->SetX(112.131809830557);
	point4->SetY(32.0425415853617);
	polygon->AddTail(*point4);

	RgPointF * point5=new RgPointF();
	point5->SetX(112.131809830557);
	point5->SetY(32.0483506612508);
	polygon->AddTail(*point1);

	CShapeLib *shp=new CShapeLib;
	bool flag=shp->CreateShapeFileA(shpfile,polygon);
	if(flag)
	{
		AfxMessageBox(L"OK");
	}
	delete shp;
	shp=NULL;
	delete polygon;
	/*if(CreateShapeFile(shpfile,polygon))
	{
		AfxMessageBox(L"OK");
	}*/

}

// CGDALDesktopApp �Զ������/���淽��

void CGDALDesktopApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CGDALDesktopApp::LoadCustomState()
{
}

void CGDALDesktopApp::SaveCustomState()
{
}

// CGDALDesktopApp ��Ϣ�������

void CGDALDesktopApp::OnFileNew()
{
	
	
}

void _Log(string info,int line)
{
	//return;
	string strDstTfwFilePath = "D:\\TilesEngine.log";
	FILE *fileDstTfw = fopen(strDstTfwFilePath.c_str(), "a+" );
	if(!fileDstTfw)
	{
		return;
	}

	fprintf( fileDstTfw, "line��%d-----%s\r\n", line,info.c_str());

	fclose(fileDstTfw);
	
};

bool CGDALDesktopApp:: CreateShapeFile(const char * shpfile,RgPolygon *polygon)
{
	DeleteShapeFile(shpfile);
	LOG("-->ɾ����Shape�ļ��ɹ���", __LINE__);

	const char *pszDriverName = "ESRI Shapefile";  
  
	// Ϊ��֧������·�������������������
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");   //����֧������·��
    // Ϊ��ʹ���Ա��ֶ�֧�����ģ�������������
    CPLSetConfigOption("SHAPE_ENCODING","");
	
    OGRRegisterAll();  
  
	LOG("-->OGRRegisterAll(),", __LINE__);

	OGRSFDriver *poDriver;  
	OGRSFDriverRegistrar* registrar=OGRSFDriverRegistrar::GetRegistrar();
    poDriver =registrar ->GetDriverByName(pszDriverName);  
	LOG("-->poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(pszDriverName); ", __LINE__);
    if (poDriver == NULL)  
    {  
		return false;
	}  
  
    OGRDataSource *poDS;  
    poDS = poDriver->CreateDataSource(shpfile, NULL);  
	LOG("-->poDS = poDriver->CreateDataSource(shpfile, NULL);  ,", __LINE__);
    if (poDS == NULL)  
    {  
		return false; 
    }  
	LOG("-->����Shape�ļ��ɹ�,", __LINE__);
	

    OGRLayer *poLayer;  
	// ������֪��ͶӰ��Ϣ
	OGRSpatialReference *poSrcSRS=new OGRSpatialReference();
	char *pszSrcWkt = NULL;
	 
	/*oSrcSRS.SetWellKnownGeogCS("WGS84");  
	oSrcSRS.exportToWkt(&pszSrcWkt);*/

	const char * prj = "PROJCS[\"Popular Visualisation CRS / Mercator\",GEOGCS[\"Popular Visualisation CRS\",DATUM[\"Popular_Visualisation_Datum\",SPHEROID[\"Popular_Visualisation_Sphere\",6378137.0,0.0]],PRIMEM[\"Greenwich\",0.0],UNIT[\"Degree\",0.0174532925199433]],PROJECTION[\"Mercator_1SP\"],PARAMETER[\"false_easting\",0.0],PARAMETER[\"false_northing\",0.0],PARAMETER[\"central_meridian\",0.0],PARAMETER[\"scale_factor\",1.0],UNIT[\"Meter\",1.0]]";
	poSrcSRS->SetFromUserInput(prj);

	LOG("-->poSrcSRS->SetFromUserInput(prj); ,", __LINE__);
	//CPLErr err;	
	//err = GDALSetProjection((OGRDataSourceH)poDS, pszSrcWkt);
	//OGRFree(pszSrcWkt);
	//if (err != CE_None)
	//{
	//	return false;
	//}

	LOG("-->��ʼ����Shape�㣬", __LINE__);

	poLayer = poDS->CreateLayer("polygon1", poSrcSRS, wkbPolygon, NULL);  

    if (poLayer == NULL)  
    {  
	    LOG("-->����Shape��ʧ�ܣ�", __LINE__);
		return false;
    }  
	LOG("-->����Shape��ɹ���", __LINE__);
    //���洴�����Ա�  
    OGRFieldDefn poFieldID("ID", OFTInteger);//����ID�ֶ�  
    poLayer->CreateField(&poFieldID);  
  
    OGRFieldDefn poFieldname("Name", OFTString);//����Name�ֶ�  
    poFieldname.SetWidth(32);  
    poLayer->CreateField(&poFieldname);  
  
	OGRLinearRing *pRing=new OGRLinearRing();  

	OGRFeature *poFeature;  

	string szname = "a_1";  
        
    poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );  

    poFeature->SetField(0, 1);  
    poFeature->SetField(1, szname.c_str());  

    for (int i  = 0; i < polygon->GetCount(); i++)  
    {  
  
		RgPointF p=polygon->GetAt(i);
		pRing->addPoint(p.GetX(), p.GetY());  

		//delete pp;
        
    }  
  
	pRing->closeRings();//��β���غ��γɱպϻ�  
          
    OGRPolygon *pogrpolygon=new OGRPolygon();  
    pogrpolygon->addRing(pRing);  
    poFeature->SetGeometry(pogrpolygon);  

    if ( poLayer->CreateFeature( poFeature) != OGRERR_NONE)  
    {  
		return false;
    }  
    OGRFeature::DestroyFeature(poFeature);  

    OGRDataSource::DestroyDataSource(poDS); 

	OGRCleanupAll();
	//registrar->~OGRSFDriverRegistrar();

	LOG("--����Shape�ļ��ɹ���", __LINE__);
	return true;
}

bool DeleteShapeFile(const char * shpfile)
{
	bool result=true;

	string strShpFile(shpfile);

	int pos = strShpFile.find_last_of('.');

	if(access(shpfile,0) != -1)
	{
		if(remove(shpfile)!=0)
		{
			result=false;
		}
	}

	string strDbfFile=strShpFile.substr(0,pos) + ".dbf";

	if(access(strDbfFile.c_str(),0) != -1)
	{
		if(remove(strDbfFile.c_str())!=0)
		{
			result=false;
		}
	}

	string strPrjFile=strShpFile.substr(0,pos) + ".prj";

	if(access(strPrjFile.c_str(),0) != -1)
	{
		if(remove(strPrjFile.c_str())!=0)
		{
			result=false;
		}
	}


	string strShxFile=strShpFile.substr(0,pos) + ".shx";

	if(access(strShxFile.c_str(),0) != -1)
	{
		if(remove(strShxFile.c_str())!=0)
		{
			result=false;
		}
	}
	return result;
}
