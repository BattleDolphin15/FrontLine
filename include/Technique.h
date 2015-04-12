#pragma once
#include "Pass.h"

class Effect;

class Technique
	: public std::enable_shared_from_this<Technique>
{
private:
	struct PassInfo 
	{
		std::shared_ptr<Pass> pass;
		std::shared_ptr<Technique> tech; //owner
		bool isActive;
	};
	
	std::vector<PassInfo> m_Passes;
	
	std::weak_ptr<Effect> m_Parent;
	
	const char* m_Name;
public:
	Technique(const char* name) {m_Name = name;}
	~Technique();
	
	void SetName(const char* name) {m_Name = name;}
	const char* GetName() { return m_Name; }
	
	void SetParent(std::shared_ptr<Effect> parent) { m_Parent = parent; }
	
	bool Validate();
	bool Invalidate();
	
	bool AddPass(std::shared_ptr<Pass> pass);
	std::shared_ptr<Pass> CreatePass(const char* name); //new
	
	bool AddSubTechnique(std::shared_ptr<Technique> tech); //new
	
	void SetSubTechniqueActive(std::shared_ptr<Technique> tech, bool active); //new
	bool GetSubTechniqueActive(std::shared_ptr<Technique> tech) const; //new
	
	bool ContainsSubTechnique(std::shared_ptr<Technique> tech) const; //new
	
	void InsertPass(int index, std::shared_ptr<Pass> pass); //new
	
	void ReplacePass(std::shared_ptr<Pass> pass); //new
	void ReplacePass(std::shared_ptr<Pass> prevPass, std::shared_ptr<Pass> newPass);  //new
	void ReplacePass(const char* name, std::shared_ptr<Pass> pass); //new
	
	bool RemovePass(std::shared_ptr<Pass> pass);
	bool RemovePass(const char* name); //new
	bool RemovePass(int index); //new
	bool RemovePasses(int srcIndex, int dstIndex); //new
	
	bool ClearPasses() { m_Passes.clear(); } //new
	
	void MovePass(int srcIndex, int dstIndex); //new
	
	bool ContainsPass(std::shared_ptr<Pass> pass) const; //new
	
	int GetNumPasses() const { return (int)m_Passes.size(); }
	
	void SetPassActive(int index,bool active);
	void SetPassActive(std::shared_ptr<Pass> pass, bool active); //new
	void SetPassActive(const char* name, bool active);
	
	bool GetPassActive(int index) const;
	bool GetPassActive(std::shared_ptr<Pass> pass) const; //new
	bool GetPassActive(const char* name) const;

	std::shared_ptr<Pass> GetPass(int index);
	const std::shared_ptr<Pass> GetPass(int index) const; //new
		
	std::shared_ptr<Pass> GetPass(const char* name); //dont return if inactive
	const std::shared_ptr<Pass> GetPass(const char* name) const; //new
};