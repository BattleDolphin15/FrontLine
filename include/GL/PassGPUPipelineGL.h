#pragma once
#include "PassDesc.h"

class GPUPipeline : public PassDesc
{
public:
	GPUPipeline()
		: PassDesc(FX_PIPELINE_DESC_FLAG) {}
	virtual ~GPUPipeline() {}
};