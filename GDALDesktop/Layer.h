#pragma once
class ScreenDisplay;
class Layer
{
public:
	Layer(void);
	~Layer(void);
	string* LayerName;
	int ShapeType;
	virtual void setLayerName(string* name);
	// ªÊ÷∆Õº≤„
	virtual int Draw(ScreenDisplay* display);
};

