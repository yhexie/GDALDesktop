#pragma once
#include "RgeosUnits.h"
#include "RgEnvelope.h"
static const  float m_screenResolution = 96;
static const  double MillmeteresPerInch = 25.4;
class DisplayTransformation
{
public:
	DisplayTransformation(void);
	~DisplayTransformation(void);
	
public:	
	float Zoom;
	RgeosUnits mUnits ;
	PointF* m_panOffset;
	PointF *m_dragOffset;
	Rect mDeviceFrame;

	RgEnvelope getVisibleBounds();
	Rect    getDeviceFrame();
	double     getPixelHeight();
	double    getPixelWidth();
	void setDeviceFrame(Rect value);
	void  setVisibleBounds(RgEnvelope value);
	double getPixelSize();
	PointF * ToScreen(OGRPoint pt);
	PointF*  ToScreen(OGRPoint* pt);
	OGRPoint* ToUnit(PointF screenpoint);
	OGRPoint *ToUnit(PointF* screenpoint);
	double ToUnit(float screenvalue);
private:
	
    RgEnvelope mVisibleBounds ;
	float ScreenHeight();	
	float GetRatio(RgeosUnits units);
};