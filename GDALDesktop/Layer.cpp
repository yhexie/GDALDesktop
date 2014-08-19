#include "StdAfx.h"
#include "Layer.h"
#include "ScreenDisplay.h"

Layer::Layer(void)
{
}


Layer::~Layer(void)
{
}


// ªÊ÷∆Õº≤„
int Layer::Draw(ScreenDisplay* display)
{
	return 0;
}
void Layer:: setLayerName(string* name)
{
	LayerName=name;
}