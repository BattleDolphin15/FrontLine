#pragma once
#include "GL.h"
#include "Effect.h"

class EffectManager
{
private:
	std::shared_ptr<Effect> m_Effects;
public:
	EffectManager();
	~EffectManager();
	
	std::shared_ptr<Effect> CreateEffect(const char* name);
	
	bool AddEffect(std::shared_ptr<Effect> effect);
	
	bool RemoveEffect(std::shared_ptr<Effect> effect);
	
	std::shared_ptr<Effect> GetEffect(const char* name);
}