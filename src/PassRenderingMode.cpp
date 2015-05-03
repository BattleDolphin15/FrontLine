#include "PassRenderingMode.h"

RenderingMode::RenderingMode(fxState renderMode)
: PassDesc(FX_RENDERMODE_DESC_FLAG) 
{
	m_RenderingMode = renderMode;
}
bool RenderingMode::Execute() 
{
	switch (m_RenderingMode) 
	{
	case FX_DRAW_FULLSCREEN_QUAD:
		flFxCore::Get()->DrawFullscreenQuad();
		break;
	case FX_DRAW_TRIANGLE:
		flFxCore::Get()->DrawTriangle(0, 0, 0);
		break;
	case FX_DO_NOTHING:
		break;
	}
	return true;
}