
// GDALDesktopView.cpp : CGDALDesktopView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GDALDesktop.h"
#endif

#include "GDALDesktopDoc.h"
#include "GDALDesktopView.h"
#include "ScreenDisplay.h"
#include "Layer.h"
#include "DisplayTransformation.h"
#include "RgFeatureLayer.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDALDesktopView

IMPLEMENT_DYNCREATE(CGDALDesktopView, CView)

BEGIN_MESSAGE_MAP(CGDALDesktopView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGDALDesktopView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CLOSE()
	ON_COMMAND(ID_FILE_SAVE, &CGDALDesktopView::OnFileSave)
	ON_COMMAND(ID_ZOOMIN, &CGDALDesktopView::OnZoomin)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CGDALDesktopView 构造/析构

CGDALDesktopView::CGDALDesktopView()
{
	// TODO: 在此处添加构造代码
	mScreenDisplay=new ScreenDisplay;
	mScreenDisplay->mDisplayTransformation->Zoom = 1.0f;
	lyr= new RgFeatureLayer;
	lyr->ShapeType=0;
	string name("Point");//思考name变量的作用域
	lyr->setLayerName(&name);
	mLayers.push_back(lyr);
}

CGDALDesktopView::~CGDALDesktopView()
{
	delete mScreenDisplay;
}

BOOL CGDALDesktopView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGDALDesktopView 绘制

void CGDALDesktopView::OnDraw(CDC* pDC)
{
	CGDALDesktopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	mScreenDisplay->hdc=pDC->GetSafeHdc();
	LPRECT rect0=new RECT;
	this->GetClientRect(rect0);
	double width=abs(rect0->right-rect0->left);
	double height=abs(rect0->top-rect0->bottom);
	Rect rect(rect0->left,rect0->top,width,height);
	mScreenDisplay->mDisplayTransformation->setDeviceFrame(rect);
	
	vector<Layer*>::iterator first=mLayers.begin();

	for(vector<Layer*>::iterator it =first; it !=mLayers.end() ; it++) ///第二种调用方法  
	{
		Layer *lyr=*it;
		lyr->Draw(mScreenDisplay);
	} 
	
	//Graphics graphics(*pDC);
	Graphics g( pDC->GetSafeHdc() );
	//建立画笔
	 Pen pen_black(Color::Black);
	 Pen pen_white(Color::White);

	//使用画笔绘制图形
	pen_black.SetWidth(6); //设置画笔宽度
	pen_black.SetStartCap(LineCapRoundAnchor); //设置开始笔帽
	pen_black.SetEndCap(LineCapArrowAnchor); //设置结束笔帽 
	g.DrawLine(&pen_black, 10, 10, 100, 10);
	Rect rect1(0,0, 150, 80);
	Rect rect2(10 + 170, 200, 150, 80);
	Rect rect3(10 + 170*2, 200, 150, 80);
	Rect rect4(10 + 170*3, 200, 150, 80);
	g.DrawRectangle(&pen_black, rect1);
	 g.DrawRectangle(&pen_black, rect2);
	 g.DrawRectangle(&pen_black, rect3);
	 g.DrawRectangle(&pen_black, rect4);
	//建立画刷
	 //实色画刷
	SolidBrush brush_black(Color::Black);
	 SolidBrush brush_white(Color::White);
	 SolidBrush brush_blue(Color::Blue);
	 g.FillRectangle(&brush_blue, rect1);
	 //网格画刷
	 HatchBrush brush_hatch( HatchStyleDiagonalBrick, Color(255, 255, 0, 0), Color(30, 0, 255, 0)); 
	g.FillRectangle(&brush_hatch, rect2);
	 //贴图画刷
	 Image image(L"res\\qq.gif"); 
	 TextureBrush brush_texture(&image); 
	 g.FillRectangle(&brush_texture, rect3);
	 //渐变画刷(线形渐变)
	 LinearGradientBrush brush_gradient_line( Point(0, 0), Point(10, 10),Color(255, 255, 0, 0), Color(255, 0, 0, 255));
	 g.FillRectangle(&brush_gradient_line, rect4);
	 //渐变画刷(路径渐变)
	 //PathGradientBrush......................
	//贴图画笔
	 Pen pen_texture(&brush_texture, 30);
	g.DrawEllipse(&pen_texture, 600, 10, 150 ,150);
	//启动抗锯齿功能
	 pen_black.SetWidth(1);
	 g.SetSmoothingMode(SmoothingModeAntiAlias);
	 g.DrawLine(&pen_black, 150, 5, 350 , 20); 
	//绘制图像
	// 不进行缩放
	 g.DrawImage(&image, 10,50);
	 // 使用低质量的插补算法
	 g.SetInterpolationMode(InterpolationModeNearestNeighbor);
	 g.DrawImage( &image, Rect(100,50, 100, 100));
	 // 使用中等质量的插补算法
	 g.SetInterpolationMode(InterpolationModeHighQualityBilinear);
	 g.DrawImage( &image, Rect(250,50, 100, 100));
	 // 使用高质量的插补算法
	 g.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	 g.DrawImage( &image, Rect(400,50, 100, 100)); 
	//路径
	GraphicsPath path1;
	path1.AddLine(300, 350, 500 ,350);
	path1.AddArc(300, 300, 200, 100, 0, -180);
	g.DrawPath(&pen_black, &path1);
	g.FillPath(&brush_black, &path1);
	//区域
	GraphicsPath pathOuter;
	pathOuter.AddRectangle(Rect(100, 320, 150 ,150));
	GraphicsPath pathInner;
	 pathInner.AddEllipse(Rect(150, 360, 90 ,80));
	 Region rgn(&pathOuter);
	 rgn.Exclude(&pathInner);
	g.FillRegion(&brush_blue, &rgn);
	// TODO: 在此处为本机数据添加绘制代码
}


// CGDALDesktopView 打印


void CGDALDesktopView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGDALDesktopView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGDALDesktopView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGDALDesktopView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CGDALDesktopView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGDALDesktopView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGDALDesktopView 诊断

#ifdef _DEBUG
void CGDALDesktopView::AssertValid() const
{
	CView::AssertValid();
}

void CGDALDesktopView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDALDesktopDoc* CGDALDesktopView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDALDesktopDoc)));
	return (CGDALDesktopDoc*)m_pDocument;
}
#endif //_DEBUG


// CGDALDesktopView 消息处理程序


void CGDALDesktopView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnClose();
}


void CGDALDesktopView::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
//	AfxMessageBox(L"Hello");
}


void CGDALDesktopView::OnZoomin()
{
	// TODO: 在此添加命令处理程序代码
}


void CGDALDesktopView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CView::OnLButtonDblClk(nFlags, point);
}


void CGDALDesktopView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	OGRPoint* pt=this->mScreenDisplay->mDisplayTransformation->ToUnit(new PointF(point.x,point.y));
	RgFeatureLayer* featLyr=dynamic_cast<RgFeatureLayer*>(lyr);
	OGRPoint* refPt=pt;
	OGRGeometry* geo=refPt;
	featLyr->AddShape(geo);
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void CGDALDesktopView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonUp(nFlags, point);
}


void CGDALDesktopView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMainFrame *pFrame=(CMainFrame*)GetParent();
	CMFCStatusBar *pStatus=&pFrame->m_wndStatusBar;
	OGRPoint* utPoint=	mScreenDisplay->mDisplayTransformation->ToUnit(new PointF(point.x,point.y));
	
	CString cs;
	cs.Format(L"%f",utPoint->getX());
	CString csY;
	csY.Format(L"%f",utPoint->getY());
	cs.Append(L",");
	cs.Append(csY);
	cs.Append(L"毫米");
	//cs.Append(L"%f",utPoint->getY());
	LPCTSTR b=cs;
	pStatus->SetWindowTextW(b);
	//CMainFrame *pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;//要求包含MainFrm.h头文件
 //   CStatusBar *pStatus=&pFrame->m_wndStatusBar;//需要将m_wndStatusBar属性修改为公有
	CView::OnMouseMove(nFlags, point);
}
