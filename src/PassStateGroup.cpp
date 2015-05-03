#include "PassStateGroup.h"

bool StateGroup::AddState(std::shared_ptr<BlankState> state) 
{
	for (auto iter = m_States.begin(); iter != m_States.end(); iter++) 
	{
		if ((*iter)->m_State == state->m_State || (*iter) == state) 
		{
			return false;
		}
	}
	m_States.push_back(state);
	return true;
}

bool StateGroup::RemoveState(fxState state) 
{
	for (auto iter = m_States.begin(); iter != m_States.end();) 
	{
		if ((*iter)->m_State == state) 
		{
			m_States.erase(iter);
			return true;
		}
		iter++;
	}
	return false;
}

std::shared_ptr<BlankState> StateGroup::FindState(fxState state) 
{
	for (auto iter = m_States.begin(); iter != m_States.end(); iter++) 
	{
		if ((*iter)->m_State = state) 
		{
			return (*iter);
		}
	}
	return NULL;
}