#include "flFxGL.h"

//cud be handled internally
/*bool PassGL::Execute() {
	Pass::Execute();
	/*std::shared_ptr<PipelineGL> glslPipeline = std::static_pointer_cast<PipelineGL>(m_PassInfo[FX_PIPELINE_DESC_FLAG][0]);
	//GetPassInfo(FX_PIPELINE_DESC_FLAG,glslPipeline);
	std::vector<std::shared_ptr<ShaderParameterGL>> shaderParameters;
	//GetPassInfo(FX_SHADER_PARAMETER_DESC_FLAG,shaderParameters); //put the vector has to have PassDesc
	for(auto iter = m_PassInfo[FX_SHADER_PARAMETER_DESC_FLAG].begin(); iter != m_PassInfo[FX_SHADER_PARAMETER_DESC_FLAG].end(); iter++) {
		shaderParameters.push_back(std::static_pointer_cast<ShaderParameterGL>(*iter));
	}
	std::shared_ptr<StateGroupGL> stateGroup;
	if(m_PassInfo[FX_STATE_GROUP_DESC_FLAG].size() > 0) { //safety
		stateGroup = std::static_pointer_cast<StateGroupGL>(m_PassInfo[FX_STATE_GROUP_DESC_FLAG][0]);
	}
	if(stateGroup) {
		stateGroup->Apply();
	}
	glslPipeline->Bind();
	for(auto iter = shaderParameters.begin(); iter != shaderParameters.end(); iter++) {
		(*iter)->Update();
	}
	return true;
}*/
static std::shared_ptr<flFxCoreGL> coreGL(new flFxCoreGL());
bool flFxCoreGL::Init() {
	std::vector<fxState> execution = {
		FX_FBO_TARGET_DESC_FLAG,
		FX_CLEARMODE_DESC_FLAG,
		FX_STATE_GROUP_DESC_FLAG,
		FX_PIPELINE_DESC_FLAG,
		FX_RESOURCE_DESC_FLAG,
		FX_SHADER_PARAMETER_DESC_FLAG,
		FX_RENDERMODE_DESC_FLAG
	};
	Pass::ConfigureExecution(execution);

	StateInterpreter::Get()->RegisterState(FX_DRAW_FULLSCREEN_QUAD, FX_DRAW_FULLSCREEN_QUAD, "FX_DRAW_FULLSCREEN_QUAD");
	StateInterpreter::Get()->RegisterState(FX_DO_NOTHING, FX_DO_NOTHING, "FX_DO_NOTHING");

	StateInterpreter::Get()->RegisterState(FX_COLOR_BUFFER_BIT, GL_COLOR_BUFFER_BIT, "FX_COLOR_BUFFER_BIT");
	StateInterpreter::Get()->RegisterState(FX_DEPTH_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, "FX_DEPTH_BUFFER_BIT");
	StateInterpreter::Get()->RegisterState(FX_STENCIL_BUFFER_BIT, GL_STENCIL_BUFFER_BIT, "FX_STENCIL_BUFFER_BIT");

	StateInterpreter::Get()->RegisterState(FX_RESOURCE_1D, GL_TEXTURE_1D, "FX_RESOURCE_1D");
	StateInterpreter::Get()->RegisterState(FX_RESOURCE_2D, GL_TEXTURE_2D, "FX_RESOURCE_2D");
	StateInterpreter::Get()->RegisterState(FX_RESOURCE_3D, GL_TEXTURE_3D, "FX_RESOURCE_3D");

	StateInterpreter::Get()->RegisterState(FX_LINEAR, GL_LINEAR, "FX_LINEAR");
	StateInterpreter::Get()->RegisterState(FX_REPEAT, GL_REPEAT, "FX_REPEAT");
	
	StateInterpreter::Get()->RegisterState(FX_BLEND, GL_BLEND, "FX_BLEND");
	StateInterpreter::Get()->RegisterState(FX_ZERO, GL_ZERO, "FX_ZERO");
	StateInterpreter::Get()->RegisterState(FX_ONE, GL_ONE, "FX_ONE");
	StateInterpreter::Get()->RegisterState(FX_SRC_COLOR, GL_SRC_COLOR, "FX_SRC_COLOR");
	StateInterpreter::Get()->RegisterState(FX_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, "FX_ONE_MINUS_SRC_COLOR");
	StateInterpreter::Get()->RegisterState(FX_DST_COLOR, GL_DST_COLOR, "FX_DST_COLOR");
	StateInterpreter::Get()->RegisterState(FX_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_DST_COLOR, "FX_ONE_MINUS_DST_COLOR");
	StateInterpreter::Get()->RegisterState(FX_SRC_ALPHA, GL_SRC_ALPHA, "FX_SRC_ALPHA");
	StateInterpreter::Get()->RegisterState(FX_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, "FX_ONE_MINUS_SRC_ALPHA");
	StateInterpreter::Get()->RegisterState(FX_DST_ALPHA, GL_DST_ALPHA, "FX_DST_ALPHA");
	StateInterpreter::Get()->RegisterState(FX_ONE_MINUS_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, "FX_ONE_MINUS_DST_ALPHA");
	StateInterpreter::Get()->RegisterState(FX_CONSTANT_COLOR, GL_CONSTANT_COLOR, "FX_CONSTANT_COLOR");
	StateInterpreter::Get()->RegisterState(FX_ONE_MINUS_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, "FX_ONE_MINUS_CONSTANT_COLOR");
	StateInterpreter::Get()->RegisterState(FX_CONSTANT_ALPHA, GL_CONSTANT_ALPHA, "FX_CONSTANT_ALPHA");
	StateInterpreter::Get()->RegisterState(FX_ONE_MINUS_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA, "FX_ONE_MINUS_CONSTANT_ALPHA");
	StateInterpreter::Get()->RegisterState(FX_SRC_ALPHA_SATURATE, GL_SRC_ALPHA_SATURATE, "FX_SRC_ALPHA_SATURATE");
	StateInterpreter::Get()->RegisterState(FX_SRC1_COLOR, GL_SRC1_COLOR, "FX_SRC1_COLOR");
	StateInterpreter::Get()->RegisterState(FX_ONE_MINUS_SRC1_COLOR, GL_ONE_MINUS_SRC1_COLOR, "FX_ONE_MINUS_SRC1_COLOR");
	StateInterpreter::Get()->RegisterState(FX_SRC1_ALPHA, GL_SRC1_ALPHA, "FX_SRC1_ALPHA");
	StateInterpreter::Get()->RegisterState(FX_ONE_MINUS_SRC1_ALPHA, GL_ONE_MINUS_SRC1_ALPHA, "FX_ONE_MINUS_SRC1_ALPHA");
	
	StateInterpreter::Get()->RegisterState(FX_DEPTH_TEST, GL_DEPTH_TEST, "FX_DEPTH_TEST");

	StateInterpreter::Get()->RegisterState(FX_RGBA16F, GL_RGBA16F, "FX_RGBA16F");
	StateInterpreter::Get()->RegisterState(FX_RGB32F, GL_RGB32F, "FX_RGB32F");
	StateInterpreter::Get()->RegisterState(FX_RGBA32F, GL_RGBA32F, "FX_RGBA32F");
	StateInterpreter::Get()->RegisterState(FX_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, "FX_DEPTH_COMPONENT");
	StateInterpreter::Get()->RegisterState(FX_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT16, "FX_DEPTH_COMPONENT16");
	StateInterpreter::Get()->RegisterState(FX_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT24, "FX_DEPTH_COMPONENT24");
	StateInterpreter::Get()->RegisterState(FX_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT32, "FX_DEPTH_COMPONENT32");
	StateInterpreter::Get()->RegisterState(FX_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT32F, "FX_DEPTH_COMPONENT32F");
	//resource
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};
	GLfloat uv[] = {
		0.0f,0.0f,
		1.0f,0.0f,
		1.0f,1.0f,
		0.0f,0.0f,
		1.0f,1.0f,
		0.0f,1.0f
	};
	/*const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	const GLfloat g_uv_buffer_data[] = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		0.0f, 1.0f,
	};*/

	glGenVertexArrays(1, &m_FullscreenQuadId);
	glBindVertexArray(m_FullscreenQuadId);

	GLuint vertId;
	glGenBuffers(1, &vertId);
	glBindBuffer(GL_ARRAY_BUFFER, vertId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	GLuint uvId;
	glGenBuffers(1, &uvId);
	glBindBuffer(GL_ARRAY_BUFFER, uvId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	return true;
}
void flFxCoreGL::DrawFullscreenQuad() {
	glBindVertexArray(m_FullscreenQuadId);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
bool flFxCoreGL::Shutdown() {
	glDeleteVertexArrays(1, &m_FullscreenQuadId);
	return true;
}
std::shared_ptr<flFxCoreGL> flFxCoreGL::Get() {
	return coreGL;
}
StateGroupGL::StateGroupGL() 
	: StateGroup() {
}
StateGroupGL::~StateGroupGL() {
}
bool StateGroupGL::Apply() {
	for(auto iter = m_States.begin(); iter != m_States.end(); iter++) {
		(*iter)->Apply();
	}
	return true;
}
bool StateGroupGL::Cleanup() {
	for (auto iter = m_States.begin(); iter != m_States.end(); iter++) {
		(*iter)->Cleanup();
	}
	return true;
}
GLSLShader::GLSLShader(const char* name,GLenum type, const char* string) 
	: Shader(name) {
	m_Type = type;
	if(string) {
		m_Code = string;
	}
}
GLSLShader::~GLSLShader() {
	glDeleteProgram(m_Id);
}
bool GLSLShader::LoadShader(const char* string) {
	m_Code = string;
	return true;
}
bool GLSLShader::LoadShaderFromFile(const char* filePath) {
	std::string shaderCode;
    std::ifstream shaderStream(filePath, std::ios::in);
    if(shaderStream.is_open())
    {
        std::string Line = "";
        while(getline(shaderStream, Line))
            shaderCode += "\n" + Line;
        shaderStream.close();
    }
	m_Code = shaderCode;
	return true;
}
bool GLSLShader::Validate() {
	if(m_Validated) {
		return false; //dont wanna validate twice
	}
	const char* code = m_Code.c_str();
	m_Id = glCreateShaderProgramv(m_Type,1,&code);
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetProgramiv(m_Id, GL_LINK_STATUS, &Result);
	glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, int(1)));

	if (InfoLogLength > 0)
	{
		glGetProgramInfoLog(m_Id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
	}
	SetValidated(true);
	Shader::Validate(); //AttachTo(pipeline);
	std::cout<<"Shader: Validated"<<std::endl;
	return true;
}
bool GLSLShader::Invalidate() {
	if(!m_Validated) {
		return false;
	}

	glDeleteProgram(m_Id);
	m_Id = NULL;
	Shader::Invalidate();
	SetValidated(false);
	return true;
}
void GLSLShader::Bind() {
	glUseProgram(m_Id);
}
void GLSLShader::Unbind() {
	glUseProgram(0);
}
PipelineGL::~PipelineGL() {
	glDeleteProgramPipelines(1,&m_Id);
}
bool PipelineGL::Validate() {
	glGenProgramPipelines(1,&m_Id);
	for(auto iter = m_Data.begin(); iter != m_Data.end(); iter++) {
		std::shared_ptr<GLSLShader> glslShader = std::static_pointer_cast<GLSLShader>(GetFromData(*iter));
		GLenum bit;
		switch(glslShader->GetType()) {
		case GL_VERTEX_SHADER:
			bit = GL_VERTEX_SHADER_BIT;
			break;
		case GL_FRAGMENT_SHADER:
			bit = GL_FRAGMENT_SHADER_BIT;
			break;
		}
		glUseProgramStages(m_Id,bit,glslShader->GetProgramId());
	}
	std::cout<<"PipelineGL: Validated"<<std::endl;
	SetValidated(true);
	return true;
}
bool PipelineGL::Invalidate() {
	glDeleteProgramPipelines(1,&m_Id);
	SetValidated(false);
	return true;
}
bool PipelineGL::SetShader(std::shared_ptr<Shader> shader) {
	if(!GPUPipeline::SetShader(shader)) {
		return false;
	}
	std::shared_ptr<GLSLShader> glslShader = std::static_pointer_cast<GLSLShader>(shader);
	glProgramParameteri(glslShader->GetProgramId(),GL_PROGRAM_SEPARABLE,GL_TRUE); //just as a precaution
	GLenum bit;
	switch(glslShader->GetType()) {
	case GL_VERTEX_SHADER:
		bit = GL_VERTEX_SHADER_BIT;
		break;
	case GL_FRAGMENT_SHADER:
		bit = GL_FRAGMENT_SHADER_BIT;
		break;
	}
	glUseProgramStages(m_Id,bit,glslShader->GetProgramId());
	return true;
}
bool PipelineGL::RemoveShader(const char* name) {
	if(!GPUPipeline::RemoveShader(name)) {
		return false;
	}
	std::shared_ptr<GLSLShader> glslShader;
	for(auto iter = m_Shaders.begin(); iter != m_Shaders.end(); iter++) {
		if(strcmp((*iter)->GetName(),name) == 0) {
			glslShader = std::static_pointer_cast<GLSLShader>(*iter);
		}
	}
	glProgramParameteri(glslShader->GetProgramId(),GL_PROGRAM_SEPARABLE,GL_FALSE);
	return true;
}
void PipelineGL::Bind() {
	glBindProgramPipeline(m_Id);
}
void PipelineGL::Unbind() {
	glBindProgramPipeline(0);
}
ShaderParameterGL::ShaderParameterGL(const char* name, Type type, float* value) 
	: ShaderParameter(name,value) {
	m_Type = type;
}
ShaderParameterGL::ShaderParameterGL(const char* name, Type type, GLsizei count, float* value) 
	: ShaderParameter(name,value) {
	m_Type = type;
	m_Size = count;
}
ShaderParameterGL::ShaderParameterGL(const char* name, Type type,GLsizei count,GLboolean transpose, float* value) 
	: ShaderParameter(name,value) {
	m_Type = type;
	m_Size = count;
	m_Transpose = transpose;
}
ShaderParameterGL::~ShaderParameterGL() {
}
bool ShaderParameterGL::Validate() {
	if(IsValid()) {
		return false;
	}
	if(!m_Parent.lock()) {
		return false;
	}
	int p = 0;
	std::shared_ptr<PipelineGL> glslPipeline = std::static_pointer_cast<PipelineGL>(m_Parent.lock()->Find(FX_PIPELINE_DESC_FLAG)); 
	std::shared_ptr<GLSLShader> glslShader = std::static_pointer_cast<GLSLShader>(glslPipeline->GetShader(p));
	while(glslShader) {
		Target t;
		glslShader->Bind();
		if(m_Type == TSUBROUTINE) {
			t.uniformLocation = glGetSubroutineIndex(glslShader->GetProgramId(), glslShader->GetType(), m_Name);
		}
		else {
			t.uniformLocation = glGetUniformLocation(glslShader->GetProgramId(), m_Name);
		}
		if(t.uniformLocation >= 0) {
			std::cout<<"found uniform location: "<<t.uniformLocation<<std::endl;
		}
		t.shaderNumber = p;
		bool emplaced = false;
		for(auto iter = m_Targets.begin(); iter != m_Targets.end(); iter++) {
			if(iter->shaderNumber == t.shaderNumber &&
				t.uniformLocation == iter->uniformLocation) {
				m_Targets.emplace(iter,t);
				emplaced = true;
				break;
			}
		}
		if(!emplaced) {
			m_Targets.push_back(t);
		}
		glslShader->Unbind();
		p++;
		glslShader = std::static_pointer_cast<GLSLShader>(glslPipeline->GetShader(p));
		
	}
	SetValidated(true);
	return true;
}
bool ShaderParameterGL::Invalidate() {
	if(!IsValid()) {
		return false;
	}
	if(!m_Parent.lock()) {
		return false;
	}
	SetValidated(false);
	return true;
}
bool ShaderParameterGL::Update() {
	for(auto iter = m_Targets.begin(); iter != m_Targets.end(); iter++) {
		Target t = (*iter);
		std::shared_ptr<PipelineGL> glslPipeline = std::static_pointer_cast<PipelineGL>(m_Parent.lock()->Find(FX_PIPELINE_DESC_FLAG)); 
		std::shared_ptr<GLSLShader> glslShader = std::static_pointer_cast<GLSLShader>(glslPipeline->GetShader(t.shaderNumber));
		if(glslShader) {///if glslProgram is valid
			switch(m_Type) { //if not resType, the m_Type
			case Type::T1I:
				glProgramUniform1i(glslShader->GetProgramId(),t.uniformLocation,(int)m_Value[0]);
				break;
			case Type::T1F:
				glProgramUniform1f(glslShader->GetProgramId(),t.uniformLocation,m_Value[0]);
				break;
			case Type::T3F:
				glProgramUniform3f(glslShader->GetProgramId(),t.uniformLocation,m_Value[0],m_Value[1],m_Value[2]);
				break;
			case Type::T1FV:
				glProgramUniform1fv(glslShader->GetProgramId(),t.uniformLocation,m_Size,m_Value);
				break;
			case Type::T3FV:
				glProgramUniform3fv(glslShader->GetProgramId(),t.uniformLocation,m_Size,m_Value);
				break;
			case Type::TMATRIX4FV:												//shud be total array size / size of individual matrix
				glProgramUniformMatrix4fv(glslShader->GetProgramId(),t.uniformLocation,m_Size,m_Transpose,m_Value); //oh the count is the number of matrices passed
				break;
			case Type::TSUBROUTINE:
				//TODO
				break;
			}
		}
	}
	return true;
}
SamplerStateGL::SamplerStateGL(const char* name)
	: SamplerState(name) {
	m_HasChanged = false;
}
SamplerStateGL::~SamplerStateGL() {
	glDeleteSamplers(1, &m_Id);
}
bool SamplerStateGL::Validate() {
	glGenSamplers(1, &m_Id);
	return true;
}
bool SamplerStateGL::Invalidate() {
	glDeleteSamplers(1, &m_Id);
	return true;
}
bool SamplerStateGL::AddState(std::shared_ptr<BlankState> state) {
	SamplerState::AddState(state);
	m_HasChanged = true;
	return true;
}
bool SamplerStateGL::RemoveState(fxState state) {
	SamplerState::RemoveState(state);
	m_HasChanged = true;
	return true;
}
bool SamplerStateGL::UpdateTexture(int unit) {
	if (!m_Id) {
		return false;
	}
	if (m_HasChanged) {
		for (auto iter = m_States.begin(); iter != m_States.end(); iter++) {
			switch ((*iter)->m_State) {
			case FX_TEXTURE_WRAP_S:
			case FX_TEXTURE_WRAP_T:
			case FX_TEXTURE_MIN_FILTER:
			case FX_TEXTURE_MAG_FILTER:
			{
				std::shared_ptr<State2<GLenum, GLenum>> state = std::static_pointer_cast<State2<GLenum, GLenum>>(*iter);
				glSamplerParameteri(m_Id, state->m_v1, state->m_v2); //well, m_v1 in this case is the GLenum state, while the m_v2 is the value
				break;
			}
			case FX_TEXTURE_MAX_ANISOTROPY:
			{
				std::shared_ptr<State2<GLenum, GLfloat>> state = std::static_pointer_cast<State2<GLenum, GLfloat>>(*iter);
				glSamplerParameterf(m_Id, state->m_v1, state->m_v2);
				break;
			}
			}
		}
		m_HasChanged = false;
	}
	glBindSampler(unit, m_Id);
	return true;
}
ResourceGL::ResourceGL(const char* name, fxState resType)
	: Resource(name,resType) {
	m_TexUnit = -1;
}
ResourceGL::~ResourceGL() {
	glDeleteTextures(1, &m_Id);
}
bool ResourceGL::CreateRenderTexture() {
	GLenum format = StateInterpreter::Get()->Convert<GLenum>(m_Data.format);
	//glActiveTexture(GL_TEXTURE0 + m_TexUnit);
	glGenTextures(1, &m_Id);
	if (m_Data.msaa) {
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_Id);
		//glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_Data.msaaSamples, m_Data.format, m_Data.dimensions[0], m_Data.dimensions[1], GL_TRUE);
		glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_Data.msaaSamples, format, GetWidth(), GetHeight(), GL_TRUE);
		glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, m_Id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, GetWidth(), GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexImage2D(GL_TEXTURE_2D, 0, m_Data.format, m_Data.dimensions[0], m_Data.dimensions[1], 0, externalFormat, pixelStorageType, NULL);
		//glTexStorage2D(GL_TEXTURE_2D, 1, format, GetWidth(), GetHeight());
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, GetWidth(), GetHeight(), 0, GL_RGB, GL_FLOAT, NULL);
		/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/
	}
	return true;
}
bool ResourceGL::CreateDepthTexture() {
	glGenRenderbuffers(1, &m_Id);
	glBindRenderbuffer(GL_RENDERBUFFER, m_Id);
	GLenum format = StateInterpreter::Get()->Convert<GLenum>(m_Data.format);
	if (m_Data.msaa) {
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_Data.msaaSamples, format, GetWidth() , GetHeight());
	}
	else {
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,800,800);
	}
	return true;
}
bool ResourceGL::Validate() {
	if (IsValid()) {
		return true; //dont validate twice
	}
	switch (m_ResourceType) {
	case FX_RESOURCE_RENDERTEX:
		if (!CreateRenderTexture()) {
			return false;
		}
		break;
	case FX_RESOURCE_DEPTHTEX:
		if (!CreateDepthTexture()) {
			return false;
		}
		break;
	}
	Resource::Validate();
	SetValidated(true);
	return true;
}
bool ResourceGL::Invalidate() {
	if (!IsValid()) {
		return true;
	}
	switch (m_ResourceType) {
	case FX_RESOURCE_RENDERTEX:
		glDeleteTextures(1, &m_Id);
	case FX_RESOURCE_DEPTHTEX:
		glDeleteRenderbuffers(1, &m_Id);
	}
	Resource::Invalidate();
	SetValidated(false);
	return true;
}
void ResourceGL::Bind() {
	switch (m_ResourceType) {
	case FX_RESOURCE_RENDERTEX:
		if (glIsEnabled(GL_TEXTURE_2D) == GL_FALSE) {
			glEnable(GL_TEXTURE_2D); //change it all bak ltr
		}
		glActiveTexture(GL_TEXTURE0 + m_TexUnit);
		glBindTexture(GL_TEXTURE_2D, m_Id);
		break;
	case FX_RESOURCE_DEPTHTEX:
		break;
	default:
		GLenum resTypeGL = StateInterpreter::Get()->Convert<GLenum>(m_ResourceType);
		if (glIsEnabled(resTypeGL) == GL_FALSE) {
			glEnable(resTypeGL); //change it all bak ltr
		}
		glActiveTexture(GL_TEXTURE0 + m_TexUnit);
		glBindTexture(resTypeGL, m_Id);
		std::shared_ptr<SamplerStateGL> samplerState = std::static_pointer_cast<SamplerStateGL>(m_Data.samplerState);
		if (samplerState) {
			samplerState->UpdateTexture(m_TexUnit);
		}
		break;
	}
}
void ResourceGL::Unbind() {
	switch (m_ResourceType) {
	case FX_RESOURCE_RENDERTEX:
		if (glIsEnabled(GL_TEXTURE_2D) == GL_TRUE) {
			glDisable(GL_TEXTURE_2D);
		}
		break;
	case FX_RESOURCE_DEPTHTEX:
		break;
	default:
		GLenum resTypeGL = StateInterpreter::Get()->Convert<GLenum>(m_ResourceType);
		if (glIsEnabled(resTypeGL) == GL_TRUE) {
			glDisable(resTypeGL);
		}
		break;
	}
}
bool ResourceGL::IsValid() {
	if (!PassDesc::IsValid()) {
		return false;
	}
	if (m_TexUnit < 0 || (!m_Id)) {
		return false;
	}
	return true;
}
FrameBufferObjectGL::~FrameBufferObjectGL() {
	glDeleteFramebuffers(1, &m_Id);
}
bool FrameBufferObjectGL::Validate() {
	//dont need this anymore cuz all the resources are added to the pass already
	/*for (auto iter = m_Resources.begin(); iter != m_Resources.end(); iter++) {
		(*iter)->Validate();
	}
	m_DSTResource->Validate();*/
	glGenFramebuffers(1, &m_Id);
	
	int size = GetDataSize() - 1; //minus one cuz of the depth buffer
	if (size > 0) {
		glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
		/*for (int i = 0; i < size; i++) {
			std::shared_ptr<ResourceGL> renderTex = std::static_pointer_cast<ResourceGL>(m_Resources.at(i));
			glBindTexture(GL_TEXTURE_2D, renderTex->GetTextureId());
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + renderTex->GetFBOAttachment(), GL_TEXTURE_2D, renderTex->GetTextureId(), 0);
			//glBindTexture(GL_TEXTURE_2D, 0);
		}*/
		for(auto iter = m_Data.begin(); iter != m_Data.end(); iter++)
		{
			std::shared_ptr<ResourceGL> res = std::static_pointer_cast<ResourceGL>(GetFromData(*iter));
			if(res->GetResourceType() == FX_RESOURCE_RENDERTEX)
			{
				glBindTexture(GL_TEXTURE_2D, res->GetTextureId());
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + res->GetFBOAttachment(), GL_TEXTURE_2D, res->GetTextureId(), 0);
			}
		}
		//glBindTexture(GL_TEXTURE_2D, 0); 
		std::shared_ptr<ResourceGL> depthTex = NULL;
		for(auto iter = m_Data.begin(); iter != m_Data.end(); iter++)
		{
			depthTex = std::static_pointer_cast<ResourceGL>(GetFromData(*iter));
			if(res->GetResourceType() == FX_RESOURCE_DEPTHTEX)
			{
				break;
			}
		}
		/*std::shared_ptr<ResourceGL> depthTex = std::static_pointer_cast<ResourceGL>(m_DSTResource);*/
		glBindRenderbuffer(GL_RENDERBUFFER, depthTex->GetTextureId()); //new
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthTex->GetTextureId());
		GLenum* drawBuffers = new GLenum[size];
		for (int i = 0; i < size; i++) {
			drawBuffers[i] = GL_COLOR_ATTACHMENT0 + (std::static_pointer_cast<ResourceGL>(m_Resources.at(i)))->GetFBOAttachment();
		}
		glDrawBuffers(size, drawBuffers);
		int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "something went wrong in the framebuffer!" << std::endl;
		}
		else {
			std::cout << "FBO SUCCESS!" << std::endl;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	SetValidated(true);
	//add render textures back to pass
	return true;
}
bool FrameBufferObjectGL::Invalidate() {
	/*for (auto iter = m_Resources.begin(); iter != m_Resources.end(); iter++) {
		(*iter)->Invalidate();
	}
	m_DSTResource->Invalidate();*/
	glDeleteFramebuffers(1, &m_Id);
	//remove render textures from pass
	return true;
}
void FrameBufferObjectGL::SetDSTTexture(std::shared_ptr<Resource> res) {
	std::shared_ptr<ResourceGL> resGL = std::static_pointer_cast<ResourceGL>(res);
	FrameBufferObject::SetDSTTexture(res);
	if (!m_Id) {
		return;
	}
	glBindRenderbuffer(GL_RENDERBUFFER, resGL->GetTextureId()); //new
	glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, resGL->GetTextureId());
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	SetValidated(false);
}
bool FrameBufferObjectGL::AddTextureResource(std::shared_ptr<Resource> res) {
	if (!FrameBufferObject::AddTextureResource(res)) {
		return false;
	}
	if (!m_Id) { //if(!IsValid()) {
		return true;
	}
	std::shared_ptr<ResourceGL> resGL = std::static_pointer_cast<ResourceGL>(res);
	glBindTexture(GL_TEXTURE_2D, resGL->GetTextureId());
	glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + resGL->GetFBOAttachment(), GL_TEXTURE_2D, resGL->GetTextureId(), 0);
	int size = GetNumResources();
	if (size > 0) {
		GLenum* drawBuffers = new GLenum[size];
		for (int i = 0; i < size; i++) {
			drawBuffers[i] = GL_COLOR_ATTACHMENT0 + (std::static_pointer_cast<ResourceGL>(m_Resources.at(i)))->GetFBOAttachment();
		}
		glDrawBuffers(size, drawBuffers);
		int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "something went wrong in the framebuffer!" << std::endl;
		}
		else {
			std::cout << "FBO SUCCESS!" << std::endl;
		}
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}
void FrameBufferObjectGL::SetCurrent() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
}
bool FrameBufferObjectGL::Execute() {
	SetCurrent(); 
	GLenum clear1 = StateInterpreter::Get()->Convert<GLenum>(m_ClearMode[0]);
	GLenum clear2 = StateInterpreter::Get()->Convert<GLenum>(m_ClearMode[1]);
	GLenum clear3 = StateInterpreter::Get()->Convert<GLenum>(m_ClearMode[2]);
	if (m_ClearMode[0] != NULL) {
		if (m_ClearMode[1] != NULL) {
			if (m_ClearMode[2] != NULL) {
				glClear(clear1 | clear2 | clear3);
				return true;
			}
			glClear(clear1 | clear2);
			return true;
		}
		glClear(clear1);
		return true;
	}
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return true; 
}
void FrameBufferObjectGL::ReleaseCurrent() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void FrameBufferObjectGL::SetClearMode(fxState clear1, fxState clear2, fxState clear3) {
	m_ClearMode[0] = clear1;
	m_ClearMode[1] = clear2;
	m_ClearMode[2] = clear3;
}
RenderingModeGL::RenderingModeGL(fxState renderMode)
	: PassDesc(FX_RENDERMODE_DESC_FLAG) {
	m_RenderingMode = renderMode;
}
bool RenderingModeGL::Execute() {
	switch (m_RenderingMode) {
	case FX_DRAW_FULLSCREEN_QUAD:
		flFxCoreGL::Get()->DrawFullscreenQuad();
		break;
	case FX_DRAW_TRIANGLE:
		flFxCoreGL::Get()->DrawTriangle(0, 0, 0);
		break;
	case FX_DO_NOTHING:
		break;
	}
	return true;
}