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
	// ����ͼ��
	virtual int Draw(ScreenDisplay* display);
};

