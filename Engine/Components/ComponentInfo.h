#pragma once
#include <initializer_list>
namespace GFX_Engine {
	template<unsigned int Count>
	struct ComponentInfo {
	public:
		enum class ComponentType {
			GFX_BUFFER_POOL, GFX_SHADER
		};
	public:
		ComponentInfo<Count>() {}
		ComponentInfo<Count>(const std::initializer_list<unsigned int>& RendererIDs, ComponentType Type)
		{
			m_Comptype = Type;
			if (RendererIDs.size() > Count) {
				for (unsigned int i = 0; i < Count; i++) {
					m_RendererID[i] = RendererIDs[i];
				}
			}
			
		}

		unsigned int Count() { return Count; }

	public:
		unsigned int m_RendererID[Count];
		ComponentType m_Comptype;
	};
}
