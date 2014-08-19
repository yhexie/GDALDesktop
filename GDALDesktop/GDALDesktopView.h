
// GDALDesktopView.h : CGDALDesktopView ��Ľӿ�
//

#pragma once

class Layer;
class ScreenDisplay;
class CGDALDesktopView : public CView
{
protected: // �������л�����
	CGDALDesktopView();
	DECLARE_DYNCREATE(CGDALDesktopView)

// ����
public:
	CGDALDesktopDoc* GetDocument() const;

// ����
public:
	vector<Layer*> mLayers;
	ScreenDisplay* mScreenDisplay;
	Layer* lyr;
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CGDALDesktopView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // GDALDesktopView.cpp �еĵ��԰汾
inline CGDALDesktopDoc* CGDALDesktopView::GetDocument() const
   { return reinterpret_cast<CGDALDesktopDoc*>(m_pDocument); }
#endif

