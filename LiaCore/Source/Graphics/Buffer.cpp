#include "Buffer.h"


namespace Lia
{
	Buffer::Buffer(const wgpu::Device& dev, wgpu::BufferUsage usages, size_t size, void* data)
	{
		wgpu::BufferDescriptor bufDesc{};
		bufDesc.mappedAtCreation = false;
		bufDesc.size = size;
		bufDesc.usage = usages;
		bufDesc.nextInChain = nullptr;


		
	}
	Buffer::~Buffer()
	{

	}

}

