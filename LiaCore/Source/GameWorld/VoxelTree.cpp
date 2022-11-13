#include "VoxelTree.h"

namespace Lia
{
	//Creates a VoxelTree as an acceleration structure for raytracing
	//rawVoxels will be moved into VoxelTree's ownership
	VoxelTree::VoxelTree(const std::vector<VoxelData>& rawVoxels)
	{

		float minX = 0, minY = 0, minZ = 0;

		float maxX = 0, maxY = 0, maxZ = 0;

		//  Still have to separate into optimal sized chunks of blocks
		//Loop gets biggest bounding box to cover all the voxels
		for (auto& v : rawVoxels)
		{
			auto size = 0.5;
				auto minLoc = v.Position - glm::vec3(size);
				auto maxLoc = v.Position + glm::vec3(size);

			if (minLoc.x < minX)
				minX= minLoc.x;
			if (minLoc.y < minY)
				minY = minLoc.y;
			if (minLoc.z < minZ)
				minZ = minLoc.z;
			if (maxLoc.x > maxX)
				maxX = maxLoc.x;
			if (maxLoc.y > maxY)
				maxY = maxLoc.y;
			if (maxLoc.z > maxZ)
				maxZ = maxLoc.z;

		}




		//mVoxelNodes.push_back(
		//	{ 
		//	glm::vec3(minX, minY, minZ),
		//	glm::vec3(maxX, maxY, maxZ),
		//	0
		//	}
		//);
		//

	}
	VoxelTree::~VoxelTree()
	{

	}
}