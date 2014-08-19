
// GDALDesktop.cpp : 定义应用程序的类行为。
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
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_NEW, &CGDALDesktopApp::OnFileNew)
END_MESSAGE_MAP()


// CGDALDesktopApp 构造

CGDALDesktopApp::CGDALDesktopApp()
{
	m_bHiColorIcons = TRUE;

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("GDALDesktop.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CGDALDesktopApp 对象

CGDALDesktopApp theApp;


// CGDALDesktopApp 初始化

BOOL CGDALDesktopApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGDALDesktopDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CGDALDesktopView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
	 GdiplusStartupInput gdiplusStartupInput;
   
	 GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	return TRUE;
}

int CGDALDesktopApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);
	 GdiplusShutdown(gdiplusToken);
	return CWinAppEx::ExitInstance();
}

// CGDALDesktopApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

// 用于运行对话框的应用程序命令
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

// CGDALDesktopApp 自定义加载/保存方法

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

// CGDALDesktopApp 消息处理程序

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

	fprintf( fileDstTfw, "line：%d-----%s\r\n", line,info.c_str());

	fclose(fileDstTfw);
	
};

bool CGDALDesktopApp:: CreateShapeFile(const char * shpfile,RgPolygon *polygon)
{
	DeleteShapeFile(shpfile);
	LOG("-->删除旧Shape文件成功，", __LINE__);

	const char *pszDriverName = "ESRI Shapefile";  
  
	// 为了支持中文路径，请添加下面这句代码
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");   //设置支持中文路径
    // 为了使属性表字段支持中文，请添加下面这句
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
	LOG("-->创建Shape文件成功,", __LINE__);
	

    OGRLayer *poLayer;  
	// 赋上已知的投影信息
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

	LOG("-->开始创建Shape层，", __LINE__);

	poLayer = poDS->CreateLayer("polygon1", poSrcSRS, wkbPolygon, NULL);  

    if (poLayer == NULL)  
    {  
	    LOG("-->创建Shape层失败！", __LINE__);
		return false;
    }  
	LOG("-->创建Shape层成功，", __LINE__);
    //下面创建属性表  
    OGRFieldDefn poFieldID("ID", OFTInteger);//创建ID字段  
    poLayer->CreateField(&poFieldID);  
  
    OGRFieldDefn poFieldname("Name", OFTString);//创建Name字段  
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
  
	pRing->closeRings();//首尾点重合形成闭合环  
          
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

	LOG("--生成Shape文件成功，", __LINE__);
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
