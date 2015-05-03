#pragma once
#include "PassDesc.h"

struct BlankState 
{
	fxState m_State;
	
	BlankState() {}
	BlankState(fxState state) { m_State = state; }
	virtual ~BlankState() {}
	
	virtual const char* GetName() { return StateInterpreter::Get()->ToString(m_State); }
	
	virtual bool Load(pugi::xml_node node) { return true; } //for flFxParserGL
	virtual bool Apply() { return true; }
	virtual bool Cleanup() { return true; }
};

class StateInterpreter
{
private:				//state	 GLenum
	std::map<fxState, std::pair<void*, const char*>> m_States;
public:
	StateInterpreter() {}
	~StateInterpreter() {}
	
	template<typename T>
	void RegisterState(fxState state, T state1, const char* xmlName) 
	{
		m_States[state].first = static_cast<void*>(new T(state1));
		m_States[state].second = xmlName;
	}
	
	template<typename T>
	T Convert(fxState state) 
	{
		if (m_States.count(state) > 0) 
		{
			return *static_cast<T*>(m_States.at(state).first);
		}
		return NULL;
	}
	
	template<typename T>
	T Convert(const char* state) 
	{
		return Convert<T>(ToState(state));
	}
	
	template<typename T>
	fxState Convert(T state) 
	{
		for (auto iter = m_States.begin(); iter != m_States.end(); iter++) 
		{
			T s = *static_cast<T*>(iter->second.first);
			if (state == s) 
			{
				return iter->first;
			}
		}
		return NULL;
	}
	
	const char* ToString(fxState state) 
	{
		if (m_States.count(state) > 0) 
		{
			return m_States.at(state).second;
		}
		return NULL;
	}
	
	fxState ToState(const char* state) 
	{
		for (auto iter = m_States.begin(); iter != m_States.end(); iter++) 
		{
			if (strcmp(state, iter->second.second) == 0) {
				return iter->first;
			}
		}
		return NULL;
	}
	
	static std::shared_ptr<StateInterpreter> Get();
};