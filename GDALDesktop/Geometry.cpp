#include "stdafx.h"
#include "Geometry.h"

using namespace RGeos::Geometry;
///////////********class point***********////////////////
RgPoint::RgPoint()
{
	m_nX = 0;
	m_nY = 0;
}

RgPoint::RgPoint(int nX, int nY)
{
	m_nX = nX;
	m_nY = nY;
}
RgPoint::RgPoint(RgPoint const &point)
{
	m_nX = point.m_nX;
	m_nY = point.m_nY;
}

int RgPoint::GetX()const
{
	return m_nX;
}
int RgPoint::GetY()const
{
	return m_nY;
}
void RgPoint::SetX(int nX)
{
	m_nX = nX;
}
void RgPoint::SetY(int nY)
{
	m_nY = nY;
}
bool RgPoint::operator == (RgPoint point)const
{
	if (m_nX==point.m_nX&&m_nY ==point.m_nY)
		return true;
	else return false;

}
void RgPoint::operator =(RgPoint const &point)
{
	m_nX = point.m_nX;
	m_nY = point.m_nY;
}
///////////********class Point***********////////////////
/////////********class PointF***********////////////////
RgPointF::RgPointF()
{
	m_dfX = 0.0;
	m_dfY = 0.0;
}

RgPointF::RgPointF(double dfX, double dfY)
{
	m_dfX = dfX;
	m_dfY = dfY;
}
RgPointF::RgPointF(RgPointF const &point)
{
	m_dfX = point.m_dfX;
	m_dfY = point.m_dfY;
}

bool RgPointF::operator == (RgPointF point)const
{
	if (m_dfX==point.m_dfX&&m_dfY ==point.m_dfY)
		return true;
	else return false;

}
void RgPointF::operator =(RgPointF const &point)
{
	m_dfX = point.m_dfX;
	m_dfY = point.m_dfY;
}
double RgPointF::GetX()const
{
	return m_dfX;
}
double RgPointF::GetY()const
{
	return m_dfY;
}
void RgPointF::SetX(double dfX)
{
	m_dfX = dfX;
}
void RgPointF::SetY(double dfY)
{
	m_dfY = dfY;
}
/////////////********class PointF***********////////////////
/////////////********class LineSegment***********////////////////

RgLineSegment::RgLineSegment()
{

}
RgLineSegment::RgLineSegment(RgLineSegment const &lineSegment)
{

	m_pointStart = lineSegment.m_pointStart;
	m_pointEnd = lineSegment.m_pointEnd;
}


RgLineSegment::RgLineSegment(RgPointF  pointStart, RgPointF  pointEnd)
{
	m_pointStart = pointStart;
	m_pointEnd = pointEnd;
}

void RgLineSegment::SetStartPoint(RgPointF point)
{
	m_pointStart= point;

}

void RgLineSegment::SetEndPoint(RgPointF point)
{
	m_pointEnd = point;


}

RgPointF RgLineSegment::GetStartPoint()const
{
	return m_pointStart;
}

RgPointF RgLineSegment::GetEndPoint()const
{	
	return m_pointEnd;
}
void RgLineSegment::operator =(RgLineSegment const &point)
{
	m_pointStart = point.m_pointStart;
	m_pointEnd = point.m_pointEnd;

}
/////////////********class LineSegment***********////////////////
///////////********class PointFList***********////////////////


RgPointFList::RgPointFList()
{		
}
RgPointFList::~RgPointFList()
{		
	if(!m_listPoint.empty())
	{
		m_listPoint.clear();
	}
}

RgPointFList::RgPointFList(RgPointFList const&pointlist)
{	
	for (int i = 0; i < pointlist.GetCount(); i++)
	{
		RgPointF  point =  pointlist.GetAt(i);
		m_listPoint.push_back(point);			
	}
}
int RgPointFList::GetCount()const
{
	return m_listPoint.size() ;
}


void RgPointFList::RemoveAt(int nIndex)
{
	list<RgPointF>::iterator los;
	los = m_listPoint.begin();
	for (int i = 0;i<nIndex;i++)
		los++;
	m_listPoint.erase(los);
}

void RgPointFList::Clear()
{
	m_listPoint.clear();
}

void RgPointFList::AddTail(RgPointF point)
{

	m_listPoint.push_back(point);

}

void RgPointFList::AddHead(RgPointF  point)
{
	m_listPoint.push_front(point);
}

void RgPointFList::Insert(int nIndex, RgPointF  point)
{

	list<RgPointF>::iterator los;
	los = m_listPoint.begin();
	for (int i = 0;i<nIndex;i++)
		los++;
	m_listPoint.insert(los,point);

}

RgPointF RgPointFList::GetAt(int nIndex)const
{

	list<RgPointF>::const_iterator los;

	los =m_listPoint.begin();

	for (int i=0;i<nIndex;i++)
	{
		los ++;
	}

	return *los;

}
void RgPointFList::operator = (RgPointFList const &pointList)
{
	for (int i = 0; i < pointList.GetCount(); i++)
	{
		RgPointF  point =  pointList.GetAt(i);
		m_listPoint.push_back(point);			
	}
}
/////////////********class PointFList***********////////////////
///////////********class Polygon***********////////////////


RgPolygon::RgPolygon()
{
	if(!m_listPoint.empty())
	{
		m_listPoint.clear();
	}
}
RgPolygon::~RgPolygon()
{
	if(!m_listPoint.empty())
	{
		m_listPoint.clear();
	}

}
RgPolygon::RgPolygon(RgPolygon const&polygon)
{
	for (int i = 0; i < polygon.GetCount(); i++)
	{
		RgPointF  point =  polygon.GetAt(i);
		m_listPoint.push_back(point);			
	}
}

int RgPolygon::GetCount()const
{
	return m_listPoint.size();
}	

bool RgPolygon::Contains(RgPointF const point)
{

	list<RgPointF>::const_iterator los;
	los =find(m_listPoint.begin(),m_listPoint.end(),point);
	if  ( los == m_listPoint.end( ) )
	{
		return false;
	}

	return true;
}

void RgPolygon::RemoveAt(int nIndex)
{
	list<RgPointF>::iterator los;
	los = m_listPoint.begin();
	for (int i = 0;i<nIndex;i++)
		los++;
	m_listPoint.erase(los);		
}

void RgPolygon::Clear()
{
	m_listPoint.clear();
}

void RgPolygon::AddTail(RgPointF point)
{
	m_listPoint.push_back(point);
}

void RgPolygon::AddHead(RgPointF  point)
{			
	m_listPoint.push_front(point);
}

void RgPolygon::Insert(int nIndex, RgPointF point)
{
	list<RgPointF>::iterator los;
	los = m_listPoint.begin();
	for (int i = 0;i<nIndex;i++)
		los++;
	m_listPoint.insert(los,point)	;		
}

RgPointF RgPolygon::GetAt(int nIndex)const
{

	list<RgPointF>::const_iterator los;
	los = m_listPoint.begin();
	for (int i=0;i<nIndex;i++)
	{
		los ++;
	}

	return *los;			
}


bool RgPolygon::operator == (RgPolygon polygon)const
{

	bool bEqual = true;
	list<RgPointF>::const_iterator los;
	los = m_listPoint.begin();
	if (polygon.GetCount() == m_listPoint.size())
	{
		for (int i = 0;i<polygon.GetCount();i++)
		{
			if (!(*los ==(polygon.GetAt(i))))
			{
				return false;
			}

			else continue; 

		}	
		return true;
	}
	else return false;
	return true;

}
void RgPolygon::operator = (RgPolygon const &polygon)
{
	for (int i = 0; i < polygon.GetCount(); i++)
	{
		RgPointF  point =  polygon.GetAt(i);
		m_listPoint.push_back(point);			
	}	

}
/////////////********class Polygon***********////////////////
///////////********class PolygonList***********////////////////


RgPolygonList::RgPolygonList()
{

}

RgPolygonList::~RgPolygonList()
{
	if(!m_listPolygon.empty())
	{
		for each(RgPolygon *objPolygon in m_listPolygon)
		{
			delete objPolygon;
		}

		m_listPolygon.clear();
	}

}
int RgPolygonList::GetCount()const
{
	return m_listPolygon.size();
}	

bool RgPolygonList::Contains(RGeos::Geometry::RgPolygon const poly)
{
	list<RgPolygon*>::const_iterator los;
	for(los = m_listPolygon.begin();los!=m_listPolygon.end();los++)
	{
		if((**los ==poly))
		{
			return true;
			
		}	
		else continue;	
	}
	
	
	 return false;

}

void RgPolygonList::RemoveAt(int nIndex)
{
	list<RgPolygon*>::iterator los;
	los = m_listPolygon.begin();
	for (int i = 0;i<nIndex;i++)
		los++;
	m_listPolygon.erase(los);	

}

void RgPolygonList::Clear()
{
	if(!m_listPolygon.empty())
	{
		for each(RgPolygon *objPolygon in m_listPolygon)
		{
			delete objPolygon;
		}

		m_listPolygon.clear();
	}
}

void RgPolygonList::AddTail(RGeos::Geometry::RgPolygon *poly)
{
	RGeos::Geometry::RgPolygon *objPoly = new RGeos::Geometry::RgPolygon();
	*objPoly = *poly;

	m_listPolygon.push_back(objPoly);
}

void RgPolygonList::AddHead(RGeos::Geometry::RgPolygon  *poly)
{	
	RGeos::Geometry::RgPolygon *objPoly = new RGeos::Geometry::RgPolygon();
	*objPoly = *poly;

	m_listPolygon.push_front(objPoly);
}

void RgPolygonList::Insert(int nIndex, RGeos::Geometry::RgPolygon *poly)
{
	RGeos::Geometry::RgPolygon *objPoly = new RGeos::Geometry::RgPolygon();
	*objPoly = *poly;

	list<RgPolygon*>::iterator los;
	los = m_listPolygon.begin();
	for (int i = 0;i<nIndex;i++)
		los++;
	m_listPolygon.insert(los,objPoly);		
}	
const RGeos::Geometry::RgPolygon  *RgPolygonList::GetAt(int nIndex)const
{
	list<RGeos::Geometry::RgPolygon*>::const_iterator los;
	los = m_listPolygon.begin();
	for (int i=0;i<nIndex;i++)
	{
		los ++;
	}
	return *los;
}
void RgPolygonList::operator = (RgPolygonList const &polygonList)
{
	if(!m_listPolygon.empty())
	{
		for each(RGeos::Geometry::RgPolygon *objPolygon in m_listPolygon)
		{
			delete objPolygon;
		}

		m_listPolygon.clear();
	}

	list<RGeos::Geometry::RgPolygon*>::const_iterator los;
	los =polygonList.m_listPolygon.begin();
	if(!(los==polygonList.m_listPolygon.end()))
	{
		RGeos::Geometry::RgPolygon *objPoly = new RGeos::Geometry::RgPolygon();
		*objPoly = *(*los);

		m_listPolygon.push_back(objPoly);	
		los++;
	}
}


///////////********class PolygonList***********////////////////
///////////********class Size***********////////////////

RgSize::RgSize()
{
	m_nWidth = 0;
	m_nHeight = 0;
}
RgSize::RgSize(int nWidth, int nHeight)
{
	m_nWidth=nWidth;
	m_nHeight=nHeight;

}
RgSize::RgSize(RgSize const& size)
{
	m_nWidth = size.GetWidth();
	m_nHeight = size.GetHeight();
}
int RgSize::GetWidth()const
{
	return m_nWidth;
}
int RgSize::GetHeight()const
{
	return m_nHeight;
}
void RgSize::SetWidth(int nWidth)
{
	m_nWidth = nWidth;
}
void RgSize::SetHeight(int nHeight)
{
	m_nHeight = nHeight;
}
void RgSize::operator =(RgSize const &size)
{
	m_nHeight = size.m_nHeight;
	m_nWidth = size.m_nWidth;
}
///////////********class RgSize***********////////////////

///////////********class Rectangle***********////////////////


RgRectangle::RgRectangle()
{

	m_dfUpLeftX=0.0;
	m_dfUpLeftY=0.0;
	m_dfDownRightX=0.0;
	m_dfDownRightY=0.0;

}
RgRectangle::RgRectangle(double dfUpLeftX, double dfUpLeftY, double dfDownRightX, double dfDownRightY)
{
	m_dfUpLeftX = dfUpLeftX;
	m_dfUpLeftY = dfUpLeftY;
	m_dfDownRightX = dfDownRightX;
	m_dfDownRightY = dfDownRightY;
}

RgRectangle::RgRectangle(RgPointF pointUpLeft, RgSize size)
{
	m_dfUpLeftX = pointUpLeft.GetX();
	m_dfUpLeftY = pointUpLeft.GetY();
	m_dfDownRightX = m_dfUpLeftX + size.GetWidth();
	m_dfDownRightY = m_dfUpLeftY + size.GetWidth();
}
RgRectangle::RgRectangle(RgRectangle const &rect)
{
	m_dfUpLeftX = rect.m_dfUpLeftX;
	m_dfUpLeftY = rect.m_dfUpLeftY;
	m_dfDownRightX = rect.m_dfDownRightX;
	m_dfDownRightY = rect.m_dfDownRightY;
}

double RgRectangle::GetLeft()const
{
	return m_dfUpLeftX;
}

double RgRectangle::GetRight()const
{
	return m_dfDownRightX;
}

double RgRectangle::GetTop()const
{
	return m_dfUpLeftY;
}

double RgRectangle::GetBottom()const
{
	return m_dfDownRightY;
}
void RgRectangle::SetLeft(double dfUpLeftX)
{
	m_dfUpLeftX =dfUpLeftX;
}
void RgRectangle::SetRight(double dfDownRightX)
{
	m_dfDownRightX =dfDownRightX;
}
void RgRectangle::SetTop(double dfUpLeftY)
{
	m_dfUpLeftY =dfUpLeftY;
}
void RgRectangle::SetBottom(double dfDownRightY)
{
	m_dfDownRightY =dfDownRightY;
}
void RgRectangle::operator =(RgRectangle const &rect)
{
	m_dfUpLeftX = rect.m_dfUpLeftX;
	m_dfUpLeftY = rect.m_dfUpLeftY;
	m_dfDownRightX = rect.m_dfDownRightX;
	m_dfDownRightY = rect.m_dfDownRightY;
}
///////////********class Rectangle***********////////////////
///////////********class SpatialRelation***********////////////////

RgSpatialRelation::RgSpatialRelation()
{

}	
double RgSpatialRelation::Mult(const RgPointF *pointFirst, const RgPointF *pointSecond, const RgPointF *pointThird)
{
	return ((pointFirst->GetX() - pointThird->GetX()) * (pointSecond->GetY() - pointThird->GetY()) - (pointSecond->GetX() - pointThird->GetX()) * (pointFirst->GetY() - pointThird->GetY()));
}

// point是否包含在rect中
bool RgSpatialRelation::Contains(const RgPointF *point, const RgRectangle *rect)
{
	if (point->GetX() >= rect->GetLeft() && point->GetX() <= rect->GetRight() && point->GetY() >= rect->GetBottom() && point->GetY() <= rect->GetTop())
	{
		return true;			
	}
	return false;
}

// point是否包含在poly中
bool RgSpatialRelation::Contains(const RgPointF  *point, const RgPolygon  *poly)
{
	bool bInside = false;
	double df1=0.0,df2=0.0;

	RgPointF point1;
	RgPointF point2 ;

	std::pair<double,double> U0;
	std::pair<double,double> U1;
	std::pair<double,double> P;

	point2 = poly->GetAt(poly->GetCount() - 1);

	for (int i = 0; i < poly->GetCount(); i++)
	{
		point1 = poly->GetAt(i);
		U0=std::make_pair(point1.GetX(),point1.GetY());
		U1=std::make_pair(point2.GetX(),point2.GetY());
		P=std::make_pair(point->GetX(),point->GetY());
		if((U0.second<=P.second && P.second<U1.second) || (U1.second<=P.second && P.second<U0.second))
		{
			double x=U0.first+(P.second-U0.second)*(U1.first-U0.first)/(U1.second-U0.second);
			if(x>P.first)
				bInside=!bInside;
		}

		point2 = poly->GetAt(i);
	}

	return bInside;

}

// rectSecond是否包含rectFirst
bool RgSpatialRelation::Contains(const RgRectangle *rectFirst, const RgRectangle  *rectSecond)
{
	// 判断rectFirst的四顶点是否全部包含在rectSecond中
	RgPointF *pointRFUpLeft = new RgPointF(rectFirst->GetLeft(), rectFirst->GetTop());
	RgPointF *pointRFUpRight = new RgPointF(rectFirst->GetRight(), rectFirst->GetTop());
	RgPointF *pointRFDownRight = new RgPointF(rectFirst->GetRight(), rectFirst->GetBottom());
	RgPointF *pointRFDownLeft = new RgPointF(rectFirst->GetLeft(), rectFirst->GetBottom());

	if (Contains(pointRFUpLeft, rectSecond) && Contains(pointRFUpRight, rectSecond) 
		&& Contains(pointRFDownRight, rectSecond) && Contains(pointRFDownLeft, rectSecond))
	{
		delete pointRFUpLeft;
		delete pointRFUpRight;
		delete pointRFDownRight;
		delete pointRFDownLeft;
		return true;
	}
	else
	{
		delete pointRFUpLeft;
		delete pointRFUpRight;
		delete pointRFDownRight;
		delete pointRFDownLeft;
		return false;
	}


}

// 两条线段是否相交
bool RgSpatialRelation::Intersects(const RgLineSegment *lineFirst, const RgLineSegment *lineSecond)
{
	return (max(lineFirst->GetStartPoint().GetX(), lineFirst->GetEndPoint().GetX()) >= min(lineSecond->GetStartPoint().GetX(), lineSecond->GetEndPoint().GetX())
		&& max(lineFirst->GetStartPoint().GetY(), lineFirst->GetEndPoint().GetY()) >= min(lineSecond->GetStartPoint().GetY(), lineSecond->GetEndPoint().GetY())
		&& max(lineSecond->GetStartPoint().GetX(), lineSecond->GetEndPoint().GetX()) >= min(lineFirst->GetStartPoint().GetX(), lineFirst->GetEndPoint().GetX())
		&& max(lineSecond->GetStartPoint().GetY(), lineSecond->GetEndPoint().GetY()) >= min(lineFirst->GetStartPoint().GetY(), lineFirst->GetEndPoint().GetY())
		&& Mult(&lineSecond->GetStartPoint(), &lineFirst->GetEndPoint(), &lineFirst->GetStartPoint()) * Mult(&lineFirst->GetEndPoint(), &lineSecond->GetEndPoint(), &lineFirst->GetStartPoint()) >= 0.0
		&& Mult(&lineFirst->GetStartPoint(), &lineSecond->GetEndPoint(), &lineSecond->GetStartPoint()) * Mult(&lineSecond->GetEndPoint(), &lineFirst->GetEndPoint(), &lineSecond->GetStartPoint()) >= 0.0);
}

// 两个rect是否相交，该相交包括其中一个包含另一个的情况
bool RgSpatialRelation::Intersects(const RgRectangle  *rectFirst, const RgRectangle  *rectSecond)
{
	// 判断rectFirst的四顶点是否包含在rectSecond中
	RgPointF  pointRFUpLeft(rectFirst->GetLeft(), rectFirst->GetTop());
	RgPointF  pointRFUpRight(rectFirst->GetRight(), rectFirst->GetTop());
	RgPointF  pointRFDownRight(rectFirst->GetRight(), rectFirst->GetBottom());
	RgPointF  pointRFDownLeft(rectFirst->GetLeft(), rectFirst->GetBottom());

	if (Contains(&pointRFUpLeft, rectSecond))
	{
		return true;
	}

	if (Contains(&pointRFUpRight, rectSecond))
	{
		return true;
	}

	if (Contains(&pointRFDownRight, rectSecond))
	{
		return true;
	}

	if (Contains(&pointRFDownLeft, rectSecond))
	{
		return true;
	}

	// 判断rectSecond的四顶点是否包含在rectFirst中
	RgPointF  pointRSUpLeft (rectSecond->GetLeft(), rectSecond->GetTop());
	RgPointF  pointRSUpRight(rectSecond->GetRight(), rectSecond->GetTop());
	RgPointF  pointRSDownRight(rectSecond->GetRight(), rectSecond->GetBottom());
	RgPointF  pointRSDownLeft (rectSecond->GetLeft(), rectSecond->GetBottom());

	if (Contains(&pointRSUpLeft, rectFirst))
	{
		return true;
	}

	if (Contains(&pointRSUpRight, rectFirst))
	{
		return true;
	}

	if (Contains(&pointRSDownRight,rectFirst))
	{
		return true;
	}

	if (Contains(&pointRSDownLeft, rectFirst))
	{
		return true;
	}

	// 判断不包含顶点但也相交的情况，判断方法：通过判断二者的每条边是否相交，得到结果
	// 将矩形变换为多边形
	RgPolygon  polyFirst ;
	RgPolygon  polySecond ;

	polyFirst.AddTail(pointRFUpLeft);
	polyFirst.AddTail(pointRFUpRight);
	polyFirst.AddTail(pointRFDownRight);
	polyFirst.AddTail(pointRFDownLeft);

	polySecond.AddTail(pointRSUpLeft);
	polySecond.AddTail(pointRSUpRight);
	polySecond.AddTail(pointRSDownRight);
	polySecond.AddTail(pointRSDownLeft);

	for (int i = 0; i < 4; i++)
	{
		RgLineSegment  lineFirst;
		RgLineSegment  lineSecond;
		if (i == 3)
		{
			lineFirst.SetStartPoint(polyFirst.GetAt(i));
			lineFirst.SetEndPoint(polyFirst.GetAt(0));

		}
		else
		{
			lineFirst.SetStartPoint(polyFirst.GetAt(i));
			lineFirst.SetEndPoint(polyFirst.GetAt(i+1));				
		}


		for (int j = 0; j < 4; j++)
		{
			if (j == 3)
			{
				lineSecond.SetStartPoint(polySecond.GetAt(j));
				lineSecond.SetEndPoint( polySecond.GetAt(0));

			}
			else
			{
				lineSecond.SetStartPoint(polySecond.GetAt(j));
				lineSecond.SetEndPoint( polySecond.GetAt(j + 1));					
			}

			// 判断两条线段是否相交，线段相交=矩形相交
			if (Intersects(&lineFirst, &lineSecond))
			{
				return true;
			}

		}
	}


	return false;
}

// 两个poly是否相交，该相交包括其中一个包含另一个
bool RgSpatialRelation::Intersects(const RgPolygon  *polyFirst, const RgPolygon  *polySecond)
{
	int i, j;
	// 判断first多边形的顶点是否包含在second中
	for (i = 0; i < polyFirst->GetCount(); i++)
	{
		if (Contains(&polyFirst->GetAt(i), polySecond))
		{
			return true;
		}
	}

	// 判断second多边形的顶点是否包含在first中
	for (i = 0; i < polySecond->GetCount(); i++)
	{
		if (Contains(&polySecond->GetAt(i), polyFirst))
		{
			return true;
		}
	}

	// 判断两多边形边中是否相交
	for (i = 0; i < polyFirst->GetCount(); i++)
	{
		RgLineSegment  lineFirst;
		RgLineSegment  lineSecond;
		if (i == polyFirst->GetCount() - 1)
		{
			lineFirst.SetStartPoint(polyFirst->GetAt(i));
			lineFirst.SetEndPoint(polyFirst->GetAt(0));
			//lineFirst = gcnew RgLineSegment(polyFirst.GetAt(i), polyFirst.GetAt(0)); 
		}
		else
		{
			lineFirst.SetStartPoint(polyFirst->GetAt(i));
			lineFirst.SetEndPoint(polyFirst->GetAt(i+1));
			//lineFirst = gcnew RgLineSegment(polyFirst.GetAt(i), polyFirst.GetAt(i + 1)); 
		}


		for (j = 0; j < polySecond->GetCount(); j++)
		{
			if (j == polySecond->GetCount() - 1)
			{
				lineSecond.SetStartPoint(polySecond->GetAt(j));
				lineSecond.SetEndPoint(polySecond->GetAt(0));

				//lineSecond = gcnew RgLineSegment(polySecond.GetAt(j), polySecond.GetAt(0)); 
			}
			else
			{
				lineSecond.SetStartPoint(polySecond->GetAt(j));
				lineSecond.SetEndPoint( polySecond->GetAt(j + 1));
				//lineSecond = gcnew RgLineSegment(polySecond.GetAt(j), polySecond.GetAt(j + 1)); 
			}

			// 判断两条线段是否相交，线段相交=矩形相交
			if (Intersects(&lineFirst, &lineSecond))
			{
				return true;
			}

		}
	}


	return false;
}

// rect与poly是否相交，该相交包括其中一个包含另一个
bool RgSpatialRelation::Intersects(const RgRectangle *rect, const RgPolygon *poly)
{
	int i, j;

	// 将矩形转化为多边形，利于处理
	RgPointF  pointUpLeft(rect->GetLeft(), rect->GetTop());
	RgPointF  pointUpRight(rect->GetRight(), rect->GetTop());
	RgPointF  pointDownRight(rect->GetRight(), rect->GetBottom());
	RgPointF  pointDownLeft(rect->GetLeft(), rect->GetBottom());

	RgPolygon polyRect;
	polyRect.AddTail(pointUpLeft);
	polyRect.AddTail(pointUpRight);
	polyRect.AddTail(pointDownRight);
	polyRect.AddTail(pointDownLeft);

	// 判断矩形的顶点是否在多边形内
	for (i = 0; i < polyRect.GetCount(); i++)
	{
		if (Contains(&polyRect.GetAt(i), poly))
		{
			return true;
		}
	}

	// 判断多边形的顶点是否在矩形内
	for (i = 0; i < poly->GetCount(); i++)
	{
		if (Contains(&poly->GetAt(i), &polyRect))
		{
			return true;
		}
	}

	// 判断矩形边和多边形边是否相交
	for (i = 0; i < polyRect.GetCount(); i++)
	{
		RgLineSegment lineFirst;
		RgLineSegment lineSecond;
		if (i == polyRect.GetCount() - 1)
		{
			lineFirst.SetStartPoint(polyRect.GetAt(i));
			lineFirst.SetEndPoint(polyRect.GetAt(0));
			//lineFirst = gcnew RgLineSegment(polyRect.GetAt(i), polyRect.GetAt(0)); 
		}
		else
		{
			lineFirst.SetStartPoint(polyRect.GetAt(i));
			lineFirst.SetEndPoint(polyRect.GetAt(i+1));
			//lineFirst = gcnew RgLineSegment(polyRect.GetAt(i), polyRect.GetAt(i + 1)); 
		}


		for (j = 0; j < poly->GetCount(); j++)
		{
			if (j == poly->GetCount() - 1)
			{
				lineSecond.SetStartPoint(poly->GetAt(j));
				lineSecond.SetEndPoint(poly->GetAt(0));
				//lineSecond = gcnew RgLineSegment(poly.GetAt(j), poly.GetAt(0)); 
			}
			else
			{
				lineSecond.SetStartPoint(poly->GetAt(j));
				lineSecond.SetEndPoint( poly->GetAt(j + 1));
				//lineSecond = gcnew RgLineSegment(poly.GetAt(j), poly.GetAt(j + 1)); 
			}

			// 判断两条线段是否相交，线段相交=矩形相交
			if (Intersects(&lineFirst, &lineSecond))
			{
				return true;
			}

		}
	}


	return false;
}


RgSpatialOperator::RgSpatialOperator()
{

}

// 计算两条线段的交点
bool RgSpatialOperator::Intersection(const RgLineSegment *lineFirst, const RgLineSegment *lineSecond,RgPointF &ptIntersection)
{

	RgPointF  pointf;
	// 判断两条线段是否相交
	if (RgSpatialRelation::Intersects(lineFirst, lineSecond))
	{
		RgPointF  p1,p2,q1,q2;
		p1 = lineFirst->GetStartPoint();		
		p2 = lineFirst->GetEndPoint();
		q1 = lineSecond->GetStartPoint();
		q2 = lineSecond->GetEndPoint(); 

		double dfTempLeft = 0.0, dfTempRight = 0.0;
		//求x坐标
		dfTempLeft = (q2.GetX() - q1.GetX()) * (p1.GetY() - p2.GetY()) - (p2.GetX() - p1.GetX()) * (q1.GetY() - q2.GetY());
		dfTempRight = (p1.GetY() - q1.GetY()) * (p2.GetX() - p1.GetX()) * (q2.GetX() - q1.GetX()) +  q1.GetX() * (q2.GetY() - q1.GetY()) * (p2.GetX() - p1.GetX())
			- p1.GetX() * (p2.GetY() - p1.GetY()) * (q2.GetX() - q1.GetX());
		pointf.SetX(dfTempRight / dfTempLeft) ;



		//求y坐标	
		dfTempLeft = (p1.GetX() - p2.GetX()) * (q2.GetY() - q1.GetY()) - (p2.GetY() - p1.GetY()) * (q1.GetX() - q2.GetX());
		dfTempRight = p2.GetY() * (p1.GetX() - p2.GetX()) * (q2.GetY() - q1.GetY()) + (q2.GetX()- p2.GetX()) * (q2.GetY() - q1.GetY()) * (p1.GetY() - p2.GetY())
			- q2.GetY() * (q1.GetX() - q2.GetX()) * (p2.GetY() - p1.GetY());			 
		pointf.SetY(dfTempRight / dfTempLeft)  ;
		ptIntersection.SetX( pointf.GetX()) ;
		ptIntersection.SetY( pointf.GetY()) ;
		return true;

	} 
	else
	{	
		return false;
	}
	return true;
}

// 将rectFirst和rectSecond合并为一个rect
bool  RgSpatialOperator::Union(const RgRectangle *rectFirst, const RgRectangle *rectSecond, RgRectangle &objrectUnion)
{

	double dfLeft = 0.0, dfRight = 0.0, dfTop = 0.0, dfBottom = 0.0;

	dfLeft = min(rectFirst->GetLeft(), rectSecond->GetLeft());
	dfRight = max(rectFirst->GetRight(), rectSecond->GetRight());
	dfTop = max(rectFirst->GetTop(), rectSecond->GetTop());
	dfBottom = min(rectFirst->GetBottom(), rectSecond->GetBottom());

	objrectUnion.SetLeft(dfLeft);
	objrectUnion.SetTop(dfTop);
	objrectUnion.SetRight(dfRight);
	objrectUnion.SetBottom(dfBottom);

	return true;

}

// 计算几何对象的最小外接矩形
bool RgSpatialOperator::Boundary(const RgPolygon  *poly, RgRectangle &objrectBoundary)
{	
	RgPointF point; 
	double dfUpLeftX = 0.0, dfUpLeftY = 0.0, dfDownRightX = 0.0, dfDownRightY = 0.0;

	point = poly->GetAt(0);
	dfUpLeftX = point.GetX(); 
	dfUpLeftY = point.GetY();
	dfDownRightX = point.GetX(); 
	dfDownRightY = point.GetY();

	for (int i = 0; i < poly->GetCount(); i++)
	{
		if (poly->GetAt(i).GetX() <= dfUpLeftX)
		{
			dfUpLeftX = poly->GetAt(i).GetX();
		}

		if (poly->GetAt(i).GetX() >= dfDownRightX)
		{
			dfDownRightX = poly->GetAt(i).GetX();
		}

		if (poly->GetAt(i).GetY() >= dfUpLeftY)
		{
			dfUpLeftY = poly->GetAt(i).GetY();
		}

		if (poly->GetAt(i).GetY() <= dfDownRightY)
		{
			dfDownRightY = poly->GetAt(i).GetY();
		}
	}

	objrectBoundary.SetLeft(dfUpLeftX);
	objrectBoundary.SetTop(dfUpLeftY);
	objrectBoundary.SetRight(dfDownRightX);
	objrectBoundary.SetBottom(dfDownRightY);

	return true;

}

// 计算两个矩形的交集
bool  RgSpatialOperator::Intersection(const RgRectangle * rectFirst, const RgRectangle  *rectSecond,RgRectangle &rectIntersection)
{
	// 判断两个矩形是否相交，相交->求交集
	RgRectangle rect(0.0, 0.0, 0.0, 0.0);
	if (RgSpatialRelation::Intersects(rectFirst, rectSecond))
	{
		// 分别计算两个矩形的交点和互相包含的顶点
		RgPointFList listPoint;		

		// 两矩形互相包含的顶点
		RgPointF  pointRFUpLeft(rectFirst->GetLeft(), rectFirst->GetTop());
		RgPointF  pointRFUpRight(rectFirst->GetRight(), rectFirst->GetTop());
		RgPointF  pointRFDownRight(rectFirst->GetRight(), rectFirst->GetBottom());
		RgPointF  pointRFDownLeft(rectFirst->GetLeft(), rectFirst->GetBottom());

		if (RgSpatialRelation::Contains(&pointRFUpLeft, rectSecond))
		{
			listPoint.AddTail(pointRFUpLeft);
		}

		if (RgSpatialRelation::Contains(&pointRFUpRight, rectSecond))
		{
			listPoint.AddTail(pointRFUpRight);
		}

		if (RgSpatialRelation::Contains(&pointRFDownRight, rectSecond))
		{
			listPoint.AddTail(pointRFDownRight);
		}

		if (RgSpatialRelation::Contains(&pointRFDownLeft, rectSecond))
		{
			listPoint.AddTail(pointRFDownLeft);
		}

		// 判断rectSecond的四顶点是否包含在rectFirst中
		RgPointF pointRSUpLeft(rectSecond->GetLeft(), rectSecond->GetTop());
		RgPointF pointRSUpRight(rectSecond->GetRight(), rectSecond->GetTop());
		RgPointF pointRSDownRight(rectSecond->GetRight(), rectSecond->GetBottom());
		RgPointF pointRSDownLeft(rectSecond->GetLeft(), rectSecond->GetBottom());

		if (RgSpatialRelation::Contains(&pointRSUpLeft, rectFirst))
		{
			listPoint.AddTail(pointRSUpLeft);
		}

		if (RgSpatialRelation::Contains(&pointRSUpRight, rectFirst))
		{
			listPoint.AddTail(pointRSUpRight);
		}

		if (RgSpatialRelation::Contains(&pointRSDownRight, rectFirst))
		{
			listPoint.AddTail(pointRSDownRight);
		}

		if (RgSpatialRelation::Contains(&pointRSDownLeft, rectFirst))
		{
			listPoint.AddTail(pointRSDownLeft);
		}

		// 计算两矩形的交点，将矩形变换为多边形
		RgPolygon  polyFirst;
		RgPolygon  polySecond;

		polyFirst.AddTail(pointRFUpLeft);
		polyFirst.AddTail(pointRFUpRight);
		polyFirst.AddTail(pointRFDownRight);
		polyFirst.AddTail(pointRFDownLeft);

		polySecond.AddTail(pointRSUpLeft);
		polySecond.AddTail(pointRSUpRight);
		polySecond.AddTail(pointRSDownRight);
		polySecond.AddTail(pointRSDownLeft);

		for (int i = 0; i < 4; i++)
		{
			RgLineSegment  lineFirst;
			RgLineSegment  lineSecond;
			if (i == 3)
			{
				lineFirst.SetStartPoint(polyFirst.GetAt(i));
				lineFirst.SetEndPoint(polyFirst.GetAt(0));				
			}
			else
			{
				lineFirst.SetStartPoint(polyFirst.GetAt(i));
				lineFirst.SetEndPoint(polyFirst.GetAt(i + 1));
			}


			for (int j = 0; j < 4; j++)
			{
				if (j == 3)
				{
					lineSecond.SetStartPoint(polySecond.GetAt(j));
					lineSecond.SetEndPoint(polySecond.GetAt(0));						
				}
				else
				{
					lineSecond.SetStartPoint(polySecond.GetAt(j));
					lineSecond.SetEndPoint(polySecond.GetAt(j + 1));							
				}

				// 判断两条线段是否相交，线段相交=矩形相交
				RgPointF pointfTemp;
				if(Intersection(&lineFirst, &lineSecond,pointfTemp))					
				{
					listPoint.AddTail(pointfTemp);
				}

			}
		}

		// 将得到的点链表，通过求取四角点值确定最终矩形
		RgPolygon poly;
		for (int i = 0; i < listPoint.GetCount(); i++)
		{
			RgPointF pointfPoly = listPoint.GetAt(i);
			poly.AddTail(pointfPoly);
		};
		

		Boundary(&poly, rect);
		rectIntersection.SetLeft(rect.GetLeft());
		rectIntersection.SetRight(rect.GetRight());
		rectIntersection.SetTop(rect.GetTop());
		rectIntersection.SetBottom(rect.GetBottom());

		return true;

	}
	else
	{
		return false;
	}

}

/////////////////////////////////////////////////////////////

////////////////////////TileLocation/////////////////////////////
RgTileLocation::RgTileLocation()
{
	m_iCol=0;
	m_iRow=0;
}
RgTileLocation::RgTileLocation(RgTileLocation const &tl)
{
	m_iCol=tl.m_iCol;
	m_iRow=tl.m_iRow;
}

RgTileLocation::RgTileLocation(int nCol, int nRow)
{
	m_iCol=nCol;
	m_iRow=nRow;
}

int RgTileLocation::GetCol()const
{
	return m_iCol;

}

void RgTileLocation::SetCol(int nCol)
{
	m_iCol=nCol;
}

int RgTileLocation::GetRow()const
{
	return m_iRow;
}

void RgTileLocation::SetRow(int nRow)
{
	m_iRow=nRow;
}

bool RgTileLocation::operator == (RgTileLocation tl)const
{
	if (m_iRow==tl.m_iRow&&m_iCol ==tl.m_iCol)
		return true;
	else return false;
}

void RgTileLocation::operator =(RgTileLocation const &tilelocation)
{
	m_iCol=tilelocation.m_iCol;
	m_iRow=tilelocation.m_iRow;
}