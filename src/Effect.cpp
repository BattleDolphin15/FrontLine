#include "Effect.h"

Effect::Effect(const char* name)
{
	m_Name = name;
}

Effect::~Effect() 
{
}

bool Effect::Execute(std::shared_ptr<Pass> pass, fxState flag, const char* name)
{
	return true;
}

bool Effect::Execute(std::shared_ptr<Pass> pass, const char* name)
{
	return true;
}

void Effect::CreatePassData(std::shared_ptr<PassDesc> data)
{
}

std::shared_ptr<PassDesc> Effect::CreatePassData(fxState flag, const char* name, bool add)
{
	return nullptr;
}

std::shared_ptr<PassDesc> Effect::Find(const char* name)
{
	return nullptr;
}

const std::shared_ptr<PassDesc> Effect::Find(const char* name) const
{
	return nullptr;
}

std::shared_ptr<PassDesc> Effect::Find(fxState flag)
{
	return nullptr;
}

const std::shared_ptr<PassDesc> Effect::Find(fxState flag) const
{
	return nullptr;
}

std::shared_ptr<PassDesc> Effect::Find(const char* techName, const char* passName, const char* name)
{
	return nullptr;
}

const std::shared_ptr<PassDesc> Effect::Find(const char* techName, const char* passName, const char* name) const
{
	return nullptr;
}

std::shared_ptr<PassDesc> Effect::Find(int techIndex, int passIndex, const char* name)
{
	return nullptr;
}

const std::shared_ptr<PassDesc> Effect::Find(int techIndex, int passIndex, const char* name) const
{
	return nullptr;
}

std::shared_ptr<PassDesc> Effect::Find(const char* techName, const char* passName, fxState flag)
{
	return nullptr;
}

const std::shared_ptr<PassDesc> Effect::Find(const char* techName, const char* passName, fxState flag) const
{
	return nullptr;
}

std::shared_ptr<PassDesc> Effect::Find(int techIndex, int passIndex, fxState flag)
{
	return nullptr;
}

const std::shared_ptr<PassDesc> Effect::Find(int techIndex, int passIndex, fxState flag) const
{
	return nullptr;
}

std::shared_ptr<Pass> Effect::CreatePass(const char* name)
{
	return nullptr;
}

std::shared_ptr<Pass> Effect::GetPass(const char* techName, const char* passName)
{
	return nullptr;
}

const std::shared_ptr<Pass> Effect::GetPass(const char* techName, const char* passName) const
{
	return nullptr;
}

std::shared_ptr<Pass> Effect::GetPass(int techIndex, int passIndex)
{
	return nullptr;
}

const std::shared_ptr<Pass> Effect::GetPass(int techIndex, int passIndex) const
{
	return nullptr;
}

bool Effect::AddTechnique(std::shared_ptr<Technique> technique) 
{
	for(auto iter = m_Techniques.begin(); iter != m_Techniques.end(); iter++) 
	{
		if((*iter) == technique) 
		{
			return false;
		}
	}
	m_Techniques.push_back(technique);
	return true;
}

std::shared_ptr<Technique> Effect::CreateTechnique(const char* name)
{
	return nullptr;
}

bool Effect::RemoveTechnique(std::shared_ptr<Technique> technique) 
{
	for(auto iter = m_Techniques.begin(); iter != m_Techniques.end(); iter++) 
	{
		if((*iter) == technique) 
		{
			m_Techniques.erase(iter);
			return true;
		}
	}
	return false;
}

bool Effect::RemoveTechnique(int index)
{
	return true;
}

bool Effect::RemoveTechnique(const char* name)
{
	return true;
}

std::shared_ptr<Technique> Effect::GetTechnique(int index) 
{
	if(index >= m_Techniques.size()) 
	{
		return NULL;
	}
	return std::shared_ptr<Technique>(m_Techniques[index]);
}

const std::shared_ptr<Technique> Effect::GetTechnique(int index) const
{
	if(index >= m_Techniques.size()) 
	{
		return NULL;
	}
	return std::shared_ptr<Technique>(m_Techniques[index]);
}

std::shared_ptr<Technique> Effect::GetTechnique(const char* name) 
{
	for(auto iter = m_Techniques.begin(); iter != m_Techniques.end(); iter++) 
	{
		if(strcmp((*iter)->GetName(),name) == 0) 
		{
			return (*iter);
		}
	}
	return NULL;
}

const std::shared_ptr<Technique> Effect::GetTechnique(const char* name) const
{
	for(auto iter = m_Techniques.begin(); iter != m_Techniques.end(); iter++) 
	{
		if(strcmp((*iter)->GetName(),name) == 0) 
		{
			return (*iter);
		}
	}
	return NULL;
}