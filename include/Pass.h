#pragma once
#include "PassDesc.h"

class Technique;
class EffectVisitor;

class Pass
	: public std::enable_shared_from_this<Pass>
{
protected:
	typedef std::vector<std::shared_ptr<PassDesc>> PassDataVec; 
	
	struct Layer {
		Layer() {}
		~Layer() {} 
		PassDataVec dataForValidation;
		PassDataVec dataForExecution;
	};
	
	std::map<int,Layer> m_Layers;
	
	PassDataVec m_Overrides;
	
	int m_BaseLayer;
	int m_ActiveLayer;
	
	std::weak_ptr<Technique> m_Parent;
	
	std::map<fxState,std::vector<std::shared_ptr<PassDesc>>> m_PassInfo;
	
	static std::vector<fxState> m_ExecutionConfig;
	
	std::map<std::shared_ptr<Pass>,int> m_OverrideIds;
	
	bool m_Validated;
	
	const char* m_Name;
public:
	Pass(const char* name);
	~Pass();
	
	void SetParent(std::shared_ptr<Technique> parent) {m_Parent = parent;}
	
	void SetName(const char* name) {m_Name = name;}
	const char* GetName() { return m_Name; }
	
	bool IsValid() { return m_Validated; }
	
	bool Accept(std::shared_ptr<EffectVisitor> visitor) { return true; } //new, not implemented yet
	
	static void ConfigureExecution(std::vector<fxState> flags) { m_ExecutionConfig = flags; }

	bool Validate(); 
	bool Execute(); 
	bool Cleanup();
	bool Invalidate();

	void SetActiveLayer(int layer, bool copyFromPrev); 

	//forces validation upon this passdesc and marks it as validated
	bool ForceValidate(std::shared_ptr<PassDesc> data);
	bool ForceValidate(std::vector<std::shared_ptr<PassDesc>>& data) { return true; }

	void CreateData(std::shared_ptr<PassDesc> data); 
	void CreateDataOverride(std::shared_ptr<PassDesc> data); 
	
	//std::shared_ptr<PassDesc> CreateData(fxState flag, const char* name = NULL); //new
	//std::shared_ptr<PassDesc> CreateDataOverride(fxState flag, const char* name = NULL); //new
	
	void Replace(std::shared_ptr<PassDesc> data);
	void Replace(std::shared_ptr<PassDesc> prevData, std::shared_ptr<PassDesc> newData); //new mothafuka
	void Replace(const char* name, std::shared_ptr<PassDesc> data); 
	
	std::shared_ptr<PassDesc> Find(const char* name); //matches up same name
	const std::shared_ptr<PassDesc> Find(const char* name) const; //put const defs for everything, new
	
	std::shared_ptr<PassDesc> Find(fxState flag);
	const std::shared_ptr<PassDesc> Find(fxState flag) const; //new
	
	void Find(fxState flag, std::vector<std::shared_ptr<PassDesc>>* data); //too lazy to const overload the vector

	std::shared_ptr<PassDesc> FindOverride(const char* name);
	const std::shared_ptr<PassDesc> FindOverride(const char* name) const; //new
	
	std::shared_ptr<PassDesc> FindOverride(fxState flag);
	const std::shared_ptr<PassDesc> FindOverride(fxState flag) const; //new
	
	void FindOverride(fxState flag, std::vector<std::shared_ptr<PassDesc>>* data);
	
	bool ContainsData(std::shared_ptr<PassDesc> data) const; //new, make parameter const?

	//detach the data here
	bool RemoveData(std::shared_ptr<PassDesc> data);
	bool RemoveData(const char* name);
	bool RemoveData(fxState flag);
	
	void ClearData() { m_Layers[m_ActiveLayer].dataForExecution.clear(); }

	void SetupOverrides(std::shared_ptr<Technique>* dest,int numTechs);
	void SetupOverrides(std::shared_ptr<Pass>* dest,int numPasses);
	
	void ReleaseOverrides(std::shared_ptr<Technique>* dest,int numTechs);
	void ReleaseOverrides(std::shared_ptr<Pass>* dest,int numPasses);
	
	bool RemoveLayer(int layer);
	bool RemoveActiveLayer();

	const Layer& GetLayer() const { return m_Layers.find(m_ActiveLayer)->second; }
	const Layer& GetBaseLayer() const { return m_Layers.find(0)->second; }
	
	int GetActiveLayerId() const { return m_ActiveLayer; }
	
	int GetNumPassDesc() const { return (int)m_Layers.find(m_ActiveLayer)->second.dataForExecution.size(); }
	int GetNumPassDescInAllLayers() const; //sums up all the layers' passdesc count
	
	int GetNumLayers() const { return (int)m_Layers.size(); }
	
friend class PassDesc;
};