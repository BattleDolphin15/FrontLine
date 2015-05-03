#pragma once
#include "PassDesc.h"

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
	
	virtual bool Apply() { return true; }
};