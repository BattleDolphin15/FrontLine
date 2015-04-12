#pragma once
#include <tuple>
#include "Effect.h"
#include "pugixml/pugiconfig.hpp"
#include "pugixml/pugixml.hpp"

//for all state parameters:
//for example:
//FX_BLEND_FUNC src = "FX_ONE" dst = "FX_ONE"
//FX_BLEND_FUNC is function name
//src and dst are parameters that take place of GL state
//maybe put the typename T in the member functions
class StateInterpreter
{
private:				//state	 GLenum
	std::map<fxState,std::pair<void*,const char*>> m_States;
public:
	StateInterpreter() {}
	~StateInterpreter() {}
	template<typename T>
	void RegisterState(fxState state, T state1, const char* xmlName) {
		m_States[state].first = static_cast<void*>(new T(state1));
		m_States[state].second = xmlName;
	}
	template<typename T>
	T Convert(fxState state) {
		if (m_States.count(state) > 0) {
			return *static_cast<T*>(m_States.at(state).first);
		}
		return NULL;
	}
	template<typename T>
	T Convert(const char* state) {
		return Convert<T>(ToState(state));
	}
	template<typename T>
	fxState Convert(T state) {
		for (auto iter = m_States.begin(); iter != m_States.end(); iter++) {
			T s = *static_cast<T*>(iter->second.first);
			if (state == s) {
				return iter->first;
			}
		}
		return NULL;
	}
	const char* ToString(fxState state) {
		if (m_States.count(state) > 0) {
			return m_States.at(state).second;
		}
		return NULL;
	}
	fxState ToState(const char* state) {
		for (auto iter = m_States.begin(); iter != m_States.end(); iter++) {
			if (strcmp(state, iter->second.second) == 0) {
				return iter->first;
			}
		}
		return NULL;
	}
	static std::shared_ptr<StateInterpreter> Get();
};
struct BlankState {
	fxState m_State;
	BlankState() {}
	BlankState(fxState state) {m_State = state;}
	virtual ~BlankState() {}
	virtual const char* GetName() { return StateInterpreter::Get()->ToString(m_State); }
	virtual bool Load(pugi::xml_node node) { return true; } //for flFxParserGL
	virtual bool Apply() { return true; }
	virtual bool Cleanup() { return true; }
};
template<typename T>
struct State1 : public BlankState 
{
	T m_v;
	State1(fxState state, T v) 
		: BlankState(state) {
		m_v = v;
	}
	State1() {}
	virtual ~State1() {}
};
template<typename T1, typename T2>
struct State2 : public BlankState 
{
	T1 m_v1;
	T2 m_v2;
	State2(fxState state, T1 v1, T2 v2) 
		: BlankState(state) {
		m_v1 = v1;
		m_v2 = v2;
	}
	State2() {}
	virtual ~State2() {}
};
template<typename T1, typename T2, typename T3>
struct State3 : public BlankState
{
	T1 m_v1;
	T2 m_v2;
	T3 m_v3;
	State3(fxState state, T1 v1, T2 v2, T3 v3)
		: BlankState(state) {
		m_v1 = v1;
		m_v2 = v2;
		m_v3 = v3;
	}  
	State3() {}
	virtual ~State3() {}

};
template<typename T1, typename T2, typename T3, typename T4>
struct State4 : public BlankState
{
	T1 m_v1;
	T2 m_v2;
	T3 m_v3;
	T4 m_v4;
	State4(fxState state, T1 v1, T2 v2, T3 v3, T4 v4)
		: BlankState(state) {
		m_v1 = v1;
		m_v2 = v2;
		m_v3 = v3;
		m_v4 = v4;
	}
	State4() {}
	virtual ~State4() {}
};

class StateGroup : public PassDesc
{
protected:
	std::list<std::shared_ptr<BlankState>>m_States;
public:
	StateGroup()
		: PassDesc(FX_STATE_GROUP_DESC_FLAG) {} //register fxState converts here
	~StateGroup() {}
	virtual bool AddState(std::shared_ptr<BlankState> state);
	virtual bool RemoveState(fxState state);
	std::shared_ptr<BlankState> FindState(fxState state);
	virtual bool Apply() {return true;}
};
//........//
class Shader : public PassDesc
{
protected:
	std::string m_Code;
public:
	Shader(const char* name)
		: PassDesc(FX_SHADER_DESC_FLAG,name) {}
	virtual ~Shader() {}
	virtual void ValidateAttachments();
	virtual bool Validate(); //dont need Pass* pass = NULL cuz of m_Parent
	virtual bool Invalidate();
};
class GPUPipeline : public PassDesc
{
protected:
	std::vector<std::shared_ptr<Shader>> m_Shaders; //this is better
public:
	GPUPipeline()
		: PassDesc(FX_PIPELINE_DESC_FLAG) {}
	virtual ~GPUPipeline() {}
	virtual bool SetShader(std::shared_ptr<Shader> shader);
	virtual void SetShaders(std::shared_ptr<Shader>* shaders,int count) {}
	virtual bool RemoveShader(const char* name);
	virtual std::shared_ptr<Shader> GetShader(const char* name);
	virtual std::shared_ptr<Shader> GetShader(int index);
	virtual void ClearAll() {m_Shaders.clear();}
};
//........//
class SamplerState
{
protected:
	const char* m_Name;
	std::vector<std::shared_ptr<BlankState>>m_States;
public:
	SamplerState(const char* name) {m_Name = name;}
	virtual ~SamplerState() {}
	void SetName(const char* name) {m_Name = name;}
	const char* GetName() {return m_Name;}
	virtual bool Validate() {return true;}
	virtual bool Invalidate() {return true;}
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
	Resource(const char* name,fxState resType);
	virtual ~Resource();
	virtual void ValidateAttachments();
	virtual bool Validate(); //if is rendertex, add to fbo
	virtual bool Invalidate(); //if is rendertex, remove from fbo
	virtual void SetSamplerState(std::shared_ptr<SamplerState> sstate) {m_Data.samplerState = sstate;}
	virtual std::shared_ptr<SamplerState> GetSamplerState() {return m_Data.samplerState;}
	virtual void SetDimensions(int w,int h = 0, int d = 0);
	virtual int GetWidth() {return m_Data.dimensions[0];}
	virtual int GetHeight() {return m_Data.dimensions[1];}
	virtual int GetDepth() {return m_Data.dimensions[2];}
	virtual void SetDimensionAppDependent(bool size) {m_Data.appDepSize = size;}
	virtual bool GetDimensionAppDependent() {return m_Data.appDepSize;}
	virtual void SetMSAAActive(bool msaa) {m_Data.msaa = msaa;}
	virtual bool GetMSAAActive() {return m_Data.msaa;}
	virtual void SetMSAASamples(unsigned int samples) {m_Data.msaaSamples = samples;}
	virtual unsigned int GetMSAASamples() {return m_Data.msaaSamples;}
	virtual void SetFormat(fxState fmt) {m_Data.format = fmt;}
	virtual fxState GetFormat() {return m_Data.format;}
	virtual fxState GetResourceType() { return m_ResourceType; }
	virtual bool IsValid() {return false;}
	virtual bool Update() {return true;}
};
class FrameBufferObject : public PassDesc
{
protected:
	std::shared_ptr<Resource> m_DSTResource;
	std::vector<std::shared_ptr<Resource>>m_Resources;
	//std::vector<const char*> m_Resources; //u can hold names instead for searchup
public:
	FrameBufferObject(const char* name);
	virtual ~FrameBufferObject();
	virtual bool Validate();
	virtual bool Invalidate();
	virtual void SetDSTTexture(std::shared_ptr<Resource> res) {m_DSTResource = res;}
	virtual std::shared_ptr<Resource> GetDSTTexture() {return m_DSTResource;}
	virtual bool AddTextureResource(std::shared_ptr<Resource> res);
	virtual std::shared_ptr<Resource> GetTextureResource(int index);
	virtual void SetCurrent() {}
	virtual void ReleaseCurrent() {}
	virtual void BlitTo(std::shared_ptr<FrameBufferObject> dst) {}
	virtual int GetNumResources() {return (int)m_Resources.size();}
};
class ShaderParameter : public PassDesc
{
protected:
	//dont need layerid cuz only one layer is ever active
	float* m_Value; //an array
public:
	//allocate size depending on value
	ShaderParameter(const char* name,float* value = NULL); 
	virtual ~ShaderParameter();
	virtual void SetValue(float* value);
	virtual bool Update() {return true;}
};
//........//