#pragma once
#include "PassDesc.h"

class FrameBufferObject : public PassDesc
{
public:
	FrameBufferObject(const char* name);
	virtual ~FrameBufferObject();
	
	virtual void SetCurrent() {}
	virtual void ReleaseCurrent() {}
	
	virtual void BlitTo(std::shared_ptr<FrameBufferObject> dst) {}
};