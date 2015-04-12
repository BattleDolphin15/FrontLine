#include "flFxExt.h"

static std::shared_ptr<StateInterpreter> stateInterpreter(new StateInterpreter());
std::shared_ptr<StateInterpreter> StateInterpreter::Get() {
	return stateInterpreter;
}
bool StateGroup::AddState(std::shared_ptr<BlankState> state) {
	for(auto iter = m_States.begin(); iter != m_States.end(); iter++) {
		if((*iter)->m_State == state->m_State || (*iter) == state) {
			return false;
		}
	}
	m_States.push_back(state);
	return true;
}
bool StateGroup::RemoveState(fxState state) {
	for(auto iter = m_States.begin(); iter != m_States.end();) {
		if((*iter)->m_State == state) {
			m_States.erase(iter);
			return true;
		}
		iter++;
	}
	return false;
}
std::shared_ptr<BlankState> StateGroup::FindState(fxState state) {
	for(auto iter = m_States.begin(); iter != m_States.end(); iter++) {
		if((*iter)->m_State = state) {
			return (*iter);
		}
	}
	return NULL;
}
void Shader::ValidateAttachments() {
	if(m_Parent.lock()) {
		std::shared_ptr<GPUPipeline> pipeline = std::static_pointer_cast<GPUPipeline>(m_Parent.lock()->Find(FX_PIPELINE_DESC_FLAG));
		if(pipeline) {
			pipeline->Attach(shared_from_this());
			//pipeline->SetShader(std::static_pointer_cast<Shader>(shared_from_this()));
			return true;
		}
	}
}
bool Shader::Validate() {
	/*if(m_Parent.lock()) {
		std::shared_ptr<GPUPipeline> pipeline = std::static_pointer_cast<GPUPipeline>(m_Parent.lock()->Find(FX_PIPELINE_DESC_FLAG));
		if(pipeline) {
			pipeline->Attach(shared_from_this());
			//pipeline->SetShader(std::static_pointer_cast<Shader>(shared_from_this()));
			return true;
		}
		return false;
	}*/
	return true;
}
bool Shader::Invalidate() {
	//done automatically
	/*if(m_Parent.lock()) {
		std::shared_ptr<GPUPipeline> pipeline = std::static_pointer_cast<GPUPipeline>(m_Parent.lock()->Find(FX_PIPELINE_DESC_FLAG));
		if(pipeline) {
			pipeline->Detach(shared_from_this());
			//pipeline->RemoveShader(m_Name);
			return true;
		}
		return false;
	}*/
	return true;
}
bool GPUPipeline::SetShader(std::shared_ptr<Shader> shader) {
	for(auto iter = m_Shaders.begin(); iter != m_Shaders.end();iter++) {
		if((*iter) == shader) {
			return false;
		}
	}
	m_Shaders.push_back(shader);
	return true;
}
bool GPUPipeline::RemoveShader(const char* name) {
	for(auto iter = m_Shaders.begin(); iter != m_Shaders.end();) {
		if(strcmp((*iter)->GetName(),name) == 0) {
			m_Shaders.erase(iter);
			return true;
		}
		iter++;
	}
	return false;
}
std::shared_ptr<Shader> GPUPipeline::GetShader(const char* name) {
	for(auto iter = m_Shaders.begin(); iter != m_Shaders.end();) {
		if(strcmp((*iter)->GetName(),name) == 0) {
			return (*iter);
		}
		iter++;
	}
	return NULL;
}
std::shared_ptr<Shader> GPUPipeline::GetShader(int index) {
	if(index >= m_Shaders.size()) {
		return NULL;
	}
	return m_Shaders[index];
}
bool SamplerState::AddState(std::shared_ptr<BlankState> state) {
	for(auto iter = m_States.begin(); iter != m_States.end(); iter++) {
		if((*iter) == state) {
			return false;
		}
	}
	m_States.push_back(state);
	return true;
}
std::shared_ptr<BlankState> SamplerState::FindState(fxState state) {
	for(auto iter = m_States.begin(); iter != m_States.end(); iter++) {
		if((*iter)->m_State = state) {
			return (*iter);
		}
	}
	return NULL;
}
bool SamplerState::RemoveState(fxState state) {
	for(auto iter = m_States.begin(); iter != m_States.end();) {
		if ((*iter)->m_State == state) {
			m_States.erase(iter);
			return true;
		}
		iter++;
	}
	return false;
}
Resource::Resource(const char* name, fxState resType) 
	: PassDesc(FX_RESOURCE_DESC_FLAG,name) {
	m_Data.appDepSize = false;
	m_Data.msaa = false;
	m_Data.external = false;
	m_ResourceType = resType;
	//flFxCore::Get().GetResourceRepository()->AddItem(this);
}
Resource::~Resource() {
	//flFxCore::Get().GetResourceRepository()->RemoveItem(this);
}
void Resource::SetDimensions(int w,int h,int d) {
	m_Data.dimensions[0] = w;
	m_Data.dimensions[1] = h;
	m_Data.dimensions[2] = d;
}
void Resource::ValidateAttachments() {
	if (m_Parent.lock()) {
		switch (m_ResourceType) {
		case FX_RESOURCE_RENDERTEX:
		{
			std::shared_ptr<FrameBufferObject> framebuffer = std::static_pointer_cast<FrameBufferObject>(m_Parent.lock()->Find(FX_FBO_TARGET_DESC_FLAG));
			if (framebuffer) {
				framebuffer->Attach(shared_from_this());
			}
			break;
		}
		case FX_RESOURCE_DEPTHTEX:
		{
			std::shared_ptr<FrameBufferObject> framebuffer = std::static_pointer_cast<FrameBufferObject>(m_Parent.lock()->Find(FX_FBO_TARGET_DESC_FLAG));
			if (framebuffer) {
				framebuffer->Attach(shared_from_this());
			}
			break;
		}
		}
	}
}
bool Resource::Validate() {
	/*if (m_Parent.lock()) {
		switch (m_ResourceType) {
		case FX_RESOURCE_RENDERTEX:
		{
			std::shared_ptr<FrameBufferObject> framebuffer = std::static_pointer_cast<FrameBufferObject>(m_Parent.lock()->Find(FX_FBO_TARGET_DESC_FLAG));
			if (framebuffer) {
				framebuffer->Attach(shared_from_this());
			}
			break;
		}
		case FX_RESOURCE_DEPTHTEX:
		{
			std::shared_ptr<FrameBufferObject> framebuffer = std::static_pointer_cast<FrameBufferObject>(m_Parent.lock()->Find(FX_FBO_TARGET_DESC_FLAG));
			if (framebuffer) {
				framebuffer->Attach(shared_from_this());
			}
			break;
		}
		}
	}*/
	return true;
}
bool Resource::Invalidate() {
	/*if (m_Parent.lock()) {
		switch (m_ResourceType) {
		case FX_RESOURCE_RENDERTEX:
		{
			std::shared_ptr<FrameBufferObject> framebuffer = std::static_pointer_cast<FrameBufferObject>(m_Parent.lock()->Find(FX_FBO_TARGET_DESC_FLAG));
			if (framebuffer) {
				framebuffer->Detach(shared_from_this());
			}
			break;
		}
		case FX_RESOURCE_DEPTHTEX:
		{
			std::shared_ptr<FrameBufferObject> framebuffer = std::static_pointer_cast<FrameBufferObject>(m_Parent.lock()->Find(FX_FBO_TARGET_DESC_FLAG));
			if (framebuffer) {
				framebuffer->Detach(shared_from_this());
			}
			break;
		}
		}
	}*/
	return true;
}
FrameBufferObject::FrameBufferObject(const char* name) 
	: PassDesc(FX_FBO_TARGET_DESC_FLAG,name) {
	//flFxCore::Get().GetFBORepository()->RemoveItem(this);
}
FrameBufferObject::~FrameBufferObject() {
	//flFxCore::Get().GetFBORepository()->RemoveItem(this);
}
bool FrameBufferObject::Validate() {
	if (m_Parent.lock()) {
		
	}
	return true;
}
bool FrameBufferObject::Invalidate() {
	if (m_Parent.lock()) {
		
	}
	return true;
}
bool FrameBufferObject::AddTextureResource(std::shared_ptr<Resource> res) {
	for(auto iter = m_Resources.begin(); iter != m_Resources.end(); iter++) {
		if((*iter) == res) {
			return false;
		}
	}
	m_Resources.push_back(res);
	return true;
}
std::shared_ptr<Resource> FrameBufferObject::GetTextureResource(int index) {
	if(index >= m_Resources.size()) {
		return NULL;
	}
	return m_Resources[index];
}
ShaderParameter::ShaderParameter(const char* name, float* value) 
	: PassDesc(FX_SHADER_PARAMETER_DESC_FLAG,name) {
	if(value) {
		m_Value = value;
	}
	//flFxCore::Get().GetShaderParameterRepository()->RemoveItem(this);
}
ShaderParameter::~ShaderParameter() {
	delete[] m_Value;
	//flFxCore::Get().GetShaderParameterRepository()->RemoveItem(this);
}
void ShaderParameter::SetValue(float* value) {
	if (value) {
		m_Value = value;
	}
}
