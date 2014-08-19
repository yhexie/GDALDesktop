// ShapeLib.cpp : 定义 DLL 应用程序的入口点。
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

// 这是导出变量的一个示例
SHAPELIB_API int nShapeLib=0;

// 这是导出函数的一个示例。
SHAPELIB_API int fnShapeLib(void)
{
	return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 ShapeLib.h
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
  
	// 为了支持中文路径，请添加下面这句代码
	//CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");   //设置支持中文路径
    // 为了使属性表字段支持中文，请添加下面这句
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
	// 赋上已知的投影信息
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
    //下面创建属性表  
    OGRFieldDefn poFieldID("ID", OFTInteger);//创建ID字段  
    poLayer->CreateField(&poFieldID);  
  
    OGRFieldDefn poFieldname("Name", OFTString);//创建Name字段  
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
  
	pRing->closeRings();//首尾点重合形成闭合环  
          
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