
namespace Lia
{

	class Buffer
	{
	public:
		Buffer(const wgpu::Device& dev, wgpu::BufferUsage usages, size_t size, void* data = nullptr);
		~Buffer();


		Buffer(Buffer&) = delete;
		Buffer& operator=(Buffer&) = delete;

		void UploadData(void* data, uint32_t size, uint32_t offset);
		uint32_t GetSize() const { return mSize; }
		wgpu::Buffer Get() const { return mBuffer; }
	private:

		wgpu::Device mDev;
		wgpu::Buffer mBuffer;

		uint32_t mSize;
	};
}