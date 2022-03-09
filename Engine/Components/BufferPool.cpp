#include "BufferPool.h"
class GFX_Engine::BufferPool::impl {
public:
	impl(){}
	static void DefaultSetAttributeFunction();
	static DrawCallData DefaultGenerateElementsFunction(unsigned int Quads);
public:
	ComponentInfo<2> m_ComponentInfo;
	DrawCallData m_DrawCallData;
	std::vector<Geometry::Vertex> m_Vertices;
	std::function<void()> m_SetUpAttribFunc;
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
GFX_Engine::BufferPool::DrawCallData GFX_Engine::BufferPool::impl::DefaultGenerateElementsFunction(unsigned int Quads)
{
	DrawCallData dcd;
	unsigned int offset = 0;
	unsigned int IndiceNumber = Quads * 6;
	unsigned int* Indices = new unsigned int[IndiceNumber];

	for (unsigned int i = 0; i < Quads; i++) {
		Indices[2 * i +  offset] = offset;
		Indices[2 * i + 1 + offset] = offset + 1;
		Indices[2 * i + 2 + offset] = offset + 2;
		Indices[2 * i + 3 + offset] = offset + 2;
		Indices[2 * i + 4 + offset] = offset + 3;
		Indices[2 * i + 5 + offset] = offset;

		offset += 4;
	}
	dcd.PrimitiveType = GL_TRIANGLES;
	dcd.IndiceNumber = IndiceNumber;
	dcd.Indices = Indices;
	return dcd;
}
GFX_Engine::BufferPool::BufferPool()
{
	m_impl = new impl();
	m_impl->m_ComponentInfo.m_Comptype = GFX_Engine::ComponentInfo<2>::ComponentType::GFX_BUFFER_POOL;
	m_impl->m_ComponentInfo.m_Comptype = GFX_Engine::ComponentInfo<2>::ComponentType::GFX_BUFFER_POOL;

	//Opengl Functions
	glGenBuffers(1, &m_impl->m_ComponentInfo.m_RendererID[0]);
	glBindBuffer(GL_VERTEX_ARRAY, m_impl->m_ComponentInfo.m_RendererID[0]);
	glBufferData(GL_VERTEX_ARRAY, 1024, nullptr, GL_DYNAMIC_DRAW);

	m_impl->m_SetUpAttribFunc = impl::DefaultSetAttributeFunction;
	m_impl->m_SetUpAttribFunc();

}
GFX_Engine::BufferPool::BufferPool(const std::function<void()>& SetUpAttribFunc)
{
	m_impl = new impl();
	m_impl->m_ComponentInfo.m_Comptype = GFX_Engine::ComponentInfo<2>::ComponentType::GFX_BUFFER_POOL;
	m_impl->m_ComponentInfo.m_Comptype = GFX_Engine::ComponentInfo<2>::ComponentType::GFX_BUFFER_POOL;

	//Opengl Functions
	glGenBuffers(1, &m_impl->m_ComponentInfo.m_RendererID[0]);
	glBindBuffer(GL_VERTEX_ARRAY, m_impl->m_ComponentInfo.m_RendererID[0]);
	glBufferData(GL_VERTEX_ARRAY, 1024, nullptr, GL_DYNAMIC_DRAW);

	m_impl->m_SetUpAttribFunc = SetUpAttribFunc;
	m_impl->m_SetUpAttribFunc();
}
GFX_Engine::BufferPool::BufferPool(const std::vector<Geometry::Vertex>& VertexList) {

	m_impl = new impl();
	m_impl->m_Vertices = VertexList;
	m_impl->m_ComponentInfo.m_Comptype = GFX_Engine::ComponentInfo<2>::ComponentType::GFX_BUFFER_POOL;
	m_impl->m_ComponentInfo.m_Comptype = GFX_Engine::ComponentInfo<2>::ComponentType::GFX_BUFFER_POOL;

	//Opengl Functions
	glGenBuffers(1, &m_impl->m_ComponentInfo.m_RendererID[0]);
	glBindBuffer(GL_VERTEX_ARRAY, m_impl->m_ComponentInfo.m_RendererID[0]);
	glBufferData(GL_VERTEX_ARRAY, Geometry::Vertex::GetSize() * VertexList.size(), VertexList[0].GetVertexRef(), GL_DYNAMIC_DRAW);

	m_impl->m_SetUpAttribFunc = impl::DefaultSetAttributeFunction;
	m_impl->m_SetUpAttribFunc();
	m_impl->m_DrawCallData = impl::DefaultGenerateElementsFunction(VertexList.size() / 6);

	glGenBuffers(1, &m_impl->m_ComponentInfo.m_RendererID[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_impl->m_ComponentInfo.m_RendererID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_impl->m_DrawCallData.IndiceNumber * sizeof(unsigned int), m_impl->m_DrawCallData.Indices, GL_DYNAMIC_DRAW);

}

GFX_Engine::BufferPool::BufferPool(const Geometry::Vertex* VertexList, unsigned int BufferSize)
{
	m_impl = new impl();
	m_impl->m_Vertices.resize(BufferSize);
	memcpy_s(&m_impl->m_Vertices[0].x, BufferSize, VertexList->GetVertexRef(), BufferSize);

	m_impl->m_ComponentInfo.m_Comptype = GFX_Engine::ComponentInfo<2>::ComponentType::GFX_BUFFER_POOL;
	m_impl->m_ComponentInfo.m_Comptype = GFX_Engine::ComponentInfo<2>::ComponentType::GFX_BUFFER_POOL;

	//Opengl Functions
	glGenBuffers(1, &m_impl->m_ComponentInfo.m_RendererID[0]);
	glBindBuffer(GL_VERTEX_ARRAY, m_impl->m_ComponentInfo.m_RendererID[0]);
	glBufferData(GL_VERTEX_ARRAY, Geometry::Vertex::GetSize() * BufferSize, m_impl->m_Vertices[0].GetVertexRef(), GL_DYNAMIC_DRAW);

	m_impl->m_SetUpAttribFunc = impl::DefaultSetAttributeFunction;
	m_impl->m_SetUpAttribFunc();

	m_impl->m_DrawCallData = impl::DefaultGenerateElementsFunction(BufferSize / 6);

	glGenBuffers(1, &m_impl->m_ComponentInfo.m_RendererID[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_impl->m_ComponentInfo.m_RendererID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_impl->m_DrawCallData.IndiceNumber * sizeof(unsigned int), m_impl->m_DrawCallData.Indices, GL_DYNAMIC_DRAW);
}

GFX_Engine::BufferPool::BufferPool(const std::vector<Geometry::Vertex>& VertexList, const std::function<void()>& SetUpAttribFun)
{
	m_impl = new impl();
	m_impl->m_Vertices = VertexList;
	m_impl->m_ComponentInfo.m_Comptype = GFX_Engine::ComponentInfo<2>::ComponentType::GFX_BUFFER_POOL;
	m_impl->m_ComponentInfo.m_Comptype = GFX_Engine::ComponentInfo<2>::ComponentType::GFX_BUFFER_POOL;

	//Opengl Functions
	glGenBuffers(1, &m_impl->m_ComponentInfo.m_RendererID[0]);
	glBindBuffer(GL_VERTEX_ARRAY, m_impl->m_ComponentInfo.m_RendererID[0]);
	glBufferData(GL_VERTEX_ARRAY, Geometry::Vertex::GetSize() * VertexList.size(), VertexList[0].GetVertexRef(), GL_DYNAMIC_DRAW);

	m_impl->m_SetUpAttribFunc = SetUpAttribFun;
	m_impl->m_SetUpAttribFunc();
	m_impl->m_DrawCallData = impl::DefaultGenerateElementsFunction(VertexList.size() / 6);

	glGenBuffers(1, &m_impl->m_ComponentInfo.m_RendererID[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_impl->m_ComponentInfo.m_RendererID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_impl->m_DrawCallData.IndiceNumber * sizeof(unsigned int), m_impl->m_DrawCallData.Indices, GL_DYNAMIC_DRAW);
}

GFX_Engine::BufferPool::BufferPool(const Geometry::Vertex* VertexList, unsigned int BufferSize, const std::function<void()>& SetUpAttribFun)
{
	m_impl = new impl();
	m_impl->m_Vertices.resize(BufferSize);
	memcpy_s(&m_impl->m_Vertices[0].x, BufferSize, VertexList->GetVertexRef(), BufferSize);

	m_impl->m_ComponentInfo.m_Comptype = GFX_Engine::ComponentInfo<2>::ComponentType::GFX_BUFFER_POOL;
	m_impl->m_ComponentInfo.m_Comptype = GFX_Engine::ComponentInfo<2>::ComponentType::GFX_BUFFER_POOL;

	//Opengl Functions
	glGenBuffers(1, &m_impl->m_ComponentInfo.m_RendererID[0]);
	glBindBuffer(GL_VERTEX_ARRAY, m_impl->m_ComponentInfo.m_RendererID[0]);
	glBufferData(GL_VERTEX_ARRAY, Geometry::Vertex::GetSize() * BufferSize, m_impl->m_Vertices[0].GetVertexRef(), GL_DYNAMIC_DRAW);

	m_impl->m_SetUpAttribFunc = SetUpAttribFun;
	m_impl->m_SetUpAttribFunc();

	m_impl->m_DrawCallData = impl::DefaultGenerateElementsFunction(BufferSize / 6);

	glGenBuffers(1, &m_impl->m_ComponentInfo.m_RendererID[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_impl->m_ComponentInfo.m_RendererID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_impl->m_DrawCallData.IndiceNumber * sizeof(unsigned int), m_impl->m_DrawCallData.Indices, GL_DYNAMIC_DRAW);
}

void GFX_Engine::BufferPool::UpdateBufferPool(const std::vector<Geometry::Vertex>& NewVertexList)
{
	m_impl->m_Vertices = NewVertexList;
	glBindBuffer(GL_ARRAY_BUFFER, m_impl->m_ComponentInfo.m_RendererID[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_impl->m_Vertices.size() * Geometry::Vertex::GetSize(),
	m_impl->m_Vertices[0].GetVertexRef());

	m_impl->m_DrawCallData = impl::DefaultGenerateElementsFunction(NewVertexList.size() / 6);

	glGenBuffers(1, &m_impl->m_ComponentInfo.m_RendererID[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_impl->m_ComponentInfo.m_RendererID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_impl->m_DrawCallData.IndiceNumber * sizeof(unsigned int), m_impl->m_DrawCallData.Indices, GL_DYNAMIC_DRAW);
}

void GFX_Engine::BufferPool::UpdateBufferPool(const Geometry::Vertex* VertexList, unsigned int BufferSize)
{
	m_impl->m_Vertices.resize(BufferSize);
	memcpy_s(&m_impl->m_Vertices[0].x, BufferSize, VertexList->GetVertexRef(), BufferSize);

	glBindBuffer(GL_ARRAY_BUFFER, m_impl->m_ComponentInfo.m_RendererID[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, BufferSize * Geometry::Vertex::GetSize(),
	VertexList->GetVertexRef());

	m_impl->m_DrawCallData = impl::DefaultGenerateElementsFunction(BufferSize/ 6);

	glGenBuffers(1, &m_impl->m_ComponentInfo.m_RendererID[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_impl->m_ComponentInfo.m_RendererID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_impl->m_DrawCallData.IndiceNumber * sizeof(unsigned int), m_impl->m_DrawCallData.Indices, GL_DYNAMIC_DRAW);
}

void GFX_Engine::BufferPool::Enable() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_impl->m_ComponentInfo.m_RendererID[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_impl->m_ComponentInfo.m_RendererID[1]);
}

void GFX_Engine::BufferPool::Disable() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GFX_Engine::BufferPool::Log() const
{

}

GFX_Engine::BufferPool::DrawCallData GFX_Engine::BufferPool::GetDrawCallInfo() const
{
	return m_impl->m_DrawCallData;
}

GFX_Engine::ComponentInfo<2> GFX_Engine::BufferPool::GetComponentInfo()
{
	return m_impl->m_ComponentInfo;
}

GFX_Engine::BufferPool::~BufferPool()
{
	delete m_impl;
}

GFX_Engine::BufferPool::BufferPool(const BufferPool& rtside)
{
	m_impl = new impl(*(rtside.m_impl));
}

GFX_Engine::BufferPool& GFX_Engine::BufferPool::operator=(const BufferPool& rtside)
{
	m_impl = new impl(*(rtside.m_impl));
	return *this;
}
