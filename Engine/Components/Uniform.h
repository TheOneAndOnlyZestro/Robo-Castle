#pragma once
#include "ComponentInfo.h"
#include "DebugTools/LogItem.h"


namespace GFX_Engine {
	template<typename T>
	struct Uniform
		:public LogItem
		{
			public:
			Uniform(const T& data) {

			}

			void Link(unsigned int ProgramID) {

			}
			virtual void Log() const {

			}

			private:
				T m_Data;
				int loc;
	};
}
