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
	//建立画笔
	
	Pen pen_black(mColorSet);
	Pen pen_white(Color::White);

	//使用画笔绘制图形
	pen_black.SetWidth(Width); //设置画笔宽度
	pen_black.SetStartCap(LineCapRoundAnchor); //设置开始笔帽
	pen_black.SetEndCap(LineCapRoundAnchor); //设置结束笔帽 
	//pen_black.SetEndCap(LineCapArrowAnchor); //设置结束笔帽 
	PointF pt2(pt->X+10,pt->Y);
	g.DrawLine(&pen_black,*pt,pt2);

}
