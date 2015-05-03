#pragma once
#include <fstream>
#include "Pass.h"

class Shader : public PassDesc
{
protected:
	struct CodeInfo
	{
		CodeInfo(int a, int b)
			{ startLineNumber = a; int totalLines = b; }
		int startLineNumber;
		int totalLines;
	}
	std::vector<CodeInfo> m_ModifiedCodeInfo;

	std::string m_Code;
	std::string m_ModifiedCode;
public:
	Shader(const char* name);
	virtual ~Shader();
	
	virtual const char* GetShaderCode() const { return m_Code.c_str(); }
	virtual int GetShaderCodeSize() const { return (int)m_Code.size(); }
	
	virtual const char* GetUnmodifiedShaderCode() const { return NULL; }
	virtual int GetUnmodifiedShaderCodeSize() const { return 0; }
	
	virtual bool LoadShaderFromFile(const char* fileName);
	virtual bool LoadShaderCode(const char* code);
	
	virtual bool AddHeaderCode(const char* code, int startLineNumber = 0) { return true; }
	virtual bool AppendCode(const char* code, int startLineNumber = 0) { return true; }
	
	virtual const char* GetHeaderCode(int startLineNumber = 0) const { return NULL; }
	virtual int GetHeaderCodeSize(int startLineNumber = 0) const { return 0; }
	
	virtual const char* GetAppendedCode(int startLineNumber) const { return NULL; }
	virtual int GetAppendCodeSize(int startLineNumber) const { return 0; }
	
	virtual void ResetCode() {}
	
	virtual void ValidateAttachments();
};