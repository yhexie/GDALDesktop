#include "StdAfx.h"
#include "RgFeatureLayer.h"
#include "Layer.h"
#include "ScreenDisplay.h"

RgFeatureLayer::RgFeatureLayer(void)
{
	mGeosList=new vector<OGRGeometry*>;
}


RgFeatureLayer::~RgFeatureLayer(void)
{
}

int RgFeatureLayer::Draw(ScreenDisplay* display)
{
	if(display!=NULL)
	{
		display->DrawPolyline();
	}
	if(this->ShapeType==0)
	{
		if(mGeosList->size()>0)
		{
			vector<OGRGeometry*>::iterator first=mGeosList->begin();

			for(vector<OGRGeometry*>::iterator it =first; it !=mGeosList->end() ; it++) ///第二种调用方法  
			{
				OGRGeometry*geo=*it;
				display->SetSymbol(Color::Red,2);
				const char* na=typeid(geo).raw_name();
				OGRPoint* ogrPt=dynamic_cast<OGRPoint*>(geo);
				display->DrawPoint(ogrPt);
			} 
		}
	}
	else if(this->ShapeType==1)
	{
		vector<OGRGeometry*>::iterator first=mGeosList->begin();

			for(vector<OGRGeometry*>::iterator it =first; it !=mGeosList->end() ; it++) ///第二种调用方法  
			{
				OGRGeometry*lyr=*it;
				display->DrawPolyline();
			} 
	}
	else if(this->ShapeType==2)
	{
		vector<OGRGeometry*>::iterator first=mGeosList->begin();

			for(vector<OGRGeometry*>::iterator it =first; it !=mGeosList->end() ; it++) ///第二种调用方法  
			{
				OGRGeometry*lyr=*it;
				display->DrawPolyline();
			} 
	}
	return 0;
}

void RgFeatureLayer::setLayerName(string* name)
{
	LayerName=name;
}
void RgFeatureLayer::AddShape(OGRGeometry* geo)
{
	mGeosList->push_back(geo);
}
