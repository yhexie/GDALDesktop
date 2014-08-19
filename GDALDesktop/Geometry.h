#pragma once
#include "stdafx.h"

namespace RGeos 
{
	namespace Geometry
	{		
					class RGEOS_API RgPoint
					{
						// TODO: 在此处添加此类的方法。
					private:
						int m_nX;
						int m_nY;

					public:				
						RgPoint();
						RgPoint(RgPoint const &pt);
						RgPoint(int nX, int nY);				
						int GetX()const;
						void SetX(int nX);
						int GetY()const;
						void SetY(int nY);
						bool operator == (RgPoint point)const;
						void operator =(RgPoint const &point);
					};

					
					class RGEOS_API RgPointF
					{
						// TODO: 在此处添加此类的方法。
					private:
						double m_dfX;
						double m_dfY;

					public:

						RgPointF();
						RgPointF(RgPointF const &pt);
						RgPointF(double dfX, double dfY);				
						double GetX()const;
						void SetX(double dfX);
						double GetY()const;
						void SetY(double dfY);
						bool operator == (RgPointF point)const;
						void operator =(RgPointF const &point);


					};

					// 线段，包含起点和终点
					class RGEOS_API RgLineSegment        
					{
						// TODO: 在此处添加此类的方法。
					private:
						RgPointF  m_pointStart;
						RgPointF  m_pointEnd;
					public:
						RgLineSegment();
						RgLineSegment(RgPointF  pointStart, RgPointF pointEnd);
						RgLineSegment(RgLineSegment const &lineSegment);
						void SetStartPoint(RgPointF point);
						void SetEndPoint(RgPointF point);
						RgPointF GetStartPoint()const;	
						RgPointF GetEndPoint()const;
						void operator =(RgLineSegment const &point);

					};

					class RGEOS_API RgPointFList        
					{
						// TODO: 在此处添加此类的方法。
					private:
						list<RgPointF>  m_listPoint;
					public:
						RgPointFList();
						~RgPointFList();
						RgPointFList( RgPointFList const& pointlist);
						int GetCount()const;
						void RemoveAt(int nIndex);
						void Clear();
						void AddTail(RgPointF  point);
						void AddHead(RgPointF  point);
						void Insert(int nIndex, RgPointF  point);	
						RgPointF  GetAt(int nIndex)const;
						void operator = (RgPointFList const &pointList);

					};

					// 多边形必须为闭合的（即首尾点相同）
					class RGEOS_API RgPolygon        
					{
						// TODO: 在此处添加此类的方法。
					private:
						list<RgPointF > m_listPoint;

					public:
						RgPolygon();
						~RgPolygon();
						RgPolygon( RgPolygon const& polygon);
						int GetCount()const;					
						bool Contains(RgPointF const point);
						void RemoveAt(int nIndex);
						void Clear();
						void AddTail(RgPointF  point);
						void AddHead(RgPointF  point);
						void Insert(int nIndex, RgPointF  point);		
						RgPointF  GetAt(int nIndex)const;
						bool operator == (RgPolygon polygon)const;			
						void operator = (RgPolygon const &polygon);
					};

					class RGEOS_API RgPolygonList
					{
						// TODO: 在此处添加此类的方法。
					private:
						list<RgPolygon *> m_listPolygon;

					public:
						RgPolygonList();
						~RgPolygonList();				
						int GetCount()const;					
						bool Contains(RgPolygon const poly);
						void RemoveAt(int nIndex);
						void Clear();
						void AddTail(RgPolygon  *poly);
						void AddHead(RgPolygon  *poly);
						void Insert(int nIndex, RgPolygon *poly);		
						const RgPolygon *GetAt(int nIndex)const;
						void operator = (RgPolygonList const &polygonList);

					};

					class RGEOS_API RgSize
					{
						// TODO: 在此处添加此类的方法。
					private:
						int m_nWidth;
						int m_nHeight;

					public:
						RgSize();
						RgSize(int nWidth, int nHeight);
						RgSize( RgSize const &size);
						int GetWidth()const;
						int GetHeight()const;
						void SetWidth(int nWidth);
						void SetHeight(int nHeight);
						void operator =(RgSize const &size);
					};

					class RGEOS_API RgRectangle
					{
						// TODO: 在此处添加此类的方法。
					private:
						double m_dfUpLeftX;
						double m_dfUpLeftY;
						double m_dfDownRightX;
						double m_dfDownRightY;

					public:
						RgRectangle();
						RgRectangle(double dfUpLeftX, double dfUpLeftY, double dfDownRightX, double dfDownRightY);
						RgRectangle(RgPointF  pointUpLeft, RgSize  size);
						RgRectangle(RgRectangle const &rect);
						double GetLeft()const;
						double GetRight()const;
						double GetTop()const;
						double GetBottom()const;
						void SetLeft(double dfUpLeftX);
						void SetRight(double dfDownRightX);
						void SetTop(double dfUpLeftY);
						void SetBottom(double dfDownRightY);
						void operator =(RgRectangle const &rect);
					};

					class RGEOS_API RgSpatialRelation
					{
						// TODO: 在此处添加此类的方法。
					private:
						static double Mult(const RgPointF *pointFirst, const RgPointF *pointSecond, const RgPointF *pointThird);
					public:
						RgSpatialRelation();
						// point是否包含在rect中
						static bool Contains(const RgPointF *point, const RgRectangle *rect);
						// point是否包含在poly中
						static bool Contains(const RgPointF  *point, const RgPolygon  *poly);
						// rectSecond是否包含rectFirst
						static bool Contains(const RgRectangle *rectFirst, const RgRectangle *rectSecond);
						// 两条线段是否相交
						static bool Intersects(const RgLineSegment *lineFirst, const RgLineSegment *lineSecond);
						// 两个rect是否相交，该相交包括其中一个包含另一个的情况
						static bool Intersects(const RgRectangle *rectFirst, const RgRectangle *rectSecond);
						// 两个poly是否相交，该相交包括其中一个包含另一个
						static bool Intersects(const RgPolygon *polyFirst, const RgPolygon *polySecond);
						// rect与poly是否相交，该相交包括其中一个包含另一个
						static bool Intersects(const RgRectangle *rect, const RgPolygon *poly);

					};

					class RGEOS_API RgSpatialOperator 
					{
						// TODO: 在此处添加此类的方法。
					public:
						RgSpatialOperator();
						// 计算两条线段的交点
						static bool Intersection(const RgLineSegment *lineFirst, const RgLineSegment *lineSecond, RgPointF &ptIntersection);		
						// 将rectFirst和rectSecond合并为一个rect
						static bool Union(const RgRectangle *rectFirst, const RgRectangle *rectSecond, RgRectangle &objrectUnion);
						// 计算几何对象的最小外接矩形
						static bool Boundary(const RgPolygon  *poly, RgRectangle &objrectBoundary);
						// 计算两个矩形的交集
						static bool  Intersection(const RgRectangle  *rectFirst, const RgRectangle  *rectSecond,RgRectangle &rectIntersection);					
					};
				
					class RGEOS_API RgTileLocation
					{
						// TODO: 在此处添加此类的方法。
					private:
						int m_iCol;
						int m_iRow;

					public:				
						RgTileLocation();
						RgTileLocation(RgTileLocation const &tl);
						RgTileLocation(int nCol, int nRow);				
						int GetCol()const;
						void SetCol(int nCol);
						int GetRow()const;
						void SetRow(int nRow);
						bool operator == (RgTileLocation tl)const;
						void operator =(RgTileLocation const &tilelocation);
					};
			
	}

}