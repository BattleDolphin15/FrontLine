#include "PassShaderParameter.h"

ShaderParameter::ShaderParameter(const char* name, float* value)
: PassDesc(FX_SHADER_PARAMETER_DESC_FLAG, name) 
{
	if (value) 
	{
		m_Value = value;
	}
	//flFxCore::Get().GetShaderParameterRepository()->RemoveItem(this);
}

ShaderParameter::~ShaderParameter() 
{
	delete[] m_Value;
	//flFxCore::Get().GetShaderParameterRepository()->RemoveItem(this);
}

void ShaderParameter::SetValue(float* value) 
{
	if (value) 
	{
		m_Value = value;
	}
}
