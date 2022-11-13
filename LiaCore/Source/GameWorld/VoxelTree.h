#pragma once
namespace Lia
{
	struct VoxelData
	{
		//has to be aligned(std430)
		glm::vec3 Position;
		glm::vec4 Color;	// 12 bytes

	};


	struct VoxelNode
	{
		//has to be aligned(std430)
		glm::vec4 MinAABB; // 16 bytes
		glm::vec4 MaxAABB; // 16 bytes

		//TODO: Pack this into the unused bytes in vec4
		uint32_t GpuBufferSDFStart; // 4 bytes
		uint32_t GpuBufferSDFEnd; // 4 bytes

	};



	//Total of 16bits = 2byte
	struct VoxelSDF
	{
		uint16_t Step : 4; // 4 bits
		uint16_t MaterialID : 12;

	};



	class VoxelTree
	{
	public:
		VoxelTree(const std::vector<VoxelData>& rawVoxels);

		~VoxelTree();

		VoxelTree(VoxelTree&) = delete;
		VoxelTree& operator=(VoxelTree&) = delete;
	private:






		
	};
}