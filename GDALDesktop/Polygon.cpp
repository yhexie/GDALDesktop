#include "Polygon.h"

using namespace EarthView::TilesEngine::VectorSpatial;
///////////********class point***********////////////////
EVPoint::EVPoint()
{
	m_nX = 0;
	m_nY = 0;
}

EVPoint::EVPoint(int nX, int nY)
{
	m_nX = nX;
	m_nY = nY;
}
EVPoint::EVPoint(EVPoint const &point)
{
	m_nX = point.m_nX;
	m_nY = point.m_nY;
}

int EVPoint::GetX()const
{
	return m_nX;
}
int EVPoint::GetY()const
{
	return m_nY;
}
void EVPoint::SetX(int nX)
{
	m_nX = nX;
}
void EVPoint::SetY(int nY)
{
	m_nY = nY;
}
bool EVPoint::operator == (EVPoint point)const
{
	if (m_nX==point.m_nX&&m_nY ==point.m_nY)
		return true;
	else return false;

}
void EVPoint::operator =(EVPoint const &point)
{
	m_nX = point.m_nX;
	m_nY = point.m_nY;
}
///////////********class Point***********////////////////
/////////********class PointF***********////////////////
EVPointF::EVPointF()
{
	m_dfX = 0.0;
	m_dfY = 0.0;
}

EVPointF::EVPointF(double dfX, double dfY)
{
	m_dfX = dfX;
	m_dfY = dfY;
}
EVPointF::EVPointF(EVPointF const &point)
{
	m_dfX = point.m_dfX;
	m_dfY = point.m_dfY;
}

bool EVPointF::operator == (EVPointF point)const
{
	if (m_dfX==point.m_dfX&&m_dfY ==point.m_dfY)
		return true;
	else return false;

}
void EVPointF::operator =(EVPointF const &point)
{
	m_dfX = point.m_dfX;
	m_dfY = point.m_dfY;
}
double EVPointF::GetX()const
{
	return m_dfX;
}
double EVPointF::GetY()const
{
	return m_dfY;
}
void EVPointF::SetX(double dfX)
{
	m_dfX = dfX;
}
void EVPointF::SetY(double dfY)
{
	m_dfY = dfY;
}
/////////////********class PointF***********////////////////
/////////////********class LineSegment***********////////////////

EVLineSegment::EVLineSegment()
{

}
EVLineSegment::EVLineSegment(EVLineSegment const &lineSegment)
{

	m_pointStart = lineSegment.m_pointStart;
	m_pointEnd = lineSegment.m_pointEnd;
}


EVLineSegment::EVLineSegment(EVPointF  pointStart, EVPointF  pointEnd)
{
	m_pointStart = pointStart;
	m_pointEnd = pointEnd;
}

void EVLineSegment::SetStartPoint(EVPointF point)
{
	m_pointStart= point;

}

void EVLineSegment::SetEndPoint(EVPointF point)
{
	m_pointEnd = point;


}

EVPointF EVLineSegment::GetStartPoint()const
{
	return m_pointStart;
}

EVPointF EVLineSegment::GetEndPoint()const
{	
	return m_pointEnd;
}
void EVLineSegment::operator =(EVLineSegment const &point)
{
	m_pointStart = point.m_pointStart;
	m_pointEnd = point.m_pointEnd;

}
/////////////********class LineSegment***********////////////////
///////////********class PointFList***********////////////////


EVPointFList::EVPointFList()
{		
}
EVPointFList::~EVPointFList()
{		
	if(!m_listPoint.empty())
	{
		m_listPoint.clear();
	}
}

EVPointFList::EVPointFList(EVPointFList const&pointlist)
{	
	for (int i = 0; i < pointlist.GetCount(); i++)
	{
		EVPointF  point =  pointlist.GetAt(i);
		m_listPoint.push_back(point);			
	}
}
int EVPointFList::GetCount()const
{
	return m_listPoint.size() ;
}


void EVPointFList::RemoveAt(int nIndex)
{
	list<EVPointF>::iterator los;
	los = m_listPoint.begin();
	for (int i = 0;i<nIndex;i++)
		los++;
	m_listPoint.erase(los);
}

void EVPointFList::Clear()
{
	m_listPoint.clear();
}

void EVPointFList::AddTail(EVPointF point)
{

	m_listPoint.push_back(point);

}

void EVPointFList::AddHead(EVPointF  point)
{
	m_listPoint.push_front(point);
}

void EVPointFList::Insert(int nIndex, EVPointF  point)
{

	list<EVPointF>::iterator los;
	los = m_listPoint.begin();
	for (int i = 0;i<nIndex;i++)
		los++;
	m_listPoint.insert(los,point);

}

EVPointF EVPointFList::GetAt(int nIndex)const
{

	list<EVPointF>::const_iterator los;

	los =m_listPoint.begin();

	for (int i=0;i<nIndex;i++)
	{
		los ++;
	}

	return *los;

}
void EVPointFList::operator = (EVPointFList const &pointList)
{
	for (int i = 0; i < pointList.GetCount(); i++)
	{
		EVPointF  point =  pointList.GetAt(i);
		m_listPoint.push_back(point);			
	}
}
/////////////********class PointFList***********////////////////
///////////********class Polygon***********////////////////


EVPolygon::EVPolygon()
{
	if(!m_listPoint.empty())
	{
		m_listPoint.clear();
	}
}
EVPolygon::~EVPolygon()
{
	if(!m_listPoint.empty())
	{
		m_listPoint.clear();
	}

}
EVPolygon::EVPolygon(EVPolygon const&polygon)
{
	for (int i = 0; i < polygon.GetCount(); i++)
	{
		EVPointF  point =  polygon.GetAt(i);
		m_listPoint.push_back(point);			
	}
}

int EVPolygon::GetCount()const
{
	return m_listPoint.size();
}	

bool EVPolygon::Contains(EVPointF const point)
{

	list<EVPointF>::const_iterator los;
	los =find(m_listPoint.begin(),m_listPoint.end(),point);
	if  ( los == m_listPoint.end( ) )
	{
		return false;
	}

	return true;
}

void EVPolygon::RemoveAt(int nIndex)
{
	list<EVPointF>::iterator los;
	los = m_listPoint.begin();
	for (int i = 0;i<nIndex;i++)
		los++;
	m_listPoint.erase(los);		
}

void EVPolygon::Clear()
{
	m_listPoint.clear();
}

void EVPolygon::AddTail(EVPointF point)
{
	m_listPoint.push_back(point);
}

void EVPolygon::AddHead(EVPointF  point)
{			
	m_listPoint.push_front(point);
}

void EVPolygon::Insert(int nIndex, EVPointF point)
{
	list<EVPointF>::iterator los;
	los = m_listPoint.begin();
	for (int i = 0;i<nIndex;i++)
		los++;
	m_listPoint.insert(los,point)	;		
}

EVPointF EVPolygon::GetAt(int nIndex)const
{

	list<EVPointF>::const_iterator los;
	los = m_listPoint.begin();
	for (int i=0;i<nIndex;i++)
	{
		los ++;
	}

	return *los;			
}


bool EVPolygon::operator == (EVPolygon polygon)const
{

	bool bEqual = true;
	list<EVPointF>::const_iterator los;
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
void EVPolygon::operator = (EVPolygon const &polygon)
{
	for (int i = 0; i < polygon.GetCount(); i++)
	{
		EVPointF  point =  polygon.GetAt(i);
		m_listPoint.push_back(point);			
	}	

}
/////////////********class Polygon***********////////////////
///////////********class PolygonList***********////////////////


EVPolygonList::EVPolygonList()
{

}

EVPolygonList::~EVPolygonList()
{
	if(!m_listPolygon.empty())
	{
		for each(EVPolygon *objPolygon in m_listPolygon)
		{
			delete objPolygon;
		}

		m_listPolygon.clear();
	}

}
int EVPolygonList::GetCount()const
{
	return m_listPolygon.size();
}	

bool EVPolygonList::Contains(EarthView::TilesEngine::VectorSpatial::EVPolygon const poly)
{
	list<EVPolygon*>::const_iterator los;
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

void EVPolygonList::RemoveAt(int nIndex)
{
	list<EVPolygon*>::iterator los;
	los = m_listPolygon.begin();
	for (int i = 0;i<nIndex;i++)
		los++;
	m_listPolygon.erase(los);	

}

void EVPolygonList::Clear()
{
	if(!m_listPolygon.empty())
	{
		for each(EVPolygon *objPolygon in m_listPolygon)
		{
			delete objPolygon;
		}

		m_listPolygon.clear();
	}
}

void EVPolygonList::AddTail(EarthView::TilesEngine::VectorSpatial::EVPolygon *poly)
{
	EarthView::TilesEngine::VectorSpatial::EVPolygon *objPoly = new EarthView::TilesEngine::VectorSpatial::EVPolygon();
	*objPoly = *poly;

	m_listPolygon.push_back(objPoly);
}

void EVPolygonList::AddHead(EarthView::TilesEngine::VectorSpatial::EVPolygon  *poly)
{	
	EarthView::TilesEngine::VectorSpatial::EVPolygon *objPoly = new EarthView::TilesEngine::VectorSpatial::EVPolygon();
	*objPoly = *poly;

	m_listPolygon.push_front(objPoly);
}

void EVPolygonList::Insert(int nIndex, EarthView::TilesEngine::VectorSpatial::EVPolygon *poly)
{
	EarthView::TilesEngine::VectorSpatial::EVPolygon *objPoly = new EarthView::TilesEngine::VectorSpatial::EVPolygon();
	*objPoly = *poly;

	list<EVPolygon*>::iterator los;
	los = m_listPolygon.begin();
	for (int i = 0;i<nIndex;i++)
		los++;
	m_listPolygon.insert(los,objPoly);		
}	
const EarthView::TilesEngine::VectorSpatial::EVPolygon  *EVPolygonList::GetAt(int nIndex)const
{
	list<EarthView::TilesEngine::VectorSpatial::EVPolygon*>::const_iterator los;
	los = m_listPolygon.begin();
	for (int i=0;i<nIndex;i++)
	{
		los ++;
	}
	return *los;
}
void EVPolygonList::operator = (EVPolygonList const &polygonList)
{
	if(!m_listPolygon.empty())
	{
		for each(EarthView::TilesEngine::VectorSpatial::EVPolygon *objPolygon in m_listPolygon)
		{
			delete objPolygon;
		}

		m_listPolygon.clear();
	}

	list<EarthView::TilesEngine::VectorSpatial::EVPolygon*>::const_iterator los;
	los =polygonList.m_listPolygon.begin();
	if(!(los==polygonList.m_listPolygon.end()))
	{
		EarthView::TilesEngine::VectorSpatial::EVPolygon *objPoly = new EarthView::TilesEngine::VectorSpatial::EVPolygon();
		*objPoly = *(*los);

		m_listPolygon.push_back(objPoly);	
		los++;
	}
}


///////////********class PolygonList***********////////////////
///////////********class Size***********////////////////

EVSize::EVSize()
{
	m_nWidth = 0;
	m_nHeight = 0;
}
EVSize::EVSize(int nWidth, int nHeight)
{
	m_nWidth=nWidth;
	m_nHeight=nHeight;

}
EVSize::EVSize(EVSize const& size)
{
	m_nWidth = size.GetWidth();
	m_nHeight = size.GetHeight();
}
int EVSize::GetWidth()const
{
	return m_nWidth;
}
int EVSize::GetHeight()const
{
	return m_nHeight;
}
void EVSize::SetWidth(int nWidth)
{
	m_nWidth = nWidth;
}
void EVSize::SetHeight(int nHeight)
{
	m_nHeight = nHeight;
}
void EVSize::operator =(EVSize const &size)
{
	m_nHeight = size.m_nHeight;
	m_nWidth = size.m_nWidth;
}
///////////********class EVSize***********////////////////

///////////********class Rectangle***********////////////////


EVRectangle::EVRectangle()
{

	m_dfUpLeftX=0.0;
	m_dfUpLeftY=0.0;
	m_dfDownRightX=0.0;
	m_dfDownRightY=0.0;

}
EVRectangle::EVRectangle(double dfUpLeftX, double dfUpLeftY, double dfDownRightX, double dfDownRightY)
{
	m_dfUpLeftX = dfUpLeftX;
	m_dfUpLeftY = dfUpLeftY;
	m_dfDownRightX = dfDownRightX;
	m_dfDownRightY = dfDownRightY;
}

EVRectangle::EVRectangle(EVPointF pointUpLeft, EVSize size)
{
	m_dfUpLeftX = pointUpLeft.GetX();
	m_dfUpLeftY = pointUpLeft.GetY();
	m_dfDownRightX = m_dfUpLeftX + size.GetWidth();
	m_dfDownRightY = m_dfUpLeftY + size.GetWidth();
}
EVRectangle::EVRectangle(EVRectangle const &rect)
{
	m_dfUpLeftX = rect.m_dfUpLeftX;
	m_dfUpLeftY = rect.m_dfUpLeftY;
	m_dfDownRightX = rect.m_dfDownRightX;
	m_dfDownRightY = rect.m_dfDownRightY;
}

double EVRectangle::GetLeft()const
{
	return m_dfUpLeftX;
}

double EVRectangle::GetRight()const
{
	return m_dfDownRightX;
}

double EVRectangle::GetTop()const
{
	return m_dfUpLeftY;
}

double EVRectangle::GetBottom()const
{
	return m_dfDownRightY;
}
void EVRectangle::SetLeft(double dfUpLeftX)
{
	m_dfUpLeftX =dfUpLeftX;
}
void EVRectangle::SetRight(double dfDownRightX)
{
	m_dfDownRightX =dfDownRightX;
}
void EVRectangle::SetTop(double dfUpLeftY)
{
	m_dfUpLeftY =dfUpLeftY;
}
void EVRectangle::SetBottom(double dfDownRightY)
{
	m_dfDownRightY =dfDownRightY;
}
void EVRectangle::operator =(EVRectangle const &rect)
{
	m_dfUpLeftX = rect.m_dfUpLeftX;
	m_dfUpLeftY = rect.m_dfUpLeftY;
	m_dfDownRightX = rect.m_dfDownRightX;
	m_dfDownRightY = rect.m_dfDownRightY;
}
///////////********class Rectangle***********////////////////
///////////********class SpatialRelation***********////////////////

EVSpatialRelation::EVSpatialRelation()
{

}	
double EVSpatialRelation::Mult(const EVPointF *pointFirst, const EVPointF *pointSecond, const EVPointF *pointThird)
{
	return ((pointFirst->GetX() - pointThird->GetX()) * (pointSecond->GetY() - pointThird->GetY()) - (pointSecond->GetX() - pointThird->GetX()) * (pointFirst->GetY() - pointThird->GetY()));
}

// point是否包含在rect中
bool EVSpatialRelation::Contains(const EVPointF *point, const EVRectangle *rect)
{
	if (point->GetX() >= rect->GetLeft() && point->GetX() <= rect->GetRight() && point->GetY() >= rect->GetBottom() && point->GetY() <= rect->GetTop())
	{
		return true;			
	}
	return false;
}

// point是否包含在poly中
bool EVSpatialRelation::Contains(const EVPointF  *point, const EVPolygon  *poly)
{
	bool bInside = false;
	double df1=0.0,df2=0.0;

	EVPointF point1;
	EVPointF point2 ;

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
bool EVSpatialRelation::Contains(const EVRectangle *rectFirst, const EVRectangle  *rectSecond)
{
	// 判断rectFirst的四顶点是否全部包含在rectSecond中
	EVPointF *pointRFUpLeft = new EVPointF(rectFirst->GetLeft(), rectFirst->GetTop());
	EVPointF *pointRFUpRight = new EVPointF(rectFirst->GetRight(), rectFirst->GetTop());
	EVPointF *pointRFDownRight = new EVPointF(rectFirst->GetRight(), rectFirst->GetBottom());
	EVPointF *pointRFDownLeft = new EVPointF(rectFirst->GetLeft(), rectFirst->GetBottom());

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
bool EVSpatialRelation::Intersects(const EVLineSegment *lineFirst, const EVLineSegment *lineSecond)
{
	return (max(lineFirst->GetStartPoint().GetX(), lineFirst->GetEndPoint().GetX()) >= min(lineSecond->GetStartPoint().GetX(), lineSecond->GetEndPoint().GetX())
		&& max(lineFirst->GetStartPoint().GetY(), lineFirst->GetEndPoint().GetY()) >= min(lineSecond->GetStartPoint().GetY(), lineSecond->GetEndPoint().GetY())
		&& max(lineSecond->GetStartPoint().GetX(), lineSecond->GetEndPoint().GetX()) >= min(lineFirst->GetStartPoint().GetX(), lineFirst->GetEndPoint().GetX())
		&& max(lineSecond->GetStartPoint().GetY(), lineSecond->GetEndPoint().GetY()) >= min(lineFirst->GetStartPoint().GetY(), lineFirst->GetEndPoint().GetY())
		&& Mult(&lineSecond->GetStartPoint(), &lineFirst->GetEndPoint(), &lineFirst->GetStartPoint()) * Mult(&lineFirst->GetEndPoint(), &lineSecond->GetEndPoint(), &lineFirst->GetStartPoint()) >= 0.0
		&& Mult(&lineFirst->GetStartPoint(), &lineSecond->GetEndPoint(), &lineSecond->GetStartPoint()) * Mult(&lineSecond->GetEndPoint(), &lineFirst->GetEndPoint(), &lineSecond->GetStartPoint()) >= 0.0);
}

// 两个rect是否相交，该相交包括其中一个包含另一个的情况
bool EVSpatialRelation::Intersects(const EVRectangle  *rectFirst, const EVRectangle  *rectSecond)
{
	// 判断rectFirst的四顶点是否包含在rectSecond中
	EVPointF  pointRFUpLeft(rectFirst->GetLeft(), rectFirst->GetTop());
	EVPointF  pointRFUpRight(rectFirst->GetRight(), rectFirst->GetTop());
	EVPointF  pointRFDownRight(rectFirst->GetRight(), rectFirst->GetBottom());
	EVPointF  pointRFDownLeft(rectFirst->GetLeft(), rectFirst->GetBottom());

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
	EVPointF  pointRSUpLeft (rectSecond->GetLeft(), rectSecond->GetTop());
	EVPointF  pointRSUpRight(rectSecond->GetRight(), rectSecond->GetTop());
	EVPointF  pointRSDownRight(rectSecond->GetRight(), rectSecond->GetBottom());
	EVPointF  pointRSDownLeft (rectSecond->GetLeft(), rectSecond->GetBottom());

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
	EVPolygon  polyFirst ;
	EVPolygon  polySecond ;

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
		EVLineSegment  lineFirst;
		EVLineSegment  lineSecond;
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
bool EVSpatialRelation::Intersects(const EVPolygon  *polyFirst, const EVPolygon  *polySecond)
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
		EVLineSegment  lineFirst;
		EVLineSegment  lineSecond;
		if (i == polyFirst->GetCount() - 1)
		{
			lineFirst.SetStartPoint(polyFirst->GetAt(i));
			lineFirst.SetEndPoint(polyFirst->GetAt(0));
			//lineFirst = gcnew EVLineSegment(polyFirst.GetAt(i), polyFirst.GetAt(0)); 
		}
		else
		{
			lineFirst.SetStartPoint(polyFirst->GetAt(i));
			lineFirst.SetEndPoint(polyFirst->GetAt(i+1));
			//lineFirst = gcnew EVLineSegment(polyFirst.GetAt(i), polyFirst.GetAt(i + 1)); 
		}


		for (j = 0; j < polySecond->GetCount(); j++)
		{
			if (j == polySecond->GetCount() - 1)
			{
				lineSecond.SetStartPoint(polySecond->GetAt(j));
				lineSecond.SetEndPoint(polySecond->GetAt(0));

				//lineSecond = gcnew EVLineSegment(polySecond.GetAt(j), polySecond.GetAt(0)); 
			}
			else
			{
				lineSecond.SetStartPoint(polySecond->GetAt(j));
				lineSecond.SetEndPoint( polySecond->GetAt(j + 1));
				//lineSecond = gcnew EVLineSegment(polySecond.GetAt(j), polySecond.GetAt(j + 1)); 
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
bool EVSpatialRelation::Intersects(const EVRectangle *rect, const EVPolygon *poly)
{
	int i, j;

	// 将矩形转化为多边形，利于处理
	EVPointF  pointUpLeft(rect->GetLeft(), rect->GetTop());
	EVPointF  pointUpRight(rect->GetRight(), rect->GetTop());
	EVPointF  pointDownRight(rect->GetRight(), rect->GetBottom());
	EVPointF  pointDownLeft(rect->GetLeft(), rect->GetBottom());

	EVPolygon polyRect;
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
		EVLineSegment lineFirst;
		EVLineSegment lineSecond;
		if (i == polyRect.GetCount() - 1)
		{
			lineFirst.SetStartPoint(polyRect.GetAt(i));
			lineFirst.SetEndPoint(polyRect.GetAt(0));
			//lineFirst = gcnew EVLineSegment(polyRect.GetAt(i), polyRect.GetAt(0)); 
		}
		else
		{
			lineFirst.SetStartPoint(polyRect.GetAt(i));
			lineFirst.SetEndPoint(polyRect.GetAt(i+1));
			//lineFirst = gcnew EVLineSegment(polyRect.GetAt(i), polyRect.GetAt(i + 1)); 
		}


		for (j = 0; j < poly->GetCount(); j++)
		{
			if (j == poly->GetCount() - 1)
			{
				lineSecond.SetStartPoint(poly->GetAt(j));
				lineSecond.SetEndPoint(poly->GetAt(0));
				//lineSecond = gcnew EVLineSegment(poly.GetAt(j), poly.GetAt(0)); 
			}
			else
			{
				lineSecond.SetStartPoint(poly->GetAt(j));
				lineSecond.SetEndPoint( poly->GetAt(j + 1));
				//lineSecond = gcnew EVLineSegment(poly.GetAt(j), poly.GetAt(j + 1)); 
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


EVSpatialOperator::EVSpatialOperator()
{

}

// 计算两条线段的交点
bool EVSpatialOperator::Intersection(const EVLineSegment *lineFirst, const EVLineSegment *lineSecond,EVPointF &ptIntersection)
{

	EVPointF  pointf;
	// 判断两条线段是否相交
	if (EVSpatialRelation::Intersects(lineFirst, lineSecond))
	{
		EVPointF  p1,p2,q1,q2;
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
bool  EVSpatialOperator::Union(const EVRectangle *rectFirst, const EVRectangle *rectSecond, EVRectangle &objrectUnion)
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
bool EVSpatialOperator::Boundary(const EVPolygon  *poly, EVRectangle &objrectBoundary)
{	
	EVPointF point; 
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
bool  EVSpatialOperator::Intersection(const EVRectangle * rectFirst, const EVRectangle  *rectSecond,EVRectangle &rectIntersection)
{
	// 判断两个矩形是否相交，相交->求交集
	EVRectangle rect(0.0, 0.0, 0.0, 0.0);
	if (EVSpatialRelation::Intersects(rectFirst, rectSecond))
	{
		// 分别计算两个矩形的交点和互相包含的顶点
		EVPointFList listPoint;		

		// 两矩形互相包含的顶点
		EVPointF  pointRFUpLeft(rectFirst->GetLeft(), rectFirst->GetTop());
		EVPointF  pointRFUpRight(rectFirst->GetRight(), rectFirst->GetTop());
		EVPointF  pointRFDownRight(rectFirst->GetRight(), rectFirst->GetBottom());
		EVPointF  pointRFDownLeft(rectFirst->GetLeft(), rectFirst->GetBottom());

		if (EVSpatialRelation::Contains(&pointRFUpLeft, rectSecond))
		{
			listPoint.AddTail(pointRFUpLeft);
		}

		if (EVSpatialRelation::Contains(&pointRFUpRight, rectSecond))
		{
			listPoint.AddTail(pointRFUpRight);
		}

		if (EVSpatialRelation::Contains(&pointRFDownRight, rectSecond))
		{
			listPoint.AddTail(pointRFDownRight);
		}

		if (EVSpatialRelation::Contains(&pointRFDownLeft, rectSecond))
		{
			listPoint.AddTail(pointRFDownLeft);
		}

		// 判断rectSecond的四顶点是否包含在rectFirst中
		EVPointF pointRSUpLeft(rectSecond->GetLeft(), rectSecond->GetTop());
		EVPointF pointRSUpRight(rectSecond->GetRight(), rectSecond->GetTop());
		EVPointF pointRSDownRight(rectSecond->GetRight(), rectSecond->GetBottom());
		EVPointF pointRSDownLeft(rectSecond->GetLeft(), rectSecond->GetBottom());

		if (EVSpatialRelation::Contains(&pointRSUpLeft, rectFirst))
		{
			listPoint.AddTail(pointRSUpLeft);
		}

		if (EVSpatialRelation::Contains(&pointRSUpRight, rectFirst))
		{
			listPoint.AddTail(pointRSUpRight);
		}

		if (EVSpatialRelation::Contains(&pointRSDownRight, rectFirst))
		{
			listPoint.AddTail(pointRSDownRight);
		}

		if (EVSpatialRelation::Contains(&pointRSDownLeft, rectFirst))
		{
			listPoint.AddTail(pointRSDownLeft);
		}

		// 计算两矩形的交点，将矩形变换为多边形
		EVPolygon  polyFirst;
		EVPolygon  polySecond;

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
			EVLineSegment  lineFirst;
			EVLineSegment  lineSecond;
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
				EVPointF pointfTemp;
				if(Intersection(&lineFirst, &lineSecond,pointfTemp))					
				{
					listPoint.AddTail(pointfTemp);
				}

			}
		}

		// 将得到的点链表，通过求取四角点值确定最终矩形
		EVPolygon poly;
		for (int i = 0; i < listPoint.GetCount(); i++)
		{
			EVPointF pointfPoly = listPoint.GetAt(i);
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
EVTileLocation::EVTileLocation()
{
	m_iCol=0;
	m_iRow=0;
}
EVTileLocation::EVTileLocation(EVTileLocation const &tl)
{
	m_iCol=tl.m_iCol;
	m_iRow=tl.m_iRow;
}

EVTileLocation::EVTileLocation(int nCol, int nRow)
{
	m_iCol=nCol;
	m_iRow=nRow;
}

int EVTileLocation::GetCol()const
{
	return m_iCol;

}

void EVTileLocation::SetCol(int nCol)
{
	m_iCol=nCol;
}

int EVTileLocation::GetRow()const
{
	return m_iRow;
}

void EVTileLocation::SetRow(int nRow)
{
	m_iRow=nRow;
}

bool EVTileLocation::operator == (EVTileLocation tl)const
{
	if (m_iRow==tl.m_iRow&&m_iCol ==tl.m_iCol)
		return true;
	else return false;
}

void EVTileLocation::operator =(EVTileLocation const &tilelocation)
{
	m_iCol=tilelocation.m_iCol;
	m_iRow=tilelocation.m_iRow;
}
