#pragma once
#include "PassDesc.h"

//subset of generic object factory
class EffectFactory
{
public:
	std::shared_ptr<PassDesc> Create(fxState flag);
}