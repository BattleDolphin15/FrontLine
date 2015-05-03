#pragma once
#include "PassDesc.h"

class ClearMode : public PassDesc
{
private:
	fxState m_ClearMode[3];
public:
	ClearMode(fxState clear1, fxState clear2 = FX_DO_NOTHING, fxState clear3 = FX_DO_NOTHING);
	virtual ~ClearMode() {}
	virtual void SetClearMode(fxState clear1, fxState clear2 = FX_DO_NOTHING, fxState clear3 = FX_DO_NOTHING);
	virtual bool Execute();
};