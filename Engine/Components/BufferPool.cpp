#include "BufferPool.h"
class GFX_Engine::BufferPool::impl {
public:
	impl(){}
	static void DefaultSetAttributeFunction();
	static DrawCallData DefaultGenerateElementsFunction(unsigned int Quads);
public:
	ComponentInfo m_VertexBufferInfo;
	ComponentInfo m_ElementsInfo;
	std::vector<Geometry::Vertex> m_Vertices;
};

void GFX_Engine::BufferPool::impl::DefaultSetAttributeFunction() {

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Geometry::Vertex::GetSize(), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, Geometry::Vertex::GetSize(), (void *) (sizeof(float) * 3));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, Geometry::Vertex::GetSize(), (void*)((sizeof(float) * 3) + (sizeof(float) * 2)));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_UNSIGNED_INT, GL_FALSE, Geometry::Vertex::GetSize(), (void*)(  (sizeof(float) * 3 ) + ( sizeof(float) * 2)  + (sizeof(float) * 4) ));
}
GFX_Engine::BufferPool::BufferPool(const std::vector<Geometry::Vertex>& VertexList) {

	m_impl = new impl();
	m_impl->m_Vertices = VertexList;
	m_impl->m_VertexBufferInfo.m_Comptype = GFX_Engine::ComponentInfo::ComponentType::GFX_BUFFER_POOL;
	m_impl->m_ElementsInfo.m_Comptype = GFX_Engine::ComponentInfo::ComponentType::GFX_BUFFER_POOL;

	//Opengl Functions
	glGenBuffers(1, &m_impl->m_VertexBufferInfo.m_RendererID);
	glBindBuffer(GL_VERTEX_ARRAY, m_impl->m_VertexBufferInfo.m_RendererID);
	glBufferData(GL_VERTEX_ARRAY, Geometry::Vertex::GetSize(), VertexList[0].GetVertexRef(), GL_DYNAMIC_DRAW);

	impl::DefaultSetAttributeFunction();

	DrawCallData dcd = impl::DefaultGenerateElementsFunction(VertexList.size() / 6);

	glGenBuffers(1, &m_impl->m_ElementsInfo.m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_impl->m_ElementsInfo.m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dcd.IndiceNumber * sizeof(unsigned int), dcd.Indices, GL_DYNAMIC_DRAW);

}
