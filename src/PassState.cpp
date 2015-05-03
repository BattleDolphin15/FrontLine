#include "PassState.h"

static std::shared_ptr<StateInterpreter> stateInterpreter(new StateInterpreter());

std::shared_ptr<StateInterpreter> StateInterpreter::Get() 
{
	return stateInterpreter;
}