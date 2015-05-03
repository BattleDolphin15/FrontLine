#include "flFxParser.h"

static flFxParser* parser = new flFxParser();
flFxParser::flFxParser() 
{
}

flFxParser* flFxParser::Get() 
{
	return parser;
}
void flFxParser::SetCurrentObject(std::shared_ptr<PassDesc> obj) 
{
	m_CurrObjects.push_back(obj);
}

std::shared_ptr<PassDesc> flFxParser::GetCurrentObject(fxState flag) 
{
	for(auto iter = m_CurrObjects.begin(); iter != m_CurrObjects.end(); iter++) 
	{
		if((*iter)->GetFlag() == flag) 
		{
			return (*iter);
		}
	}
	return NULL;
}

void flFxParser::SetQueuedObject(std::shared_ptr<PassDesc> obj) 
{
	m_QueuedObjects.push_back(obj);
}

std::shared_ptr<PassDesc> flFxParser::GetQueuedObject(const char* name) 
{
	for(auto iter = m_QueuedObjects.begin(); iter != m_QueuedObjects.end(); iter++) 
	{
		if(strcmp((*iter)->GetName(),name) == 0) 
		{
			return (*iter);
		}
	}
	return NULL;
}

void flFxParser::SaveObject(std::shared_ptr<PassDesc> obj) 
{
	m_SavedObjects.push_back(obj);
}

std::shared_ptr<PassDesc> flFxParser::GetSavedObject(const char* name) 
{
	for (auto iter = m_SavedObjects.begin(); iter != m_SavedObjects.end(); iter++) 
	{
		if (strcmp((*iter)->GetName(), name) == 0) 
		{
			return (*iter);
		}
	}
	return NULL;
}

bool flFxParser::for_each(pugi::xml_node& node) 
{
	for(auto iter = m_NodeHandlers.begin(); iter != m_NodeHandlers.end(); iter++) 
	{
		if(strcmp(iter->first,node.name()) == 0) 
		{
			NodeHandle func = iter->second;
			func(node);
			return true;
		}
	}
	return true;
}

std::shared_ptr<Effect> flFxParser::LoadEffect(pugi::xml_document& doc) 
{
	doc.traverse(*this);
	return m_TmpEffect;
}