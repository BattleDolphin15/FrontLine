#pragma once
#include "flFxConfig.h"
#include "GL.h"

class Pass;

class PassDesc 
	: public std::enable_shared_from_this<PassDesc>
{
protected:
	bool m_Active;
	bool m_Validated;
	bool m_Modified; //if the PassDesc has been modified since validation

	const char* m_Name;
	fxState m_Flag;
	//use multiple parents
	std::weak_ptr<Pass> m_Parent;
	//std::list<std::weak_ptr<Pass>> m_Parents; //have multiple parents
	std::vector<std::weak_ptr<PassDesc>> m_Owners; //use weak_ptrs instead of dependency
	//std::vector<Dependency> m_Data;
	std::vector<std::weak_ptr<PassDesc>> m_Data;
	
	uint32 m_Mask;
public:
	PassDesc(fxState flag,const char* name = NULL);
	virtual ~PassDesc();
	
	//PassDesc& operator=(PassDesc& other);

	virtual void SetName(const char* name) {m_Name = name;}
	virtual const char* GetName() {return m_Name;}

	virtual void SetFlag(fxState flag) {m_Flag = flag;}
	virtual fxState GetFlag() {return m_Flag;}

	virtual void SetActive(bool active) { m_Active = active; }
	virtual bool IsActive() const { return m_Active; }

	virtual bool IsValid() const { return m_Validated; } //<-- put these as const funcs so const refs can access them

	virtual bool HasChanged() const { return m_Modified; }

	virtual void SetParent(std::shared_ptr<Pass> parent) {m_Parent = parent;}
	
	void SetDataMask(uint32 mask);
	uint32 GetDataMask() const;
	
	std::shared_ptr<PassDesc> Copy();
protected:
	virtual void SetValidated(bool validated) { m_Validated = validated; }
	
	virtual void NotifyChanged() { m_Modified = true; }
public:
	virtual bool Attach(std::shared_ptr<PassDesc> data);
	virtual bool Attach(fxState flag, const char* name = NULL);

	virtual bool Detach(std::shared_ptr<PassDesc> data);
	virtual bool Detach(fxState flag, const char* name = NULL);

	//data
	virtual std::shared_ptr<PassDesc> FindData(const char* name);
	virtual const std::shared_ptr<PassDesc> FindData(const char* name) const;

	virtual std::shared_ptr<PassDesc> FindData(fxState flag);
	virtual const std::shared_ptr<PassDesc> FindData(fxState flag) const;

	virtual void FindData(fxState flag, std::vector<std::shared_ptr<PassDesc>>& data);
	virtual void FindData(fxState flag, std::vector<const std::shared_ptr<PassDesc>>& data) const;

	virtual std::shared_ptr<PassDesc> FindData(int index);
	virtual const std::shared_ptr<PassDesc> FindData(int index) const;

	//now owners
	virtual std::shared_ptr<PassDesc> FindOwner(const char* name);
	virtual const std::shared_ptr<PassDesc> FindOwner(const char* name) const;

	virtual std::shared_ptr<PassDesc> FindOwner(fxState flag);
	virtual const std::shared_ptr<PassDesc> FindOwner(fxState flag) const;

	virtual void FindOwner(fxState flag, std::vector<std::shared_ptr<PassDesc>>& data);
	virtual void FindOwner(fxState flag, std::vector<const std::shared_ptr<PassDesc>>& data) const;

	virtual std::shared_ptr<PassDesc> FindOwner(int index);
	virtual const std::shared_ptr<PassDesc> FindOwner(int index) const;
	
	//....//
	//std::shared_ptr<PassDesc> Safe_Get(std::weak_ptr<PassDesc> iter); //checks for expiration

	//TODO: needs to be fixed
	virtual void ClearAttachments() { m_Data.clear(); }
	
	virtual void ClearOwners() { m_Owners.clear(); }
	
	void SaveAttachmentData();
	
	void ClearAttachmentData();
	
	bool RecalculateAttachments();

	std::vector<std::shared_ptr<PassDesc>> GetVecFromData();
	std::vector<const std::shared_ptr<PassDesc>> GetVecFromData() const;
	//make const versions
	std::vector<std::shared_ptr<PassDesc>> GetVecFromOwners();
	std::vector<const std::shared_ptr<PassDesc>> GetVecFromOwners() const;

	typedef std::vector<std::weak_ptr<PassDesc>>::iterator PassDescIterator;
	typedef std::pair<PassDescIterator, PassDescIterator> PassDescIteratorPair;

	typedef std::vector<std::weak_ptr<PassDesc>>::const_iterator ConstPassDescIterator;
	typedef std::pair<ConstPassDescIterator, ConstPassDescIterator> ConstPassDescIteratorPair;

	PassDescIteratorPair GetDataIterator() { return std::make_pair(m_Data.begin(), m_Data.end()); }
	ConstPassDescIteratorPair GetConstDataIterator() { return std::make_pair(m_Data.cbegin(), m_Data.cend()); }

	PassDescIteratorPair GetOwnerIterator() { return std::make_pair(m_Owners.begin(), m_Owners.end()); }
	ConstPassDescIteratorPair GetConstOwnerIterator() { return std::make_pair(m_Owners.cbegin(), m_Owners.cend()); }
	
	int GetDataSize() { return (int)m_Data.size(); }
	int GetOwnerSize() { return (int)m_Owners.size(); }
	
protected:
	virtual bool Validate() { SetValidated(true); return true; }

	virtual bool Execute() { return true; } 

	virtual bool Cleanup() { return true; } 

	virtual bool Invalidate() { SetValidated(false); return true; }

	virtual void ValidateAttachments() {} //called in Pass::Validate before the actual validation

	virtual void InvalidateAttachments(); //implemented here
	
friend class Pass;
};