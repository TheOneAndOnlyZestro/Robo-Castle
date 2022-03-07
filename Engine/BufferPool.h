#pragma once
namespace GFX_Engine {
	class BufferPool
	{
	public:
		BufferPool();

		~BufferPool();
		BufferPool(const BufferPool& rtside);
		BufferPool& operator=(const BufferPool& rtside);

	private:
		class impl;
		impl* m_impl;
	};

}

