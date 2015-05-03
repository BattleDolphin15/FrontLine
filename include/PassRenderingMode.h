#pragma once
#include "PassDesc.h"

class RenderingMode : public PassDesc
{
private:
	fxState m_RenderingMode;
public:
	RenderingMode(fxState renderMode);
	virtual ~RenderingModeGL() {}
	virtual fxState GetRenderingMode() { return m_RenderingMode; }
	virtual bool Execute(); //draw fullscreen quad or do nothing
};