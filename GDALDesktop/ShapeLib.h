// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SHAPELIB_EXTERN
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SHAPELIB_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef SHAPELIB_EXTERN
#define SHAPELIB_API __declspec(dllexport)
#else
#define SHAPELIB_API __declspec(dllimport)
#endif
#include "Geometry.h"
using namespace RGeos::Geometry;
// �����Ǵ� ShapeLib.dll ������
class SHAPELIB_API CShapeLib {
public:
	CShapeLib(void);
	~CShapeLib(void);
	// TODO: �ڴ�������ķ�����
	bool CreateShapeFileA(const char * shpfile,RgPolygon *polygon);
};

extern SHAPELIB_API int nShapeLib;

SHAPELIB_API int fnShapeLib(void);

//bool DeleteShapeFile(const char * shpfile);
