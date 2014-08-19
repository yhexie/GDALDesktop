#pragma once
#include "stdafx.h"

namespace RGeos 
{
	namespace Geometry
	{		
					class RGEOS_API RgPoint
					{
						// TODO: �ڴ˴���Ӵ���ķ�����
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
						// TODO: �ڴ˴���Ӵ���ķ�����
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

					// �߶Σ����������յ�
					class RGEOS_API RgLineSegment        
					{
						// TODO: �ڴ˴���Ӵ���ķ�����
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
						// TODO: �ڴ˴���Ӵ���ķ�����
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

					// ����α���Ϊ�պϵģ�����β����ͬ��
					class RGEOS_API RgPolygon        
					{
						// TODO: �ڴ˴���Ӵ���ķ�����
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
						// TODO: �ڴ˴���Ӵ���ķ�����
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
						// TODO: �ڴ˴���Ӵ���ķ�����
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
						// TODO: �ڴ˴���Ӵ���ķ�����
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
						// TODO: �ڴ˴���Ӵ���ķ�����
					private:
						static double Mult(const RgPointF *pointFirst, const RgPointF *pointSecond, const RgPointF *pointThird);
					public:
						RgSpatialRelation();
						// point�Ƿ������rect��
						static bool Contains(const RgPointF *point, const RgRectangle *rect);
						// point�Ƿ������poly��
						static bool Contains(const RgPointF  *point, const RgPolygon  *poly);
						// rectSecond�Ƿ����rectFirst
						static bool Contains(const RgRectangle *rectFirst, const RgRectangle *rectSecond);
						// �����߶��Ƿ��ཻ
						static bool Intersects(const RgLineSegment *lineFirst, const RgLineSegment *lineSecond);
						// ����rect�Ƿ��ཻ�����ཻ��������һ��������һ�������
						static bool Intersects(const RgRectangle *rectFirst, const RgRectangle *rectSecond);
						// ����poly�Ƿ��ཻ�����ཻ��������һ��������һ��
						static bool Intersects(const RgPolygon *polyFirst, const RgPolygon *polySecond);
						// rect��poly�Ƿ��ཻ�����ཻ��������һ��������һ��
						static bool Intersects(const RgRectangle *rect, const RgPolygon *poly);

					};

					class RGEOS_API RgSpatialOperator 
					{
						// TODO: �ڴ˴���Ӵ���ķ�����
					public:
						RgSpatialOperator();
						// ���������߶εĽ���
						static bool Intersection(const RgLineSegment *lineFirst, const RgLineSegment *lineSecond, RgPointF &ptIntersection);		
						// ��rectFirst��rectSecond�ϲ�Ϊһ��rect
						static bool Union(const RgRectangle *rectFirst, const RgRectangle *rectSecond, RgRectangle &objrectUnion);
						// ���㼸�ζ������С��Ӿ���
						static bool Boundary(const RgPolygon  *poly, RgRectangle &objrectBoundary);
						// �����������εĽ���
						static bool  Intersection(const RgRectangle  *rectFirst, const RgRectangle  *rectSecond,RgRectangle &rectIntersection);					
					};
				
					class RGEOS_API RgTileLocation
					{
						// TODO: �ڴ˴���Ӵ���ķ�����
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