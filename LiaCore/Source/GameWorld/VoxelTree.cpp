#include "VoxelTree.h"

namespace Lia
{

	VoxelTree::VoxelTree(const std::vector<VoxelData>& rawVoxels)
	{
		glm::vec3 minVoxelLoc = {};
		glm::vec3 maxVoxelLoc = {};
		

		//Loop gets biggest bounding box to cover all the voxels
		for (auto& v : rawVoxels)
		{
			v.Size = abs(v.Size);
			auto minLoc = v.Position - glm::vec3(v.Size);
			auto maxLoc = v.Position + glm::vec3(v.Size);

			if (minLoc < minVoxelLoc)
				minVoxelLoc = minLoc;
			if (maxLoc < maxVoxelLoc)
				maxVoxelLoc = maxLoc;
		}


		

	}
	VoxelTree::~VoxelTree()
	{
	}
}