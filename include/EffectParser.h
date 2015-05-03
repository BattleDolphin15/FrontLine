#pragma once
#include "Effect.h"
#include "pugixml/pugiconfig.hpp"
#include "pugixml/pugixml.hpp"
#include "fastdelegate/FastDelegate.h"
#include "fastdelegate/FastDelegateBind.h"

typedef fastdelegate::FastDelegate1<pugi::xml_node,bool> NodeHandle;
class flFxParser : public pugi::xml_tree_walker
{
protected:
	std::shared_ptr<Effect> m_TmpEffect;
	std::shared_ptr<Technique> m_CurrTechnique;
	std::shared_ptr<Pass> m_CurrPass;
private:
	std::vector<std::shared_ptr<PassDesc>> m_CurrObjects; //make this a vector
	std::vector<std::shared_ptr<PassDesc>> m_QueuedObjects; //make this a vector
	std::vector<std::shared_ptr<PassDesc>> m_SavedObjects;
	pugi::xml_node m_CurrXmlScope; //curent node
	std::map<const char*,NodeHandle> m_NodeHandlers;
protected:
	void RegisterXmlNodeHandle(const char* name, NodeHandle node) { m_NodeHandlers[name] = node; }
	///queued = an object that has been declared but not set
	///current = the object the current scope iterator is in
	void SetCurrentObject(std::shared_ptr<PassDesc> obj);
	std::shared_ptr<PassDesc> GetCurrentObject(fxState flag);
	void SetQueuedObject(std::shared_ptr<PassDesc> obj);
	std::shared_ptr<PassDesc> GetQueuedObject(const char* name);
	//std::shared_ptr<PassDesc> GetQueuedObjectCopy(const char* name) { return nullptr; }
	void SaveObject(std::shared_ptr<PassDesc> obj);
	//std::shared_ptr<PassDesc> GetSavedObject(fxState flag);
	std::shared_ptr<PassDesc> GetSavedObject(const char* name);

	virtual bool for_each(pugi::xml_node& node);
public:
	flFxParser(void);
	~flFxParser(void) {}
	std::shared_ptr<Effect> LoadEffect(pugi::xml_document& doc);
	static flFxParser* Get();
};