#include "StdAfx.h"
#include "Layer.h"
#include "ScreenDisplay.h"

Layer::Layer(void)
{
}


Layer::~Layer(void)
{
}


// ����ͼ��
int Layer::Draw(ScreenDisplay* display)
{
	return 0;
}
void Layer:: setLayerName(string* name)
{
	LayerName=name;
}