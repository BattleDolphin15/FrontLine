#include "Technique.h"
#include "Pass.h"

Technique::~Technique() {
}
bool Technique::Validate() {
	for(auto iter = m_Passes.begin(); iter != m_Passes.end(); iter++) {
		if(!iter->pass->Validate()) {
			return false;
		}
	}
	return true;
}
bool Technique::Invalidate() {
	for(auto iter = m_Passes.begin(); iter != m_Passes.end(); iter++) {
		if(!iter->pass->Invalidate()) {
			return false;
		}
	}
	return true;
}
bool Technique::AddPass(std::shared_ptr<Pass> pass) {
	for(auto iter = m_Passes.begin(); iter != m_Passes.end(); iter++) {
		if(iter->pass == pass) {
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
bool Technique::RemovePass(std::shared_ptr<Pass> pass) {
	for(auto iter = m_Passes.begin(); iter != m_Passes.end(); iter++) {
		if(iter->pass == pass) {
			m_Passes.erase(iter);
			return true;
		}
	}
	return false;
}
void Technique::SetPassActive(int index, bool active) {
	if(index >= m_Passes.size()) {
		return;
	}
	m_Passes[index].isActive = active;
}
void Technique::SetPassActive(const char* name, bool active) {
	for(auto iter = m_Passes.begin(); iter != m_Passes.end(); iter++) {
		if(strcmp(iter->pass->GetName(),name) == 0) {
			iter->isActive = active;
			break;
		}
	}
}
bool Technique::GetPassActive(int index) {
	if(index >= m_Passes.size()) {
		return false;
	}
	return m_Passes[index].isActive;
}
bool Technique::GetPassActive(const char* name) {
	for(auto iter = m_Passes.begin(); iter != m_Passes.end(); iter++) {
		if(strcmp(iter->pass->GetName(),name) == 0) {
			return iter->isActive;
		}
	}
	return false;
}
std::shared_ptr<Pass> Technique::GetPass(int index) {
	if(index >= m_Passes.size()) {
		return NULL;
	}
	return std::shared_ptr<Pass>(m_Passes[index].pass);
}
std::shared_ptr<Pass> Technique::GetPass(const char* name) {
	for(auto iter = m_Passes.begin(); iter != m_Passes.end(); iter++) {
		if(strcmp(iter->pass->GetName(),name) == 0) {
			return iter->pass;
		}
	}
	return NULL;
}