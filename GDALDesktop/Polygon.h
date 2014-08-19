#pragma once

#include "stdafx.h"
namespace EarthView 
{
	namespace TilesEngine
	{		
				namespace VectorSpatial
				{

					class TILESENGINECPP_API EVPoint
					{
						// TODO: 在此处添加此类的方法。
					private:
						int m_nX;
						int m_nY;

					public:				
						EVPoint();
						EVPoint(EVPoint const &pt);
						EVPoint(int nX, int nY);				
						int GetX()const;
						void SetX(int nX);
						int GetY()const;
						void SetY(int nY);
						bool operator == (EVPoint point)const;
						void operator =(EVPoint const &point);
					};

					
					class TILESENGINECPP_API EVPointF
					{
						// TODO: 在此处添加此类的方法。
					private:
						double m_dfX;
						double m_dfY;

					public:

						EVPointF();
						EVPointF(EVPointF const &pt);
						EVPointF(double dfX, double dfY);				
						double GetX()const;
						void SetX(double dfX);
						double GetY()const;
						void SetY(double dfY);
						bool operator == (EVPointF point)const;
						void operator =(EVPointF const &point);


					};

					// 线段，包含起点和终点
					class TILESENGINECPP_API EVLineSegment        
					{
						// TODO: 在此处添加此类的方法。
					private:
						EVPointF  m_pointStart;
						EVPointF  m_pointEnd;
					public:
						EVLineSegment();
						EVLineSegment(EVPointF  pointStart, EVPointF pointEnd);
						EVLineSegment(EVLineSegment const &lineSegment);
						void SetStartPoint(EVPointF point);
						void SetEndPoint(EVPointF point);
						EVPointF GetStartPoint()const;	
						EVPointF GetEndPoint()const;
						void operator =(EVLineSegment const &point);

					};

					class TILESENGINECPP_API EVPointFList        
					{
						// TODO: 在此处添加此类的方法。
					private:
						list<EVPointF>  m_listPoint;
					public:
						EVPointFList();
						~EVPointFList();
						EVPointFList( EVPointFList const& pointlist);
						int GetCount()const;
						void RemoveAt(int nIndex);
						void Clear();
						void AddTail(EVPointF  point);
						void AddHead(EVPointF  point);
						void Insert(int nIndex, EVPointF  point);	
						EVPointF  GetAt(int nIndex)const;
						void operator = (EVPointFList const &pointList);

					};

					// 多边形必须为闭合的（即首尾点相同）
					class TILESENGINECPP_API EVPolygon        
					{
						// TODO: 在此处添加此类的方法。
					private:
						list<EVPointF > m_listPoint;

					public:
						EVPolygon();
						~EVPolygon();
						EVPolygon( EVPolygon const& polygon);
						int GetCount()const;					
						bool Contains(EVPointF const point);
						void RemoveAt(int nIndex);
						void Clear();
						void AddTail(EVPointF  point);
						void AddHead(EVPointF  point);
						void Insert(int nIndex, EVPointF  point);		
						EVPointF  GetAt(int nIndex)const;
						bool operator == (EVPolygon polygon)const;			
						void operator = (EVPolygon const &polygon);
					};

					class TILESENGINECPP_API EVPolygonList
					{
						// TODO: 在此处添加此类的方法。
					private:
						list<EVPolygon *> m_listPolygon;

					public:
						EVPolygonList();
						~EVPolygonList();				
						int GetCount()const;					
						bool Contains(EVPolygon const poly);
						void RemoveAt(int nIndex);
						void Clear();
						void AddTail(EVPolygon  *poly);
						void AddHead(EVPolygon  *poly);
						void Insert(int nIndex, EVPolygon *poly);		
						const EVPolygon *GetAt(int nIndex)const;
						void operator = (EVPolygonList const &polygonList);

					};

					class TILESENGINECPP_API EVSize
					{
						// TODO: 在此处添加此类的方法。
					private:
						int m_nWidth;
						int m_nHeight;

					public:
						EVSize();
						EVSize(int nWidth, int nHeight);
						EVSize( EVSize const &size);
						int GetWidth()const;
						int GetHeight()const;
						void SetWidth(int nWidth);
						void SetHeight(int nHeight);
						void operator =(EVSize const &size);
					};

					class TILESENGINECPP_API EVRectangle
					{
						// TODO: 在此处添加此类的方法。
					private:
						double m_dfUpLeftX;
						double m_dfUpLeftY;
						double m_dfDownRightX;
						double m_dfDownRightY;

					public:
						EVRectangle();
						EVRectangle(double dfUpLeftX, double dfUpLeftY, double dfDownRightX, double dfDownRightY);
						EVRectangle(EVPointF  pointUpLeft, EVSize  size);
						EVRectangle(EVRectangle const &rect);
						double GetLeft()const;
						double GetRight()const;
						double GetTop()const;
						double GetBottom()const;
						void SetLeft(double dfUpLeftX);
						void SetRight(double dfDownRightX);
						void SetTop(double dfUpLeftY);
						void SetBottom(double dfDownRightY);
						void operator =(EVRectangle const &rect);
					};

					class TILESENGINECPP_API EVSpatialRelation
					{
						// TODO: 在此处添加此类的方法。
					private:
						static double Mult(const EVPointF *pointFirst, const EVPointF *pointSecond, const EVPointF *pointThird);
					public:
						EVSpatialRelation();
						// point是否包含在rect中
						static bool Contains(const EVPointF *point, const EVRectangle *rect);
						// point是否包含在poly中
						static bool Contains(const EVPointF  *point, const EVPolygon  *poly);
						// rectSecond是否包含rectFirst
						static bool Contains(const EVRectangle *rectFirst, const EVRectangle *rectSecond);
						// 两条线段是否相交
						static bool Intersects(const EVLineSegment *lineFirst, const EVLineSegment *lineSecond);
						// 两个rect是否相交，该相交包括其中一个包含另一个的情况
						static bool Intersects(const EVRectangle *rectFirst, const EVRectangle *rectSecond);
						// 两个poly是否相交，该相交包括其中一个包含另一个
						static bool Intersects(const EVPolygon *polyFirst, const EVPolygon *polySecond);
						// rect与poly是否相交，该相交包括其中一个包含另一个
						static bool Intersects(const EVRectangle *rect, const EVPolygon *poly);

					};

					class TILESENGINECPP_API EVSpatialOperator 
					{
						// TODO: 在此处添加此类的方法。
					public:
						EVSpatialOperator();
						// 计算两条线段的交点
						static bool Intersection(const EVLineSegment *lineFirst, const EVLineSegment *lineSecond, EVPointF &ptIntersection);		
						// 将rectFirst和rectSecond合并为一个rect
						static bool Union(const EVRectangle *rectFirst, const EVRectangle *rectSecond, EVRectangle &objrectUnion);
						// 计算几何对象的最小外接矩形
						static bool Boundary(const EVPolygon  *poly, EVRectangle &objrectBoundary);
						// 计算两个矩形的交集
						static bool  Intersection(const EVRectangle  *rectFirst, const EVRectangle  *rectSecond,EVRectangle &rectIntersection);					
					};


				
					class TILESENGINECPP_API EVTileLocation
					{
						// TODO: 在此处添加此类的方法。
					private:
						int m_iCol;
						int m_iRow;

					public:				
						EVTileLocation();
						EVTileLocation(EVTileLocation const &tl);
						EVTileLocation(int nCol, int nRow);				
						int GetCol()const;
						void SetCol(int nCol);
						int GetRow()const;
						void SetRow(int nRow);
						bool operator == (EVTileLocation tl)const;
						void operator =(EVTileLocation const &tilelocation);
					};
				}
			
	}

}