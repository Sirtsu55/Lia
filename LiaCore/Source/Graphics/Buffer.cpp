#include "Buffer.h"


namespace Lia
{
	Buffer::Buffer(const wgpu::Device& dev, wgpu::BufferUsage usages, size_t size, void* data)
		:mDev(dev), mSize(size)
	{


		wgpu::BufferDescriptor bufDesc{};

		bufDesc.mappedAtCreation = false;
		bufDesc.size = size;
		bufDesc.usage = usages | wgpu::BufferUsage::CopyDst;
		bufDesc.nextInChain = nullptr;

		mBuffer = mDev.CreateBuffer(&bufDesc);

		if (data)
			UploadData(data, mSize, 0);
	}

	void Buffer::UploadData(void* data, uint32_t size, uint32_t offset)
	{

		auto queue = mDev.GetQueue();
		queue.WriteBuffer(mBuffer, offset, data, size);

		

	}

	Buffer::~Buffer()
	{

	}

}

