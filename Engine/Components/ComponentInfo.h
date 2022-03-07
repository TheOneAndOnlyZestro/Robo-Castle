#pragma once
struct ComponentInfo {
public:
	enum class ComponentType {
		GFX_BUFFER_POOL, GFX_SHADER
	};
public:
	ComponentInfo(){}
	ComponentInfo(unsigned int RendererID, ComponentType Type) 
		:m_RendererID(RendererID), m_Comptype(Type)
	{}
public:
	unsigned int m_RendererID;
	ComponentType m_Comptype;
};