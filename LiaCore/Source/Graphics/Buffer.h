
namespace Lia
{

	class Buffer
	{
	public:

		Buffer(const wgpu::Device& dev, wgpu::BufferUsage usages, size_t size, void* data = nullptr);
		~Buffer();


		Buffer(Buffer&) = delete;
		Buffer& operator=(Buffer&) = delete;

	private:

		wgpu::Buffer mBuffer;
	};
}