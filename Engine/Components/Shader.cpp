#include "Shader.h"
class GFX_Engine::Shader::impl {
public:
	impl() {}
public:
	void CreateShaderProgram();
	std::string ParseShader(const std::string& FilePath);
public:
	ComponentInfo<1> m_ComponentInfo;
	std::string m_FilePath;
};
void GFX_Engine::Shader::impl::CreateShaderProgram() {
	std::string vsSrc = ParseShader(m_FilePath + std::string("/VertexShader.shader"));
	std::string fsSrc = ParseShader(m_FilePath + std::string("/FragmentShader.shader"));

	char** vsSrcC = new char*;
	char** fsSrcC = new char*;
	memcpy_s(*vsSrcC, vsSrc.size() * sizeof(char), vsSrc.c_str(), vsSrc.size() * sizeof(char));
	memcpy_s(*fsSrcC, fsSrc.size() * sizeof(char), fsSrc.c_str(), fsSrc.size() * sizeof(char));

	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, vsSrcC,(int *) (vsSrc.size() * sizeof(char)));
	glCompileShader(vs);

	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, fsSrcC, (int*)(fsSrc.size() * sizeof(char)));
	glCompileShader(fs);

	m_ComponentInfo.m_RendererID[0] = glCreateProgram();
	glAttachShader(m_ComponentInfo.m_RendererID[0], vs);
	glAttachShader(m_ComponentInfo.m_RendererID[0], fs);

	glValidateProgram(m_ComponentInfo.m_RendererID[0]);
	glLinkProgram(m_ComponentInfo.m_RendererID[0]);
	
	glUseProgram(m_ComponentInfo.m_RendererID[0]);
	
	glDeleteShader(vs);
	glDeleteShader(fs);

}
GFX_Engine::Shader::Shader(const std::string& FilePath)
{
	m_impl = new impl();
	m_impl->m_FilePath = FilePath;
	m_impl->CreateShaderProgram();
}
