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
						// TODO: �ڴ˴���Ӵ���ķ�����
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
						// TODO: �ڴ˴���Ӵ���ķ�����
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

					// �߶Σ����������յ�
					class TILESENGINECPP_API EVLineSegment        
					{
						// TODO: �ڴ˴���Ӵ���ķ�����
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
						// TODO: �ڴ˴���Ӵ���ķ�����
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

					// ����α���Ϊ�պϵģ�����β����ͬ��
					class TILESENGINECPP_API EVPolygon        
					{
						// TODO: �ڴ˴���Ӵ���ķ�����
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
						// TODO: �ڴ˴���Ӵ���ķ�����
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
						// TODO: �ڴ˴���Ӵ���ķ�����
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
						// TODO: �ڴ˴���Ӵ���ķ�����
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
						// TODO: �ڴ˴���Ӵ���ķ�����
					private:
						static double Mult(const EVPointF *pointFirst, const EVPointF *pointSecond, const EVPointF *pointThird);
					public:
						EVSpatialRelation();
						// point�Ƿ������rect��
						static bool Contains(const EVPointF *point, const EVRectangle *rect);
						// point�Ƿ������poly��
						static bool Contains(const EVPointF  *point, const EVPolygon  *poly);
						// rectSecond�Ƿ����rectFirst
						static bool Contains(const EVRectangle *rectFirst, const EVRectangle *rectSecond);
						// �����߶��Ƿ��ཻ
						static bool Intersects(const EVLineSegment *lineFirst, const EVLineSegment *lineSecond);
						// ����rect�Ƿ��ཻ�����ཻ��������һ��������һ�������
						static bool Intersects(const EVRectangle *rectFirst, const EVRectangle *rectSecond);
						// ����poly�Ƿ��ཻ�����ཻ��������һ��������һ��
						static bool Intersects(const EVPolygon *polyFirst, const EVPolygon *polySecond);
						// rect��poly�Ƿ��ཻ�����ཻ��������һ��������һ��
						static bool Intersects(const EVRectangle *rect, const EVPolygon *poly);

					};

					class TILESENGINECPP_API EVSpatialOperator 
					{
						// TODO: �ڴ˴���Ӵ���ķ�����
					public:
						EVSpatialOperator();
						// ���������߶εĽ���
						static bool Intersection(const EVLineSegment *lineFirst, const EVLineSegment *lineSecond, EVPointF &ptIntersection);		
						// ��rectFirst��rectSecond�ϲ�Ϊһ��rect
						static bool Union(const EVRectangle *rectFirst, const EVRectangle *rectSecond, EVRectangle &objrectUnion);
						// ���㼸�ζ������С��Ӿ���
						static bool Boundary(const EVPolygon  *poly, EVRectangle &objrectBoundary);
						// �����������εĽ���
						static bool  Intersection(const EVRectangle  *rectFirst, const EVRectangle  *rectSecond,EVRectangle &rectIntersection);					
					};


				
					class TILESENGINECPP_API EVTileLocation
					{
						// TODO: �ڴ˴���Ӵ���ķ�����
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