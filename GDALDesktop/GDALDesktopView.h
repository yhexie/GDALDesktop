
// GDALDesktopView.h : CGDALDesktopView 类的接口
//

#pragma once

class Layer;
class ScreenDisplay;
class CGDALDesktopView : public CView
{
protected: // 仅从序列化创建
	CGDALDesktopView();
	DECLARE_DYNCREATE(CGDALDesktopView)

// 特性
public:
	CGDALDesktopDoc* GetDocument() const;

// 操作
public:
	vector<Layer*> mLayers;
	ScreenDisplay* mScreenDisplay;
	Layer* lyr;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGDALDesktopView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnFileSave();
	afx_msg void OnZoomin();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // GDALDesktopView.cpp 中的调试版本
inline CGDALDesktopDoc* CGDALDesktopView::GetDocument() const
   { return reinterpret_cast<CGDALDesktopDoc*>(m_pDocument); }
#endif

