#pragma once
#include "Layer.h"
class ScreenDisplay;
class RgFeatureLayer: public Layer
{
public:
	RgFeatureLayer(void);
	~RgFeatureLayer(void);
	int Draw(ScreenDisplay* display);
public:
	OGRGeometry* NewObj;
	vector<OGRGeometry*>  *mGeosList;
	void AddShape(OGRGeometry* geo);
	void setLayerName(string* name);
};

