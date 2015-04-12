#pragma once
#include "PassDesc.h"

class Repository
{
protected:
	std::vector<std::shared_ptr<PassDesc>> m_Items;
public:
	Repository() {}
	virtual ~Repository();
	
	virtual bool AddItem(std::shared_ptr<PassDesc> item);
	
	virtual bool RemoveItem(const char* name);
	virtual bool RemoveItem(std::shared_ptr<PassDesc> item);
	
	virtual std::shared_ptr<PassDesc> Find(const char* name);
	virtual const std::shared_ptr<PassDesc> Find(const char* name) const;
	
	virtual std::shared_ptr<PassDesc> Find(int index);
	virtual const std::shared_ptr<PassDesc> Find(int index) const;
	
	virtual   GetSize() {return (int)m_Items.size();}
};