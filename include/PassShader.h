#pragma once
#include "Pass.h"

class Shader
{
protected:
	std::string m_Code;
public:
	Shader(const char* name)
		: PassDesc(FX_SHADER_DESC_FLAG,name) {}
	virtual ~Shader() {}
	
	virtual bool Validate(); //dont need Pass* pass = NULL cuz of m_Parent
	virtual bool Invalidate();
};