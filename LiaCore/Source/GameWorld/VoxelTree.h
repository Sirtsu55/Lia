#pragma once
namespace Lia
{
	struct VoxelData
	{
		//has to be aligned(std430)
		glm::vec3 Position;
		float Size;
	};

	struct VoxelNode
	{
		//has to be aligned(std430)
		VoxelData Voxel; // 16 bytes
		uint8_t NextChildMask; // 1 byte
		glm::vec3 color;	// 12 bytes
	};
	class VoxelTree
	{
	public:
		VoxelTree(const std::vector<VoxelData>& rawVoxels);

		~VoxelTree();

		VoxelTree(VoxelTree&) = delete;
		VoxelTree& operator=(VoxelTree&) = delete;
	private:
		std::vector<VoxelNode> 

		
	};
}