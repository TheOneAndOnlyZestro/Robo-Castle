#pragma once
#include "DebugTools/LogItem.h"
#include "ComponentInfo.h"
#include "Math/Vertex.h"
#include <GL/glew.h>

#include <functional>
#include <vector>
namespace GFX_Engine {
	class BufferPool
		:public LogItem
	{
	public:
		struct DrawCallData {
			GLenum PrimitiveType;
			unsigned int IndiceNumber;
		};
	public:
		BufferPool();
		explicit BufferPool(const std::function<void()>& SetUpAttribFunc);

		explicit BufferPool(const std::vector<Geometry::Vertex>& VertexList);
		BufferPool(const Geometry::Vertex* VertexList, unsigned int BufferSize);

		BufferPool(const std::vector<Geometry::Vertex>& VertexList, const std::function<void()>& SetUpAttribFun);
		BufferPool(const Geometry::Vertex* VertexList, unsigned int BufferSize, const std::function<void()>& SetUpAttribFun);

		void UpdateBufferPool(const std::vector<Geometry::Vertex>& NewVertexList);
		void UpdateBufferPool(const Geometry::Vertex* VertexList, unsigned int BufferSize);

		void Enable() const;
		void Disable() const;

		virtual void Log() const;
		DrawCallData GetDrawCallInfo() const;

		~BufferPool();
		BufferPool(const BufferPool& rtside);
		BufferPool& operator=(const BufferPool& rtside);

	private:
		class impl;
		impl* m_impl;
	};

}

