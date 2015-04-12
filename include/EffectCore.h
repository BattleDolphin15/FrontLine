#pragma once

class EffectCore
{
public:
	EffectCore() {}
	~EffectCore() {}

	virtual bool Init() { return true; }
	virtual bool Shutdown() { return true; }
	virtual void DrawFullscreenQuad() {}
	virtual void DrawTriangle(int x, int y, int z) {}
};