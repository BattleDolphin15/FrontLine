#pragma once
#include "EffectCore.h"
#include "Pass.h"
#include "PassDesc.h"
#include "Technique.h"

//make this a like the context/container system in nvfx
class Effect
	: public std::enable_shared_from_this<Effect>
{
private:
	typedef std::shared_ptr<PassDesc> PassDescVec;
	PassDescVec m_PassData;
	
	std::vector<std::shared_ptr<Technique>>m_Techniques;
	
	const char* m_Name;
public:
	Effect(const char* name);
	~Effect();
	
	void SetName(const char* name) { m_Name = name; }
	const char* GetName() { return m_Name; }
	
	//PassDesc stuff
	bool Execute(std::shared_ptr<Pass> pass, fxState flag, const char* name = NULL); //new
	bool Execute(std::shared_ptr<Pass> pass, const char* name); //new
	
	//the Effect can save PassDesc, just maybe for later use
	void CreatePassData(std::shared_ptr<PassDesc> data); //new
	std::shared_ptr<PassDesc> CreatePassData(fxState flag, const char* name, bool add); //new
	
	std::shared_ptr<PassDesc> Find(const char* name); //new
	const std::shared_ptr<PassDesc> Find(const char* name) const; //new
	
	std::shared_ptr<PassDesc> Find(fxState flag); //new
	const std::shared_ptr<PassDesc> Find(fxState flag) const; //new
	
	std::shared_ptr<PassDesc> Find(const char* techName, const char* passName, const char* name); //new
	const std::shared_ptr<PassDesc> Find(const char* techName, const char* passName, const char* name) const; //new
	
	std::shared_ptr<PassDesc> Find(int techIndex, int passIndex, const char* name); //new
	const std::shared_ptr<PassDesc> Find(int techIndex, int passIndex, const char* name) const; //new
	
	std::shared_ptr<PassDesc> Find(const char* techName, const char* passName, fxState flag); //new
	const std::shared_ptr<PassDesc> Find(const char* techName, const char* passName, fxState flag) const; //new
	
	std::shared_ptr<PassDesc> Find(int techIndex, int passIndex, fxState flag); //new
	const std::shared_ptr<PassDesc> Find(int techIndex, int passIndex, fxState flag) const; //new
		
	//Pass and Technique stuff
	std::shared_ptr<Pass> CreatePass(const char* name); //new
	
	std::shared_ptr<Pass> GetPass(const char* techName, const char* passName); //new
	const std::shared_ptr<Pass> GetPass(const char* techName, const char* passName) const; //new
	
	std::shared_ptr<Pass> GetPass(int techIndex, int passIndex); //new
	const std::shared_ptr<Pass> GetPass(int techIndex, int passIndex) const; //new
	
	bool AddTechnique(std::shared_ptr<Technique> technique);
	std::shared_ptr<Technique> CreateTechnique(const char* name); //new
	
	bool RemoveTechnique(std::shared_ptr<Technique> technique);
	bool RemoveTechnique(int index); //new
	bool RemoveTechnique(const char* name); //new
	
	std::shared_ptr<Technique> GetTechnique(int index);
	const std::shared_ptr<Technique> GetTechnique(int index) const; //new
	
	std::shared_ptr<Technique> GetTechnique(const char* name);
	const std::shared_ptr<Technique> GetTechnique(const char* name) const; //new
	
	int GetNumTechniques() const { return (int)m_Techniques.size(); } 
};

//this goes in Effect class
	//Effect setting methods here
	/*void SetAmbient(float r, float g, float b);
	void setAmbient(const Color& ambient);
	
	void SetDiffuse(float r, float g, float b, float a = 1.0f);
	void SetDiffuse(const Color& diffuse);
	
	void SetSpecular(float r, float g, float b, float a = 1.0f);
	void SetSpecular(const Color& diffuse);
	
	void SetSpecularPower(float power);
	
	void SetEmissive(float r, float g, float b, float a = 1.0f);
	void SetEmissive(const Color& emissive);
	
	const Color& GetAmbient() const;
	
	const Color& GetDiffuse() const;
	
	const Color& GetSpecular() const;
	
	float GetSpecularPower() const;
	
	const Color& GetEmissive() const;*/