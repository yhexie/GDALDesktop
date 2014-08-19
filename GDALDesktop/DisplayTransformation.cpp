#include "StdAfx.h"
#include "DisplayTransformation.h"
#include "RgeosUnits.h"

DisplayTransformation::DisplayTransformation(void)
{
	  Zoom = 1.0f;
	 // mUnits = RgUnknownUnits;
	  mUnits = RgMillimeters;
	  m_panOffset = new PointF(0, 0);
	  m_dragOffset = new PointF(0, 0);
}

DisplayTransformation::~DisplayTransformation(void)
{
	if(m_panOffset!=NULL)
	{
		delete m_panOffset;
		m_panOffset=NULL;
	}
	if(m_dragOffset!=NULL)
	{
		delete m_dragOffset;
		m_dragOffset=NULL;
	}
}

RgEnvelope  DisplayTransformation::getVisibleBounds()
{
    if (!mDeviceFrame.IsEmptyArea())
    {
        OGRPoint* lowLeft = ToUnit( PointF(mDeviceFrame.GetLeft(), mDeviceFrame.GetBottom()));
        OGRPoint* upRight = ToUnit( PointF(mDeviceFrame.GetRight(), mDeviceFrame.GetTop()));
        mVisibleBounds = RgEnvelope();
		mVisibleBounds.MinX=lowLeft->getX();
		mVisibleBounds.MinY=lowLeft->getY();
		mVisibleBounds.MaxX=upRight->getX();
		mVisibleBounds.MaxY=upRight->getY();
        return mVisibleBounds;
    }
}

void  DisplayTransformation::setVisibleBounds(RgEnvelope value)
{
    mVisibleBounds = value;
}
/// <summary>
/// һ�������ڵ�ǰ���ű����´���ĵ�ͼ�ߴ�
/// </summary>
double DisplayTransformation::getPixelSize()
{
    return mVisibleBounds.GetWidth() / mDeviceFrame.Width; 
           
}

double  DisplayTransformation::getPixelWidth()
{
	double PixelSize=getPixelSize();
    return PixelSize; 
}

double   DisplayTransformation::getPixelHeight()
{
	double PixelSize=getPixelSize();
    return PixelSize; 
}

//�豸�Ŀɼ���Χ.
//The DeviceFrame is normally the full extent of the device with the origin equal to (0, 0).  
Rect  DisplayTransformation::getDeviceFrame()
{
    return mDeviceFrame;
}

 void DisplayTransformation:: setDeviceFrame(Rect value)
{
     if (!mDeviceFrame.Equals( value))
     {
        mDeviceFrame = value;
     }
}

PointF* DisplayTransformation:: ToScreen(OGRPoint pt)
{
	float ratio = GetRatio(mUnits);
	PointF *transformedPoint = new PointF((float)pt.getX(), (float)pt.getY());
	transformedPoint->Y = ScreenHeight() - transformedPoint->Y;//��Unit����ϵת��Ϊ��Ļ����ϵ��Y�ᷴ�򣬴�ʱY����Ϊ��Ļ����ϵ����
	transformedPoint->Y *= ratio * Zoom;//�������Ļԭ��Ŵ�
	transformedPoint->X *= ratio * Zoom;

	transformedPoint->X += m_panOffset->X + m_dragOffset->X;
	transformedPoint->Y += m_panOffset->Y + m_dragOffset->Y;
	return transformedPoint;
}
PointF* DisplayTransformation:: ToScreen(OGRPoint* pt)
{
	float ratio = GetRatio(mUnits);
	PointF *transformedPoint = new PointF((float)pt->getX(), (float)pt->getY());
	transformedPoint->Y = ScreenHeight() - transformedPoint->Y;//��Unit����ϵת��Ϊ��Ļ����ϵ��Y�ᷴ�򣬴�ʱY����Ϊ��Ļ����ϵ����
	transformedPoint->Y *= ratio * Zoom;//�������Ļԭ��Ŵ�
	transformedPoint->X *= ratio * Zoom;

	transformedPoint->X += m_panOffset->X + m_dragOffset->X;
	transformedPoint->Y += m_panOffset->Y + m_dragOffset->Y;
	return transformedPoint;
}
float  DisplayTransformation::ScreenHeight()
{
    return (float)(ToUnit(this->mDeviceFrame.Height));
}

OGRPoint* DisplayTransformation:: ToUnit(PointF screenpoint)
{
    float ratio = GetRatio(mUnits);
    float panoffsetX = m_panOffset->X + m_dragOffset->X;
    float panoffsetY = m_panOffset->Y + m_dragOffset->Y;
    float xpos = (screenpoint.X - panoffsetX) / (ratio * Zoom);
    float ypos = ScreenHeight() - ((screenpoint.Y - panoffsetY)) / (ratio * Zoom);
    return new OGRPoint(xpos, ypos);
}
OGRPoint* DisplayTransformation:: ToUnit(PointF* screenpoint)
{
    float ratio = GetRatio(mUnits);
    float panoffsetX = m_panOffset->X + m_dragOffset->X;
    float panoffsetY = m_panOffset->Y + m_dragOffset->Y;
    float xpos = (screenpoint->X - panoffsetX) / (ratio * Zoom);
    float ypos = ScreenHeight() - ((screenpoint->Y - panoffsetY)) / (ratio * Zoom);
    return  new OGRPoint(xpos, ypos);
}
//����Ļ�������ΪZoom�ȼ��µĵ�ͼ����
double DisplayTransformation:: ToUnit(float screenvalue)
{
    float ratio = GetRatio(mUnits);
    return (double)screenvalue / (double)(ratio * Zoom);
}

//��λ����Ӣ�硪������
float DisplayTransformation:: GetRatio(RgeosUnits units)
{
            float ratio = 1;
            switch (units)
            {
                case RgInches://Inches.
                    ratio = m_screenResolution;
                    break;
                case RgPoints:// Points. 
                    ratio = 1;
                    break;
                case RgMillimeters:// Millimeters.
                    ratio = (float)(m_screenResolution / MillmeteresPerInch);
                    break;
                case RgCentimeters: //Centimeters. 
                    ratio = (float)(m_screenResolution / MillmeteresPerInch * 10);
                    break;
                case RgMeters://Meters. 
                    ratio = (float)(m_screenResolution / MillmeteresPerInch * 1000);
                    break;
                case RgKilometers:// Kilometers. 
                    ratio = (float)(m_screenResolution / MillmeteresPerInch * 1000000);
                    break;
                case RgDecimalDegrees:// Decimal degrees. 
                case RgDecimeters:// Decimeters. 
                case RgUnitsLast:
                case RgFeet: //Feet. 
                case RgYards:// Yards. 
                case RgMiles://Miles. 
                case RgNauticalMiles: //Nautical miles. 
                case RgUnknownUnits:
                    ratio = 1;
                    break;
                default:
                    ratio = 1;
                    break;
            }
            return ratio;

}
