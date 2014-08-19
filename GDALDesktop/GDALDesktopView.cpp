
// GDALDesktopView.cpp : CGDALDesktopView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CGDALDesktopView ����/����

CGDALDesktopView::CGDALDesktopView()
{
	// TODO: �ڴ˴���ӹ������
	mScreenDisplay=new ScreenDisplay;
	mScreenDisplay->mDisplayTransformation->Zoom = 1.0f;
	lyr= new RgFeatureLayer;
	lyr->ShapeType=0;
	string name("Point");//˼��name������������
	lyr->setLayerName(&name);
	mLayers.push_back(lyr);
}

CGDALDesktopView::~CGDALDesktopView()
{
	delete mScreenDisplay;
}

BOOL CGDALDesktopView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGDALDesktopView ����

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

	for(vector<Layer*>::iterator it =first; it !=mLayers.end() ; it++) ///�ڶ��ֵ��÷���  
	{
		Layer *lyr=*it;
		lyr->Draw(mScreenDisplay);
	} 
	
	//Graphics graphics(*pDC);
	Graphics g( pDC->GetSafeHdc() );
	//��������
	 Pen pen_black(Color::Black);
	 Pen pen_white(Color::White);

	//ʹ�û��ʻ���ͼ��
	pen_black.SetWidth(6); //���û��ʿ��
	pen_black.SetStartCap(LineCapRoundAnchor); //���ÿ�ʼ��ñ
	pen_black.SetEndCap(LineCapArrowAnchor); //���ý�����ñ 
	g.DrawLine(&pen_black, 10, 10, 100, 10);
	Rect rect1(0,0, 150, 80);
	Rect rect2(10 + 170, 200, 150, 80);
	Rect rect3(10 + 170*2, 200, 150, 80);
	Rect rect4(10 + 170*3, 200, 150, 80);
	g.DrawRectangle(&pen_black, rect1);
	 g.DrawRectangle(&pen_black, rect2);
	 g.DrawRectangle(&pen_black, rect3);
	 g.DrawRectangle(&pen_black, rect4);
	//������ˢ
	 //ʵɫ��ˢ
	SolidBrush brush_black(Color::Black);
	 SolidBrush brush_white(Color::White);
	 SolidBrush brush_blue(Color::Blue);
	 g.FillRectangle(&brush_blue, rect1);
	 //����ˢ
	 HatchBrush brush_hatch( HatchStyleDiagonalBrick, Color(255, 255, 0, 0), Color(30, 0, 255, 0)); 
	g.FillRectangle(&brush_hatch, rect2);
	 //��ͼ��ˢ
	 Image image(L"res\\qq.gif"); 
	 TextureBrush brush_texture(&image); 
	 g.FillRectangle(&brush_texture, rect3);
	 //���仭ˢ(���ν���)
	 LinearGradientBrush brush_gradient_line( Point(0, 0), Point(10, 10),Color(255, 255, 0, 0), Color(255, 0, 0, 255));
	 g.FillRectangle(&brush_gradient_line, rect4);
	 //���仭ˢ(·������)
	 //PathGradientBrush......................
	//��ͼ����
	 Pen pen_texture(&brush_texture, 30);
	g.DrawEllipse(&pen_texture, 600, 10, 150 ,150);
	//��������ݹ���
	 pen_black.SetWidth(1);
	 g.SetSmoothingMode(SmoothingModeAntiAlias);
	 g.DrawLine(&pen_black, 150, 5, 350 , 20); 
	//����ͼ��
	// ����������
	 g.DrawImage(&image, 10,50);
	 // ʹ�õ������Ĳ岹�㷨
	 g.SetInterpolationMode(InterpolationModeNearestNeighbor);
	 g.DrawImage( &image, Rect(100,50, 100, 100));
	 // ʹ���е������Ĳ岹�㷨
	 g.SetInterpolationMode(InterpolationModeHighQualityBilinear);
	 g.DrawImage( &image, Rect(250,50, 100, 100));
	 // ʹ�ø������Ĳ岹�㷨
	 g.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	 g.DrawImage( &image, Rect(400,50, 100, 100)); 
	//·��
	GraphicsPath path1;
	path1.AddLine(300, 350, 500 ,350);
	path1.AddArc(300, 300, 200, 100, 0, -180);
	g.DrawPath(&pen_black, &path1);
	g.FillPath(&brush_black, &path1);
	//����
	GraphicsPath pathOuter;
	pathOuter.AddRectangle(Rect(100, 320, 150 ,150));
	GraphicsPath pathInner;
	 pathInner.AddEllipse(Rect(150, 360, 90 ,80));
	 Region rgn(&pathOuter);
	 rgn.Exclude(&pathInner);
	g.FillRegion(&brush_blue, &rgn);
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CGDALDesktopView ��ӡ


void CGDALDesktopView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGDALDesktopView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGDALDesktopView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGDALDesktopView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CGDALDesktopView ���

#ifdef _DEBUG
void CGDALDesktopView::AssertValid() const
{
	CView::AssertValid();
}

void CGDALDesktopView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDALDesktopDoc* CGDALDesktopView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDALDesktopDoc)));
	return (CGDALDesktopDoc*)m_pDocument;
}
#endif //_DEBUG


// CGDALDesktopView ��Ϣ�������


void CGDALDesktopView::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnClose();
}


void CGDALDesktopView::OnFileSave()
{
	// TODO: �ڴ���������������
//	AfxMessageBox(L"Hello");
}


void CGDALDesktopView::OnZoomin()
{
	// TODO: �ڴ���������������
}


void CGDALDesktopView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CView::OnLButtonDblClk(nFlags, point);
}


void CGDALDesktopView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnLButtonUp(nFlags, point);
}


void CGDALDesktopView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMainFrame *pFrame=(CMainFrame*)GetParent();
	CMFCStatusBar *pStatus=&pFrame->m_wndStatusBar;
	OGRPoint* utPoint=	mScreenDisplay->mDisplayTransformation->ToUnit(new PointF(point.x,point.y));
	
	CString cs;
	cs.Format(L"%f",utPoint->getX());
	CString csY;
	csY.Format(L"%f",utPoint->getY());
	cs.Append(L",");
	cs.Append(csY);
	cs.Append(L"����");
	//cs.Append(L"%f",utPoint->getY());
	LPCTSTR b=cs;
	pStatus->SetWindowTextW(b);
	//CMainFrame *pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;//Ҫ�����MainFrm.hͷ�ļ�
 //   CStatusBar *pStatus=&pFrame->m_wndStatusBar;//��Ҫ��m_wndStatusBar�����޸�Ϊ����
	CView::OnMouseMove(nFlags, point);
}
