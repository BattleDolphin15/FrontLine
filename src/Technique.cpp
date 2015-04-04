#include "Technique.h"
#include "Pass.h"

Technique::~Technique() 
{
}

bool Technique::Validate() 
{
	for(auto iter = m_Passes.begin(); iter != m_Passes.end(); iter++) 
	{
		if(!iter->pass->Validate()) 
		{
			return false;
		}
	}
	return true;
}

bool Technique::Invalidate() 
{
	for(auto iter = m_Passes.begin(); iter != m_Passes.end(); iter++) 
	{
		if(!iter->pass->Invalidate()) 
		{
			return false;
		}
	}
	return true;
}

bool Technique::AddPass(std::shared_ptr<Pass> pass) 
{
	for(auto iter = m_Passes.begin(); iter != m_Passes.end(); iter++) 
	{
		if(iter->pass == pass) 
		{
			return false;
		}
	}
	
	PassInfo passInfo;
	passInfo.isActive = true;
	pass->SetParent(shared_from_this());
	passInfo.pass = pass;
	m_Passes.push_back(passInfo);
	return true;
}

std::shared_ptr<Pass> Technique::CreatePass(const char* name)
{
}

bool Technique::AddSubTechnique(std::shared_ptr<Technique> tech)
{
}

void Technique::SetSubTechniqueActive(std::shared_ptr<Technique> tech, bool active)
{
}

bool Technique::ContainsSubTechnique(std::shared_ptr<Technique> tech)
{
}

bool Technique::GetSubTechniqueActive(std::shared_ptr<Technique> tech) const
{
}

void Technique::InsertPass(int index, std::shared_ptr<Pass> pass)
{
}

void Technique::ReplacePass(std::shared_ptr<Pass> pass)
{
}

void Technique::ReplacePass(std::shared_ptr<Pass> prevPass, std::shared_ptr<Pass> newPass)
{
}

void Technique::ReplacePass(const char* name, std::shared_ptr<Pass> pass)
{
}

bool Technique::RemovePass(std::shared_ptr<Pass> pass) 
{
	for(auto iter = m_Passes.begin(); iter != m_Passes.end();) 
	{
		if(iter->pass == pass) 
		{
			m_Passes.erase(iter);
			return true;
		}
		iter++;
	}
	return false;
}

bool Technique::RemovePass(const char* name)
{
}

bool Technique::RemovePass(int index)
{
}

bool Technique::RemovePasses(int srcIndex, int dstIndex)
{
}

void Technique::MovePass(int srcIndex, int dstIndex)
{
}

bool Technique::ContainsPass(std::shared_ptr<Pass> pass) const
{
}

void Technique::SetPassActive(int index, bool active) 
{
	if(index >= m_Passes.size()) 
	{
		return;
	}
	m_Passes[index].isActive = active;
}

bool Technique::SetPassActive(std::shared_ptr<Pass> pass, bool active)
{
}

void Technique::SetPassActive(const char* name, bool active) 
{
	for(auto iter = m_Passes.begin(); iter != m_Passes.end(); iter++) 
	{
		if(strcmp(iter->pass->GetName(),name) == 0) 
		{
			iter->isActive = active;
			break;
		}
	}
}

bool Technique::GetPassActive(int index) const
{
	if(index >= m_Passes.size())
	{
		return false;
	}
	return m_Passes[index].isActive;
}

bool Technique::GetPassActive(std::shared_ptr<Pass> pass) const
{
}

bool Technique::GetPassActive(const char* name) const
{
	for(auto iter = m_Passes.begin(); iter != m_Passes.end(); iter++) 
	{
		if(strcmp(iter->pass->GetName(),name) == 0) 
		{
			return iter->isActive;
		}
	}
	return false;
}

std::shared_ptr<Pass> Technique::GetPass(int index) 
{
	if(index >= m_Passes.size()) 
	{
		return NULL;
	}
	return std::shared_ptr<Pass>(m_Passes[index].pass);
}

const std::shared_ptr<Pass> Technique::GetPass(int index) const
{
	if(index >= m_Passes.size()) 
	{
		return NULL;
	}
	return std::shared_ptr<Pass>(m_Passes[index].pass);
}

std::shared_ptr<Pass> Technique::GetPass(const char* name) 
{
	for(auto iter = m_Passes.begin(); iter != m_Passes.end(); iter++)
	{
		if(strcmp(iter->pass->GetName(),name) == 0) 
		{
			return iter->pass;
		}
	}
	return NULL;
}

const std::shared_ptr<Pass> Technique::GetPass(const char* name) const
{
	for(auto iter = m_Passes.begin(); iter != m_Passes.end(); iter++)
	{
		if(strcmp(iter->pass->GetName(),name) == 0) 
		{
			return iter->pass;
		}
	}
	return NULL;
}