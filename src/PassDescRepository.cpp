#include "PassDescRepository.h"

Repository::~Repository() 
{
}
bool Repository::AddItem(std::shared_ptr<PassDesc> item) 
{
	for(auto iter = m_Items.begin(); iter != m_Items.end(); iter++) 
	{
		if((*iter) == item) 
		{
			return false;
		}
	}
	m_Items.push_back(item);
	return true;
}

bool Repository::RemoveItem(const char* name) 
{
	for(auto iter = m_Items.begin(); iter != m_Items.end();) 
	{
		if(strcmp((*iter)->GetName(),name) == 0) 
		{
			m_Items.erase(iter);
			return true;
		}
		iter++;
	}
	return false;
}

bool Repository::RemoveItem(std::shared_ptr<PassDesc> item) 
{
	for(auto iter = m_Items.begin(); iter != m_Items.end();) 
	{
		if((*iter) == item) 
		{
			m_Items.erase(iter);
			return true;
		}
		iter++;
	}
	return false;
}

std::shared_ptr<PassDesc> Repository::Find(const char* name) 
{
	for(auto iter = m_Items.begin(); iter != m_Items.end();) 
	{
		if(strcmp((*iter)->GetName(),name) == 0) 
		{
			return (*iter);
		}
		iter++;
	}
	return NULL;
}

std::shared_ptr<PassDesc> Repository::Find(unsigned int index) 
{
	if(index >= m_Items.size()) 
	{
		return NULL;
	}
	return m_Items[index];
}