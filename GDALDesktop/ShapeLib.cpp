// ShapeLib.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ShapeLib.h"
#include "Geometry.h"
//using namespace EarthView::TilesEngine;
using namespace RGeos::Geometry;
#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

// ���ǵ���������һ��ʾ��
SHAPELIB_API int nShapeLib=0;

// ���ǵ���������һ��ʾ����
SHAPELIB_API int fnShapeLib(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� ShapeLib.h
CShapeLib::CShapeLib()
{
	return;
}
CShapeLib::~CShapeLib(void)
{
}
bool DeleteShapeFile(const char * shpfile);
bool CShapeLib::CreateShapeFileA(const char *shpfile, RgPolygon *polygon)
{
	DeleteShapeFile(shpfile);

	const char *pszDriverName = "ESRI Shapefile";  
    OGRSFDriver *poDriver;  
  
	// Ϊ��֧������·�������������������
	//CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");   //����֧������·��
    // Ϊ��ʹ���Ա��ֶ�֧�����ģ�������������
    //CPLSetConfigOption("SHAPE_ENCODING","");
	
    OGRRegisterAll();  
  
    poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(pszDriverName);  
    if (poDriver == NULL)  
    {  
		return false;
	}  
  
    OGRDataSource *poDS;  
    poDS = poDriver->CreateDataSource(shpfile, NULL);  
    if (poDS == NULL)  
    {  
		return false; 
    }  

    OGRLayer *poLayer;  
	// ������֪��ͶӰ��Ϣ
	OGRSpatialReference *poSrcSRS=new OGRSpatialReference();
	char *pszSrcWkt = NULL;
	 
	/*oSrcSRS.SetWellKnownGeogCS("WGS84");  
	oSrcSRS.exportToWkt(&pszSrcWkt);*/

	const char * prj = "PROJCS[\"Popular Visualisation CRS / Mercator\",GEOGCS[\"Popular Visualisation CRS\",DATUM[\"Popular_Visualisation_Datum\",SPHEROID[\"Popular_Visualisation_Sphere\",6378137.0,0.0]],PRIMEM[\"Greenwich\",0.0],UNIT[\"Degree\",0.0174532925199433]],PROJECTION[\"Mercator_1SP\"],PARAMETER[\"false_easting\",0.0],PARAMETER[\"false_northing\",0.0],PARAMETER[\"central_meridian\",0.0],PARAMETER[\"scale_factor\",1.0],UNIT[\"Meter\",1.0]]";
	poSrcSRS->SetFromUserInput(prj);

	//CPLErr err;	
	//err = GDALSetProjection((OGRDataSourceH)poDS, pszSrcWkt);
	//OGRFree(pszSrcWkt);
	//if (err != CE_None)
	//{
	//	return false;
	//}

	poLayer = poDS->CreateLayer("polygon1", poSrcSRS, wkbPolygon, NULL);  

    if (poLayer == NULL)  
    {  
		return false;
    }  
    //���洴�����Ա�  
    OGRFieldDefn poFieldID("ID", OFTInteger);//����ID�ֶ�  
    poLayer->CreateField(&poFieldID);  
  
    OGRFieldDefn poFieldname("Name", OFTString);//����Name�ֶ�  
    poFieldname.SetWidth(32);  
    poLayer->CreateField(&poFieldname);  
  
	OGRLinearRing *pRing=new OGRLinearRing();  

	OGRFeature *poFeature;  

	string szname = "a_1";  
        
    poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );  

    poFeature->SetField(0, 1);  
    poFeature->SetField(1, szname.c_str());  

    for (int i  = 0; i < polygon->GetCount(); i++)  
    {  
  
		RgPointF p=polygon->GetAt(i);
		
	/*	RgPointF *pp = CGoogleMathEngine::WGS84ToWebMercator(&p);
*/
		pRing->addPoint(p.GetX(), p.GetY());   

		//delete pp;
        
    }  
  
	pRing->closeRings();//��β���غ��γɱպϻ�  
          
    OGRPolygon *pogrpolygon=new OGRPolygon();  
    pogrpolygon->addRing(pRing);  
    poFeature->SetGeometry(pogrpolygon);  

    if ( poLayer->CreateFeature( poFeature) != OGRERR_NONE)  
    {  
		return false;
    }  
	
    OGRFeature::DestroyFeature(poFeature);  
	
    OGRDataSource::DestroyDataSource(poDS); 
	
	OGRCleanupAll();
	delete pogrpolygon;
	return true;
}