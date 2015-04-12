#pragma once

class Pass;
class PassDesc;
class Technique;
class Material;

class MaterialVisitor
{
public:
	FxVisitor() {}
	~FxVisitor {}
	
	//can provide additional functionality from the pass. For example,
	//if you wanna use part of the pass execution functionality
	//or glean information from pass
	virtual bool Visit(std::shared_ptr<Pass> pass) { return true; }
	
	virtual bool Visit(std::shared_ptr<PassDesc> data) { return true; }
	
	virtual bool Visit(std::shared_ptr<Technique> tech) { return true; }
	
	virtual bool Visit(std::shared_ptr<Material> mat) { return true; }
};
	