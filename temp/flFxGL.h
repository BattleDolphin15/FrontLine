#pragma once
#include "GL.h"
#include "flFxExt.h"
#include "StatesGL.h"
#include "GLenum.h"
#include <fstream>

/*class PassGL : public Pass
{
public:
	PassGL(const char* name) 
		: Pass(name) {}
	~PassGL() {}
	virtual bool Execute();
};*/
class flFxCoreGL : public flFxCore
{
private:
	GLuint m_FullscreenQuadId;
public:
	flFxCoreGL() {}
	~flFxCoreGL() {}
	bool Init();
	bool Shutdown();
	void DrawFullscreenQuad();
	static std::shared_ptr<flFxCoreGL> Get();
};
class StateGroupGL : public StateGroup
{
private:
public:
	StateGroupGL();
	virtual ~StateGroupGL();
	bool Apply();
	bool Execute() { return Apply(); }
	bool Cleanup();
};
class GLSLShader : public Shader
{
private:
	GLuint m_Id;
	GLenum m_Type;
public:
	GLSLShader(const char* name,GLenum type, const char* string = NULL);
	virtual ~GLSLShader();
	bool LoadShader(const char* string);
	bool LoadShaderFromFile(const char* filePath);
	bool Validate(); //create shaderprogram
	bool Invalidate(); //destroy shaderprogram
	void Bind();
	void Unbind();
	bool IsValid() {return (m_Validated && m_Id) ? true : false;}
	GLenum GetType() {return m_Type;}
	GLuint GetProgramId() {return m_Id;}
friend class flFxParser; //temp
};
class PipelineGL : public GPUPipeline
{
private:
	GLuint m_Id;
public:
	PipelineGL(){}
	virtual ~PipelineGL();
	bool Validate();
	bool Execute() { Bind(); return true; }
	bool Cleanup() { Unbind(); return true; }
	bool Invalidate();
	bool SetShader(std::shared_ptr<Shader> shader);
	void SetShaders(std::shared_ptr<Shader>* shaders,int count) {}
	bool RemoveShader(const char* name);
	//GetShader doesnt need to be overrided, handled by GPUPipeline already
	void ClearAll() {}
	bool IsValid() {return m_Id ? true : false;}
	void Bind();
	void Unbind();
};
class ShaderParameterGL : public ShaderParameter 
{
public:
	enum Type {
		T1F,
		T1I,
		T1FV,
		T2F,
		T2I,
		T2FV,
		T3F,
		T3I,
		T3FV,
		TMATRIX4FV,
		TSUBROUTINE
	};
	struct Target {
		GLenum shaderType; //for subroutines
		int shaderNumber;
		int uniformLocation;
	};
private:
	Type m_Type;
	std::vector<Target> m_Targets;
	GLsizei m_Size;
	GLboolean m_Transpose; 
public:
	ShaderParameterGL(const char* name,Type type,float* value = NULL); //single uniforms
	ShaderParameterGL(const char* name,Type type,GLsizei count, float* value = NULL); //arrays of uniforms
	ShaderParameterGL(const char* name,Type type,GLsizei count, GLboolean transpose ,float* value = NULL); //matrices
	virtual ~ShaderParameterGL();
	bool Validate();
	bool Invalidate();
	bool Update();
	bool Execute() { return Update(); }
	void SetValue(GLsizei count, float* value) {}
	void SetValue(GLsizei count, GLboolean transpose, float* value) {}
};
class SamplerStateGL : public SamplerState
{
private:
	bool m_HasChanged;
	GLuint m_Id;
public:
	SamplerStateGL(const char* name);
	virtual ~SamplerStateGL();
	bool Validate();
	bool Invalidate();
	bool AddState(std::shared_ptr<BlankState> state);
	bool RemoveState(fxState state);
	bool UpdateTexture(int texUnit);
};
class ResourceGL : public Resource
{
private:
	GLuint m_Id;
	int m_TexUnit;
	int m_FBOAttachment;
	bool CreateRenderTexture();
	bool CreateDepthTexture();
public:
	ResourceGL(const char* name, fxState resType);
	virtual ~ResourceGL();
	bool Validate();
	bool Execute() { Bind(); return true; }
	bool Cleanup() { Unbind(); return true; }
	bool Invalidate();
	void SetTexture(GLuint id) { m_Id = id; }
	void SetTexture(GLuint id, int unit) { m_Id = id; m_TexUnit = unit; }
	void SetTexUnit(int unit) { m_TexUnit = unit; }
	GLuint GetTextureId() { return m_Id; }
	int GetTexUnit() { return m_TexUnit; }
	void SetFBOAttachment(int attachment) { m_FBOAttachment = attachment; }
	int GetFBOAttachment() { return m_FBOAttachment; }
	void Bind();
	void Unbind();
	bool IsValid();
	// bool Update(); //well all this can be handled in ResourceGL::Bind() including updating samplers
};
class FrameBufferObjectGL : public FrameBufferObject
{
private:
	GLuint m_Id;
	fxState m_ClearMode[3]; //make independent?
public:
	FrameBufferObjectGL(const char* name) :
		FrameBufferObject(name) { m_Id = NULL; }
	~FrameBufferObjectGL();
	bool Validate();
	bool Execute();
	bool Cleanup() { ReleaseCurrent(); return true; }
	bool Invalidate();
	void SetDSTTexture(std::shared_ptr<Resource> res);
	bool AddTextureResource(std::shared_ptr<Resource> res);
	GLuint GetFBOId() { return m_Id; }
	void SetCurrent();
	void ReleaseCurrent();
	void SetClearMode(fxState clear1, fxState clear2 = NULL, fxState clear3 = NULL);
};
class RenderingModeGL : public PassDesc
{
private:
	fxState m_RenderingMode;
public:
	RenderingModeGL(fxState renderMode);
	~RenderingModeGL() {}
	fxState GetRenderingMode() { return m_RenderingMode; }
	bool Execute(); //draw fullscreen quad or do nothing
};
class ClearModeGL : public PassDesc
{
private:
	fxState m_ClearMode[3];
public:
	ClearModeGL(fxState clear1, fxState clear2 = FX_DO_NOTHING, fxState clear3 = FX_DO_NOTHING);
	~ClearModeGL() {}
	void SetClearMode(fxState clear1, fxState clear2 = FX_DO_NOTHING, fxState clear3 = FX_DO_NOTHING);
	bool Execute();
};