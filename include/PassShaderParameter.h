#pragma once
#include "PassDesc.h"

class ShaderParameter : public PassDesc
{
protected:
	//dont need layerid cuz only one layer is ever active
	float* m_Value; //an array
public:
	//allocate size depending on value
	ShaderParameter(const char* name, float* value = NULL);
	virtual ~ShaderParameter();
	virtual void SetValue(float* value);
	virtual bool Update() { return true; }
};