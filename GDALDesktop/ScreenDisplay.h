#pragma once
class DisplayTransformation;
class ScreenDisplay
{
public:
	ScreenDisplay(void);
	~ScreenDisplay(void);
public:
	HDC hdc;
	Color mColorSet;
	double Width;
	DisplayTransformation* mDisplayTransformation;
	void SetSymbol(Color mColor,int width);

	void DrawPolyline();
	void DrawPoint(OGRPoint* unitPt);
};

