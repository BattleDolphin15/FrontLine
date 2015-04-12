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
		Detach(iter->flag, iter->name);
	}
	
	//detach from parent
	for (auto iter = m_Owners.begin(); iter != m_Owners.end(); iter++)
	{
		//clear this data from owners
		std::shared_ptr<PassDesc> data = GetFromData(*iter);
		if(data)
			data->Detach(shared_from_this());
	}
}

bool PassDesc::Attach(std::shared_ptr<PassDesc> dep)
{
	//if (m_Parent.lock() && dep->m_Parent.lock())
	//{
		Dependency data;
		data.name = dep->GetName();
		data.flag = dep->GetFlag();
		m_Data.push_back(data);

		Dependency owner;
		owner.name = m_Name;
		owner.flag = m_Flag;
		dep->m_Owners.push_back(owner);

		return true;
	//}
	//return false;
}

bool PassDesc::Attach(fxState flag, const char* name)
{
	//this one is the only if parents
	if (m_Parent.lock())
	{
		std::shared_ptr<PassDesc> attached = NULL;
		if (name)
			attached = m_Parent.lock()->Find(name);
		else
			attached = m_Parent.lock()->Find(flag);
		if (!attached)
			return false;

		Dependency data;
		data.name = name;
		data.flag = flag;
		m_Data.push_back(data);

		Dependency owner;
		owner.name = m_Name;
		owner.flag = m_Flag;
		attached->m_Owners.push_back(owner);

		return true;
	}
	return false;
}

bool PassDesc::Detach(std::shared_ptr<PassDesc> dep)
{
	if (m_Parent.lock() && dep->m_Parent.lock())
	{
		for (auto iter = m_Data.begin(); iter != m_Data.end();)
		{
			if (iter->name && dep->GetName())
			{
				if (strcmp(iter->name, dep->GetName()) == 0)
				{
					//remove
					m_Data.erase(iter);
					return true;
				}
			}
			//if deleting by flag, the data cannot have a name
			else if (iter->flag == dep->GetFlag())
			{
				//basically make sure theres only one flag of the type existing in here
				//for example, PipelineGL and FrameBufferObjectGL
				int count = 0;
				for (auto flagIter = m_Data.begin(); flagIter != m_Data.end(); flagIter++)
				{
					if (flagIter->flag == dep->GetFlag())
						count++;
					if (count > 1)
						return false;
				}
				//now that we know theres only one of this flag, now remove
				m_Data.erase(iter);
				return true;
			}
			iter++;
		}

		//now do the owners
		for (auto iter = dep->m_Owners.begin(); iter != dep->m_Owners.end();)
		{
			if (iter->name && GetName())
			{
				if (strcmp(iter->name, GetName()) == 0)
				{
					//remove
					dep->m_Owners.erase(iter);
					return true;
				}
			}
			//if deleting by flag, the data cannot have a name
			else if (iter->flag == GetFlag())
			{
				//basically make sure theres only one flag of the type existing in here
				//for example, PipelineGL and FrameBufferObjectGL
				int count = 0;
				for (auto flagIter = m_Data.begin(); flagIter != m_Data.end(); flagIter++)
				{
					if (flagIter->flag == GetFlag())
						count++;
					if (count > 1)
						return false;
				}
				//now that we know theres only one of this flag, now remove
				dep->m_Owners.erase(iter);
				return true;
			}
			iter++;
		}
	}
	return false;
}

bool PassDesc::Detach(fxState flag, const char* name)
{
	bool usedName = false;
	bool erased = false;
	if (m_Parent.lock())
	{
		for (auto iter = m_Data.begin(); iter != m_Data.end();)
		{
			if (iter->name && name)
			{
				if (strcmp(iter->name, name) == 0)
				{
					//remove
					m_Data.erase(iter);
					usedName = true;
					erased = true;
					break;
				}
			}
			//if deleting by flag, the data cannot have a name
			else if (iter->flag == flag)
			{
				//basically make sure theres only one flag of the type existing in here
				//for example, PipelineGL and FrameBufferObjectGL
				int count = 0;
				for (auto flagIter = m_Data.begin(); flagIter != m_Data.end(); flagIter++)
				{
					if (flagIter->flag == flag)
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
		
		std::shared_ptr<PassDesc> data = NULL;
		if (usedName)
			data = m_Parent.lock()->Find(name);
		else
			data = m_Parent.lock()->Find(flag);
		if (!data)
			return false;
		//now do the owners
		for (auto iter = data->m_Owners.begin(); iter != data->m_Owners.end();)
		{
			if (iter->name && GetName())
			{
				if (strcmp(iter->name, GetName()) == 0)
				{
					//remove
					data->m_Owners.erase(iter);
					return true;
				}
			}
			//if deleting by flag, the data cannot have a name
			else if (iter->flag == GetFlag())
			{
				//basically make sure theres only one flag of the type existing in here
				//for example, PipelineGL and FrameBufferObjectGL
				int count = 0;
				for (auto flagIter = m_Data.begin(); flagIter != m_Data.end(); flagIter++)
				{
					if (flagIter->flag == GetFlag())
						count++;
					if (count > 1)
						return false;
				}
				//now that we know theres only one of this flag, now remove
				data->m_Owners.erase(iter);
				return true;
			}
			iter++;
		}
	}
	return false;
}

std::shared_ptr<PassDesc> PassDesc::GetFromData(Dependency dep)
{
	if (!m_Parent.lock())
		return NULL;
	std::shared_ptr<Pass> parent = m_Parent.lock();
	std::shared_ptr<PassDesc> data = parent->Find(dep.name);
	if (data)
	{
		return data;
	}
	else
	{
		data = parent->Find(dep.flag);
		if (data)
		{
			return data;
		}
	}
	return NULL;
}

const std::shared_ptr<PassDesc> PassDesc::GetFromData(Dependency dep) const
{
	if (!m_Parent.lock())
		return NULL;
	std::shared_ptr<Pass> parent = m_Parent.lock();
	std::shared_ptr<PassDesc> data = parent->Find(dep.name);
	if (data)
	{
		return data;
	}
	else
	{
		data = parent->Find(dep.flag);
		if (data)
		{
			return data;
		}
	}
	return NULL;
}

//only accept flags here because names are specific while flags are generic
void PassDesc::GetFromData(fxState flag, std::vector<std::shared_ptr<PassDesc>>* data)
{
	if (m_Parent.lock())
	{
		m_Parent.lock()->Find(flag, data);
	}
}

std::vector<std::shared_ptr<PassDesc>>& PassDesc::GetVecFromData()
{
	std::vector<std::shared_ptr<PassDesc>> dataVec;
	for (auto iter = m_Data.begin(); iter != m_Data.end(); iter++)
	{
		std::shared_ptr<PassDesc> data = GetFromData(*iter);
		if (data)
			dataVec.push_back(data);
	}
	return dataVec;
}

std::vector<std::shared_ptr<PassDesc>>& PassDesc::GetVecFrormOwners()
{
	std::vector<std::shared_ptr<PassDesc>> dataVec;
	for (auto iter = m_Owners.begin(); iter != m_Owners.end(); iter++)
	{
		std::shared_ptr<PassDesc> data = GetFromData(*iter);
		if (data)
			dataVec.push_back(data);
	}
	return dataVec;
}

void PassDesc::InvalidateAttachments()
{
	//detach the children
	for (auto iter = m_Data.begin(); iter != m_Data.end(); iter++)
	{
		//clear this data from owners
		Detach(iter->flag, iter->name);
	}
	
	//detach from parent
	for (auto iter = m_Owners.begin(); iter != m_Owners.end(); iter++)
	{
		//clear this data from owners
		std::shared_ptr<PassDesc> data = GetFromData(*iter);
		if(data)
			data->Detach(shared_from_this());
	}
}