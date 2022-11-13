#include "World.h"

namespace Lia
{


	World::World()
	{
	}

	World::~World()
	{
	}


	//The voxels should be near to eachother for performance reasons
	void World::AddVoxels(const std::vector<VoxelData>& voxels, const glm::vec3 worldPosition)
	{
		auto [minAABB, maxAABB] = GetBoundingBoxofVoxels(voxels);


		glm::uvec3 dim = glm::abs(maxAABB - minAABB);

		uint32_t SDFSize = (dim.x * dim.y * dim.z);
		uint32_t start = mVoxelSDF.size();
		mVoxelsTree.push_back({
			glm::vec4(minAABB + worldPosition, 0),
			glm::vec4(maxAABB + worldPosition, 0),
			start, SDFSize/2});

		//Add padding, because it has to be aligned to 4 bytes
		//adding 2 because at the start it has a uint32_t indicating the SDF size
		// sizeof(2 * VoxelSDF) = sizeof(uint32_t)
		auto padding = (start + SDFSize  ) % 4;


		mVoxelSDF.resize(start + SDFSize + padding);

		//TODO: Optimize this and add color feature
		//Maybe move SDF generation to another thread
		VoxelSDF* currentSDF = &mVoxelSDF[start];

		//Access by: x*y+z
		for (uint32_t x = 0; x < dim.x; x++)
		{
			for (uint32_t y = 0;y < dim.y; y++)
			{
				for (uint32_t z = 0; z < dim.z; z++)
				{
					auto dist = GetDistanceToNearestVoxelFromPoint(glm::vec3(x, y, z), voxels);
					uint8_t steps = 0;
					if (dist >= 15)
					{
						steps = 15;
					}
					else
					{
						steps = static_cast<uint8_t>(floor(dist));
					}

					currentSDF->Step = steps;

					//TOOD: Add Material ID
					uint16_t matID = 0;
					currentSDF->MaterialID = matID;

					//move onto next sdf
					currentSDF += 1;
				}
			}
		}
		//After voxelSDF is updated
		VoxelsUpdated = true;
	}


	std::pair<glm::vec3, glm::vec3> World::GetBoundingBoxofVoxels(const std::vector<VoxelData>& voxels) const
	{
		//initializze with a voxel position, because null initializing may cause a component to stay as 0
		glm::vec3 minAABB = voxels[0].Position;
		glm::vec3 maxAABB = voxels[0].Position;

		//Can probably be optimized further
		for (auto& v : voxels)
		{
			auto size = 0.5;
			auto minLoc = v.Position - glm::vec3(size);
			auto maxLoc = v.Position + glm::vec3(size);

			if (minLoc.x < minAABB.x)
				minAABB.x = minLoc.x;

			if (minLoc.y < minAABB.y)
				minAABB.y = minLoc.y;

			if (minLoc.z < minAABB.z)
				minAABB.z = minLoc.z;

			if (maxLoc.x > maxAABB.x)
				maxAABB.x = maxLoc.x;

			if (maxLoc.y > maxAABB.y)
				maxAABB.y = maxLoc.y;

			if (maxLoc.z > maxAABB.z)
				maxAABB.z = maxLoc.z;

		}

		return std::make_pair(minAABB, maxAABB);
	}
	float World::GetDistanceToNearestVoxelFromPoint(const glm::vec3& point, const std::vector<VoxelData>& voxels) const
	{
		float minDistance = FLT_MAX; // Set to max value, because it gets corrected in the loop
		for (auto& v : voxels)
		{
			float dist = glm::distance(v.Position, point);
			if (dist < minDistance)
				minDistance = dist;
		}

		return minDistance;
	}

}