#pragma once
#include "PassDesc.h"

class Technique;
class EffectVisitor;

class Pass
	: public std::enable_shared_from_this<Pass>
{
protected:
	typedef std::vector<std::shared_ptr<PassDesc>> PassDataVec; 
	
	struct Layer 
	{
		Layer() {}
		~Layer() {} 
		PassDataVec dataForValidation;
		PassDataVec dataForExecution;
	};
	
	std::map<int,Layer> m_Layers;
	
	PassDataVec m_Overrides;
	//map pass number to data, pass number can only be pass that is + or - 1 of this pass
	std::map<int,PassDataVec> m_SharedData; 
	//basically, in order for shared data to be valid, the other pass that
	//the data is shared to has to confirm the action
	std::map<int, bool> m_SharedDataValidity; 
	
	int m_BaseLayer;
	int m_ActiveLayer;
	
	int m_LoopCount;
	
	std::weak_ptr<Technique> m_Parent;
	
	std::map<fxState,std::vector<std::shared_ptr<PassDesc>>> m_PassInfo;
	
	static std::vector<fxState> m_ExecutionConfig;
	
	std::map<std::shared_ptr<Pass>,int> m_OverrideIds;
	
	int m_PassNumber;
	
	bool m_Validated;
	
	uint32 m_Mask;
	
	const char* m_Name;
public:
	Pass(const char* name);
	~Pass();
	
	//std::shared_ptr<Pass> Copy();
	
	void SetParent(std::shared_ptr<Technique> parent) {m_Parent = parent;}
	
	void SetName(const char* name) {m_Name = name;}
	const char* GetName() { return m_Name; }
	
	bool IsValid() { return m_Validated; }
	
	void SetFlagActive(fxState flag, bool active);
	bool GetFlagActive(fxState flag);
	
	void SetDataActive(const char* name, bool active);
	bool GetDataActive(const char* name);
	
	void SetPassDataMask(uint32 mask);
	uint32 GetPassDataMask() const;
	
	bool Accept(std::shared_ptr<EffectVisitor> visitor) { return true; } //new, not implemented yet
	
	static void ConfigureExecution(std::vector<fxState> flags) { m_ExecutionConfig = flags; }
	
	void ConfigureExecutionOverride(std::vector<fxState> flags); //overrides the static configure execution
	void ConfigureExecuutionOverride(std::vector<const char*> names);

	bool Validate(); 
	bool Execute(); 
	bool Cleanup();
	bool Invalidate();

	void SetActiveLayer(int layer, bool copyFromPrev); 

	//forces validation upon this passdesc and marks it as validated
	bool ForceValidate(std::shared_ptr<PassDesc> data);
	bool ForceValidate(std::vector<std::shared_ptr<PassDesc>>& data) { return true; }

	bool ForceInvalidate(std::shared_ptr<PassDesc> data) { return true; }
	bool ForceInvalidate(std::vector<std::shared_ptr<PassDesc>>& data) { return true; }

	void CreateData(std::shared_ptr<PassDesc> data); 
	void CreateDataOverride(std::shared_ptr<PassDesc> data); 
	
	//data that is shared over passes to minimize openGL calls
	//for example, FBOs, UniformBuffers, RenderStates, textures
	//the number of the pass has to be consecutive with this pass
	//the pass has to confirm this action from its own side in order for the data to be valid for sharing
	void CreateDataShared(int passNumber, std::shared_ptr<PassDesc> data); 
	void CreateDataShared(const char* passName, std::shared_ptr<PassDesc> data); 
	void CreateDataShared(std::shared_ptr<Pass> pass, std::shared_ptr<PassDesc> data); 
	//when setting up overrides, all the passes containing this shared data has to be modified
	//sharing data with multiple passes, the passes also have to be consecutive
	void CreateDataShared(int* passNumbers, int count, std::shared_ptr<PassDesc> data); 
	void CreateDataShared(const char** passNames, int count, std::shared_ptr<PassDesc> data); 
	void CreateDataShared(std::shared_ptr<Pass>* passes, int count, std::shared_ptr<PassDesc> data); 
	
	//not quite sure yet how overrides will handle this...
	//both shared data and non shared data can override
	//if a non-shared data overrides a piece of shared data, it will override
	//the shared data in all of the passes, not just the pass it overrides
	//basically, the non-shared data will turn into shared data in the pass it overrides
	//if a shared data overrides a non-shared data piece, the shared data will be turned
	//in to a plain non-shared data
	//if a shared data overrides another shared data, the shared data from all of the
	//overriders passes will replace all the shared data of the pass that is being overrided
	void CreateDataSharedOverride(int passNumber, std::shared_ptr<PassDesc> data); 
	void CreateDataSharedOverride(const char* passName, std::shared_ptr<PassDesc> data); 
	void CreateDataSharedOverride(std::shared_ptr<Pass> pass, std::shared_ptr<PassDesc> data); 
	//when setting up overrides, all the passes containing this shared data has to be modified
	//sharing data with multiple passes, the passes also have to be consecutive
	void CreateDataSharedOverride(int* passNumbers, int count, std::shared_ptr<PassDesc> data); 
	void CreateDataSharedOverride(const char** passNames, int count, std::shared_ptr<PassDesc> data); 
	void CreateDataSharedOverride(std::shared_ptr<Pass>* passes, int count, std::shared_ptr<PassDesc> data); 
	
	//deletes shared data that has been added, but not confirmed
	void DeleteUnconfirmedData();
	
	//gets status of shared data, whether it has been confirmed or not
	bool IsConfirmed(std::shared_ptr<PassDesc> data) const;
	bool IsConfirmed(const char* name) const;
	bool IsConfirmed(fxState flag) const;
	
	//std::shared_ptr<PassDesc> CreateData(fxState flag, const char* name = NULL); //new
	//std::shared_ptr<PassDesc> CreateDataOverride(fxState flag, const char* name = NULL); //new
	
	//now for the CreateDatas for validation, the finds, the fuckin replaces
	//void CreateDataForValidation(std::shared_ptr<PassDesc> data);
	
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
	
	//do the find shared data
	
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
	
	void SetLoopCount(int loopCount);
	int GetLoopCount();
	
	void SetPassNumber(int pNum);
	int GetPassNumber();
	
friend class PassDesc;
};