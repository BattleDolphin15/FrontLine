#pragma once

class PassDesc 
	: public std::enable_shared_from_this<PassDesc>
{
protected:
	struct Dependency {
		Dependency()
		: flag(NULL), name(NULL) {}
		const char* name;
		fxState flag;
	};

	bool m_Active;
	bool m_Validated;
	bool m_Modified; //if the PassDesc has been modified since validation

	const char* m_Name;
	fxState m_Flag;

	std::weak_ptr<Pass> m_Parent;

	std::vector<Dependency> m_Owners; //shud owners just be one dep instead of a list
	std::vector<Dependency> m_Data;
public:
	PassDesc(fxState flag,const char* name = NULL);
	virtual ~PassDesc();

	virtual void SetName(const char* name) {m_Name = name;}
	virtual const char* GetName() {return m_Name;}

	virtual void SetFlag(fxState flag) {m_Flag = flag;}
	virtual fxState GetFlag() {return m_Flag;}

	virtual void SetActive(bool active) { m_Active = active; }
	virtual bool IsActive() const { return m_Active; }

	virtual bool IsValid() const {return m_Validated;} //<-- put these as const funcs so const refs can access them

	virtual bool HasChanged() { return m_Modified; }

	virtual void SetParent(std::shared_ptr<Pass> parent) {m_Parent = parent;}
protected:
	virtual void SetValidated(bool validated) { m_Validated = validated; }
public:
	virtual bool Attach(std::shared_ptr<PassDesc> dep);
	virtual bool Attach(fxState flag, const char* name = NULL);

	virtual bool Detach(std::shared_ptr<PassDesc> dep);
	virtual bool Detach(fxState flag, const char* name = NULL);

	std::shared_ptr<PassDesc> GetFromData(Dependency dep);
	void GetFromData(fxState flag, std::vector<std::shared_ptr<PassDesc>>* data);

	std::vector<std::shared_ptr<PassDesc>>* GetVecFromData();
	//make const versions
	std::vector<std::shared_ptr<PassDesc>>* GetVecFrormOwners();

	template<typename T>
	std::shared_ptr<T> GetFromData(Dependency dep)
	{
		if (m_Parent.empty())
			return NULL;
		std::shared_ptr<Pass> parent = m_Parent.lock();
		std::shared_ptr<PassDesc> data = parent->Find(dep.name);
		if (data)
		{
			return std::static_pointer_cast<T>(data);
		}
		else
		{
			data = parent->Find(dep.flag);
			if (data)
			{
				return std::static_pointer_cast<T>(data);
			}
		}
		return NULL;
	}
protected:
	virtual bool Validate() { SetValidated(true); return true; }
	//virtual bool ValidateImpl() { return true; }
	virtual bool Execute() { return true; } 
	virtual bool Cleanup() { return true; } 
	virtual bool Invalidate() { SetValidated(false); return true; }
	//virtual bool InvalidateImpl() { return true; }
	
friend class Pass;
};