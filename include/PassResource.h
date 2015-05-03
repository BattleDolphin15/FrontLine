#pragma once
#include "PassState.h"

class SamplerState
{
protected:
	const char* m_Name;
	std::vector<std::shared_ptr<BlankState>>m_States;
public:
	SamplerState(const char* name) { m_Name = name; }
	virtual ~SamplerState() {}
	
	void SetName(const char* name) { m_Name = name; }
	const char* GetName() { return m_Name; }
	
	virtual bool Validate() { return true; }
	virtual bool Invalidate() { return true; }
	
	virtual bool AddState(std::shared_ptr<BlankState> state);
	
	virtual std::shared_ptr<BlankState> FindState(fxState state);
	
	virtual bool RemoveState(fxState state);
};
//........//
class Resource : public PassDesc
{
protected:
	struct ResourceData {
		bool appDepSize;
		unsigned int dimensions[3];
		bool msaa;
		unsigned int msaaSamples;
		std::shared_ptr<SamplerState> samplerState;
		fxState format;
		//BlankState format;
		bool external;
	};
	fxState m_ResourceType;
	//BlankState m_ResourceType;
	ResourceData m_Data;
public:
	Resource(const char* name, fxState resType);
	virtual ~Resource();
	
	virtual void ValidateAttachments();
	
	virtual void SetSamplerState(std::shared_ptr<SamplerState> sstate) { m_Data.samplerState = sstate; }
	virtual std::shared_ptr<SamplerState> GetSamplerState() { return m_Data.samplerState; }
	virtual void SetDimensions(int w, int h = 0, int d = 0);
	virtual int GetWidth() { return m_Data.dimensions[0]; }
	virtual int GetHeight() { return m_Data.dimensions[1]; }
	virtual int GetDepth() { return m_Data.dimensions[2]; }
	virtual void SetDimensionAppDependent(bool size) { m_Data.appDepSize = size; }
	virtual bool GetDimensionAppDependent() { return m_Data.appDepSize; }
	virtual void SetMSAAActive(bool msaa) { m_Data.msaa = msaa; }
	virtual bool GetMSAAActive() { return m_Data.msaa; }
	virtual void SetMSAASamples(unsigned int samples) { m_Data.msaaSamples = samples; }
	virtual unsigned int GetMSAASamples() { return m_Data.msaaSamples; }
	virtual void SetFormat(fxState fmt) { m_Data.format = fmt; }
	virtual fxState GetFormat() { return m_Data.format; }
	virtual fxState GetResourceType() { return m_ResourceType; }
	
	virtual bool IsValid() { return false; }
	
	virtual bool Update() { return true; }
};