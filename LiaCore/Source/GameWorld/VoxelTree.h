#pragma once
namespace Lia
{
	struct VoxelData
	{
		//has to be aligned(std430)
		glm::vec3 Position;
		float Size;
		glm::vec4 Color;	// 12 bytes

	};



	class VoxelTree
	{
	public:
		VoxelTree(const std::vector<VoxelData>& rawVoxels);

		~VoxelTree();

		VoxelTree(VoxelTree&) = delete;
		VoxelTree& operator=(VoxelTree&) = delete;
	private:
		struct VoxelNode
		{
			//has to be aligned(std430)
			VoxelData Voxel; // 16 bytes
			uint32_t GpuBufferSDFStart; // 4 bytes

		};
		struct VoxelSDF
		{
			uint8_t Step0and1; // 4 bytes

		};


		std::vector<VoxelNode> 

		
	};
}