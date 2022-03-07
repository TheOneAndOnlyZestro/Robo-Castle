#pragma once
#include "DebugTools/LogItem.h"
#include "ComponentInfo.h"
#include <GL/glew.h>
namespace GFX_Engine {
	class Shader
		:public LogItem
	{
	public:
		Shader();
		Shader(const char* FilePath);

		~Shader();
		Shader(const Shader& rtside);
		Shader& operator=(const Shader& rtside);

		virtual void Log() const;
		void Enable() const;
		void Disable() const;
	private:
		class impl;
		impl* m_impl;
	};
}


