#pragma once
#include "VoxelTree.h"


namespace Lia
{

	class World
	{

	public:
		World();

		~World();

		World(World&) = delete;
		World& operator=(World&) = delete;

		void AddVoxels(const std::vector<VoxelData>& voxels, const glm::vec3 worldPosition);


		
	private:



		std::pair<glm::vec3, glm::vec3> GetBoundingBoxofVoxels(
			const std::vector<VoxelData>& voxels
		) const;
		float GetDistanceToNearestVoxelFromPoint(
			const glm::vec3& point,
			const std::vector<VoxelData>& voxels
		) const;

		//Gets reset when RayTracer Class renders the scene
		bool VoxelsUpdated = false;
		
		std::vector<VoxelNode> mVoxelsTree;

		// at the start of every a Signed distance field of an object 
		//there is a 4byte integer specifying the length of the SDF
		std::vector<VoxelSDF> mVoxelSDF;

		friend class RayTracer;
	};
}