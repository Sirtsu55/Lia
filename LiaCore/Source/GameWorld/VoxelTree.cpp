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
		auto s1 = maxVoxelLoc / 4;
		auto s2 = maxVoxelLoc / 2;
		auto s3 = maxVoxelLoc / 2;
		auto s4 = maxVoxelLoc / 2;

		for (auto& v : rawVoxels)
		{
			v.Size = abs(v.Size);
			auto minLoc = v.Position - glm::vec3(v.Size);
			auto maxLoc = v.Position + glm::vec3(v.Size);

		}


		//Count how many voxels are at each of 8 subdivisions 
		//discard empty spaces 
		//look at the most dense areas and make a dense tree there
		//use recursion

	}
	VoxelTree::~VoxelTree()
	{
	}
}