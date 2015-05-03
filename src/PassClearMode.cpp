#include "PassClearMode.h"

ClearMode::ClearMode(fxState clear1, fxState clear2, fxState clear3)
	: PassDesc(FX_CLEARMODE_DESC_FLAG)
{
	m_ClearMode[0] = clear1;
	m_ClearMode[1] = clear2;
	m_ClearMode[2] = clear3;
}

void ClearMode::SetClearMode(fxState clear1, fxState clear2, fxState clear3)
{
	m_ClearMode[0] = clear1;
	m_ClearMode[1] = clear2;
	m_ClearMode[2] = clear3;
}