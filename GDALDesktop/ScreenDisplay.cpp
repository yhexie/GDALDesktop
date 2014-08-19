#include "StdAfx.h"
#include "ScreenDisplay.h"
#include "DisplayTransformation.h"

ScreenDisplay::ScreenDisplay(void)
{
	mDisplayTransformation=new DisplayTransformation;
	mColorSet=Color::Red;
}
void ScreenDisplay::SetSymbol(Color mColor,int width)
{
	mColorSet=mColor;
	Width=width;
}
void ScreenDisplay::DrawPolyline()
{
	
}

ScreenDisplay::~ScreenDisplay(void)
{
}

void ScreenDisplay::DrawPoint(OGRPoint* unitPt)
{
	PointF* pt=mDisplayTransformation->ToScreen(unitPt);
	Graphics g(hdc);
	//��������
	
	Pen pen_black(mColorSet);
	Pen pen_white(Color::White);

	//ʹ�û��ʻ���ͼ��
	pen_black.SetWidth(Width); //���û��ʿ��
	pen_black.SetStartCap(LineCapRoundAnchor); //���ÿ�ʼ��ñ
	pen_black.SetEndCap(LineCapRoundAnchor); //���ý�����ñ 
	//pen_black.SetEndCap(LineCapArrowAnchor); //���ý�����ñ 
	PointF pt2(pt->X+10,pt->Y);
	g.DrawLine(&pen_black,*pt,pt2);

}
