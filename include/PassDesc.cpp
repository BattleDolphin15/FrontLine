#include "PassDesc.h"
#include "Pass.h"

PassDesc::PassDesc(fxState flag,const char* name) 
{
	m_Flag = flag;
	m_Name = name;
	m_Active = true;
	m_Validated = false;
}

PassDesc::~PassDesc() 
{
	//detach the children
	for (auto iter = m_Data.begin(); iter != m_Data.end(); iter++)
	{
		//clear this data from owners
		if (iter->expired())
		{
			continue;
		}
		else
		{
			//make data remove this as owner
			for (auto dataIter = iter->lock()->m_Owners.begin(); dataIter != iter->lock()->m_Owners.end();)
			{
				//this case if in the destructor -  u cannot lock an expired weak_ptr
				if (dataIter->expired())
				{
					dataIter = iter->lock()->m_Owners.erase(dataIter);
				}
				//this is for all other cases of removal
				else if (dataIter->lock() == shared_from_this())
				{
					//remove
					iter->lock()->m_Owners.erase(dataIter);
					break;
				}
				else
				{
					dataIter++;
				}
			}
		}
	}
	m_Data.clear();
	
	//detach from parent
	for (auto iter = m_Owners.begin(); iter != m_Owners.end(); iter++)
	{
		//clear this data from owners
		if (iter->expired())
		{
			continue;
		}
		else
		{
			//have the parent detach this from its data
			for (auto ownerIter = iter->lock()->m_Data.begin(); ownerIter != iter->lock()->m_Data.end();)
			{
				if (ownerIter->expired())
				{
					ownerIter = iter->lock()->m_Data.erase(ownerIter);
				}
				else if (ownerIter->lock() == shared_from_this())
				{
					//remove
					ownerIter->lock()->m_Data.erase(ownerIter);
					break;
				}
				else
				{
					ownerIter++;
				}
			}
		}
	}
	m_Owners.clear();
}

bool PassDesc::Attach(std::shared_ptr<PassDesc> data)
{
	for (auto iter = m_Data.begin(); iter != m_Data.end(); iter++)
	{
		if (iter->lock() == data)
			return false;
	}

	m_Data.push_back(data);
	data->m_Owners.push_back(shared_from_this());
	return true;
}

bool PassDesc::Attach(fxState flag, const char* name)
{
	//this one is the only if parents
	if (m_Parent.lock())
	{
		std::shared_ptr<PassDesc> data = NULL;
		if (name)
			data = m_Parent.lock()->Find(name);
		else
			data = m_Parent.lock()->Find(flag);
		if (!data)
			return false;
		return Attach(data);
	}
	return false;
}

bool PassDesc::Detach(std::shared_ptr<PassDesc> data)
{
	bool erased = false;
	for (auto iter = m_Data.begin(); iter != m_Data.end();)
	{
		if (iter->expired())
		{
			iter = m_Data.erase(iter);
		}
		else if (iter->lock() == data)
		{
			//remove
			erased = true;
			m_Data.erase(iter);
			break;
		}
		else
		{
			iter++;
		}
	}

	//now do the owners
	for (auto iter = data->m_Owners.begin(); iter != data->m_Owners.end();)
	{
		//this case if in the destructor -  u cannot lock an expired weak_ptr
		if (iter->expired())
		{
			iter = data->m_Owners.erase(iter);
		}
		//this is for all other cases of removal
		else if (iter->lock() == shared_from_this())
		{
			//remove
			data->m_Owners.erase(iter);
			break;
		}
		else
		{
			iter++;
		}
	}
	return erased;
}

bool PassDesc::Detach(fxState flag, const char* name)
{
	bool usedName = false;
	bool erased = false;
	std::shared_ptr<PassDesc> data = NULL;

	//remove owners first here
	if (name)
		data = shared_from_this()->FindData(name);
	else
		data = shared_from_this()->FindData(flag);
	if (!data)
		return false;

	for (auto iter = data->m_Owners.begin(); iter != data->m_Owners.end();)
	{
		if (iter->expired())
		{
			data->m_Owners.erase(iter);
		}
		else if (iter->lock() == shared_from_this())
		{
			//remove
			data->m_Owners.erase(iter);
			break;
		}
		iter++;
	}

	for (auto iter = m_Data.begin(); iter != m_Data.end();)
	{
		if (iter->expired())
		{
			m_Data.erase(iter);
		}
		else if (iter->lock()->GetName() && name)
		{
			if (strcmp(iter->lock()->GetName(), name) == 0)
			{
				//remove
				m_Data.erase(iter);
				usedName = true;
				erased = true;
				break;
			}
		}
		//if deleting by flag, the data cannot have a name
		else if (iter->lock()->GetFlag() == flag)
		{
			//basically make sure theres only one flag of the type existing in here
			//for example, PipelineGL and FrameBufferObjectGL
			int count = 0;
			for (auto flagIter = m_Data.begin(); flagIter != m_Data.end(); flagIter++)
			{
				if (flagIter->lock()->GetFlag() == flag)
					count++;
				if (count > 1)
					return false;
			}
			//now that we know theres only one of this flag, now remove
			m_Data.erase(iter);
			erased = true;
			break;
		}
		iter++;
	}
	if (!erased)
		return false;
	return true;
}

std::shared_ptr<PassDesc> PassDesc::FindData(const char* name)
{
	for (auto iter = m_Data.begin(); iter != m_Data.end(); iter++)
	{
		if (iter->expired())
			continue;
		if (iter->lock()->GetName()) 
		{
			if (strcmp(iter->lock()->GetName(), name) == 0)
			{
				return iter->lock();
			}
		}
	}
	return NULL;
}

const std::shared_ptr<PassDesc> PassDesc::FindData(const char* name) const
{
	for (auto iter = m_Data.begin(); iter != m_Data.end(); iter++)
	{
		if (iter->expired())
			continue;
		if (iter->lock()->GetName())
		{
			if (strcmp(iter->lock()->GetName(), name) == 0)
			{
				return iter->lock();
			}
		}
	}
	return NULL;
}

std::shared_ptr<PassDesc> PassDesc::FindData(fxState flag)
{
	for (auto iter = m_Data.begin(); iter != m_Data.end(); iter++)
	{
		if (iter->expired())
			continue;
		if (iter->lock()->GetFlag() == flag)
		{
			return iter->lock();
		}
	}
	return NULL;
}

const std::shared_ptr<PassDesc> PassDesc::FindData(fxState flag) const
{
	for (auto iter = m_Data.begin(); iter != m_Data.end(); iter++)
	{
		if (iter->expired())
			continue;
		if (iter->lock()->GetFlag() == flag)
		{
			return iter->lock();
		}
	}
	return NULL;
}

void PassDesc::FindData(fxState flag, std::vector<std::shared_ptr<PassDesc>>& data)
{
	for (auto iter = m_Data.begin(); iter != m_Data.end(); iter++)
	{
		if (iter->expired())
			continue;
		if (iter->lock()->GetFlag() == flag)
		{
			data.push_back(iter->lock());
		}
	}
}

void PassDesc::FindData(fxState flag, std::vector<const std::shared_ptr<PassDesc>>& data) const
{
	for (auto iter = m_Data.begin(); iter != m_Data.end(); iter++)
	{
		if (iter->expired())
			continue;
		if (iter->lock()->GetFlag() == flag)
		{
			data.push_back(iter->lock());
		}
	}
}

std::shared_ptr<PassDesc> PassDesc::FindData(int index)
{
	if (index < m_Data.size())
	{
		if (m_Data.at(index).expired())
			return NULL;
		return m_Data.at(index).lock();
	}
	return NULL;
}

const std::shared_ptr<PassDesc> PassDesc::FindData(int index) const
{
	if (index < m_Data.size())
	{
		if (m_Data.at(index).expired())
			return NULL;
		return m_Data.at(index).lock();
	}
	return NULL;
}

/**********************************************************************/

std::shared_ptr<PassDesc> PassDesc::FindOwner(const char* name)
{
	for (auto iter = m_Owners.begin(); iter != m_Owners.end(); iter++)
	{
		if (iter->expired())
			continue;
		if (iter->lock()->GetName())
		{
			if (strcmp(iter->lock()->GetName(), name) == 0)
			{
				return iter->lock();
			}
		}
	}
	return NULL;
}

const std::shared_ptr<PassDesc> PassDesc::FindOwner(const char* name) const
{
	for (auto iter = m_Owners.begin(); iter != m_Owners.end(); iter++)
	{
		if (iter->expired())
			continue;
		if (iter->lock()->GetName())
		{
			if (strcmp(iter->lock()->GetName(), name) == 0)
			{
				return iter->lock();
			}
		}
	}
	return NULL;
}

std::shared_ptr<PassDesc> PassDesc::FindOwner(fxState flag)
{
	for (auto iter = m_Owners.begin(); iter != m_Owners.end(); iter++)
	{
		if (iter->expired())
			continue;
		if (iter->lock()->GetFlag() == flag)
		{
			return iter->lock();
		}
	}
	return NULL;
}

const std::shared_ptr<PassDesc> PassDesc::FindOwner(fxState flag) const
{
	for (auto iter = m_Owners.begin(); iter != m_Owners.end(); iter++)
	{
		if (iter->expired())
			continue;
		if (iter->lock()->GetFlag() == flag)
		{
			return iter->lock();
		}
	}
	return NULL;
}

void PassDesc::FindOwner(fxState flag, std::vector<std::shared_ptr<PassDesc>>& data)
{
	for (auto iter = m_Owners.begin(); iter != m_Owners.end(); iter++)
	{
		if (iter->expired())
			continue;
		if (iter->lock()->GetFlag() == flag)
		{
			data.push_back(iter->lock());
		}
	}
}

void PassDesc::FindOwner(fxState flag, std::vector<const std::shared_ptr<PassDesc>>& data) const
{
	for (auto iter = m_Owners.begin(); iter != m_Owners.end(); iter++)
	{
		if (iter->expired())
			continue;
		if (iter->lock()->GetFlag() == flag)
		{
			data.push_back(iter->lock());
		}
	}
}

std::shared_ptr<PassDesc> PassDesc::FindOwner(int index)
{
	if (index < m_Owners.size())
	{
		if (m_Owners.at(index).expired())
			return NULL;
		return m_Owners.at(index).lock();
	}
	return NULL;
}

const std::shared_ptr<PassDesc> PassDesc::FindOwner(int index) const
{
	if (index < m_Owners.size())
	{
		if (m_Owners.at(index).expired())
			return NULL;
		return m_Owners.at(index).lock();
	}
	return NULL;
}

/*********************************************************************************/

std::vector<std::shared_ptr<PassDesc>> PassDesc::GetVecFromData()
{
	std::vector<std::shared_ptr<PassDesc>> dataVec;
	for (auto iter = m_Data.begin(); iter != m_Data.end(); iter++)
	{
		std::shared_ptr<PassDesc> data = iter->lock();
		if (data)
			dataVec.push_back(data);
	}
	return dataVec;
}

std::vector<const std::shared_ptr<PassDesc>> PassDesc::GetVecFromData() const
{
	std::vector<const std::shared_ptr<PassDesc>> dataVec;
	for (auto iter = m_Data.begin(); iter != m_Data.end(); iter++)
	{
		std::shared_ptr<PassDesc> data = iter->lock();
		if (data)
			dataVec.push_back(data);
	}
	return dataVec;
}

std::vector<std::shared_ptr<PassDesc>> PassDesc::GetVecFromOwners()
{
	std::vector<std::shared_ptr<PassDesc>> dataVec;
	for (auto iter = m_Owners.begin(); iter != m_Owners.end(); iter++)
	{
		std::shared_ptr<PassDesc> data = iter->lock();
		if (data)
			dataVec.push_back(data);
	}
	return dataVec;
}

std::vector<const std::shared_ptr<PassDesc>> PassDesc::GetVecFromOwners() const
{
	std::vector<const std::shared_ptr<PassDesc>> dataVec;
	for (auto iter = m_Owners.begin(); iter != m_Owners.end(); iter++)
	{
		std::shared_ptr<PassDesc> data = iter->lock();
		if (data)
			dataVec.push_back(data);
	}
	return dataVec;
}

void PassDesc::InvalidateAttachments()
{
	for (auto iter = m_Data.begin(); iter != m_Data.end(); iter++)
	{
		//clear this data from owners
		if (iter->expired())
		{
			continue;
		}
		else
		{
			//make data remove this as owner
			for (auto dataIter = iter->lock()->m_Owners.begin(); dataIter != iter->lock()->m_Owners.end();)
			{
				//this case if in the destructor -  u cannot lock an expired weak_ptr
				if (dataIter->expired())
				{
					dataIter = iter->lock()->m_Owners.erase(dataIter);
				}
				//this is for all other cases of removal
				else if (dataIter->lock() == shared_from_this())
				{
					//remove
					iter->lock()->m_Owners.erase(dataIter);
					break;
				}
				else
				{
					dataIter++;
				}
			}
		}
	}
	m_Data.clear();

	//detach from parent
	for (auto iter = m_Owners.begin(); iter != m_Owners.end(); iter++)
	{
		//clear this data from owners
		if (iter->expired())
		{
			continue;
		}
		else
		{
			//have the parent detach this from its data
			for (auto ownerIter = iter->lock()->m_Data.begin(); ownerIter != iter->lock()->m_Data.end();)
			{
				if (ownerIter->expired())
				{
					ownerIter = iter->lock()->m_Data.erase(ownerIter);
				}
				else if (ownerIter->lock() == shared_from_this())
				{
					//remove
					ownerIter->lock()->m_Data.erase(ownerIter);
					break;
				}
				else
				{
					ownerIter++;
				}
			}
		}
	}
	m_Owners.clear();
}