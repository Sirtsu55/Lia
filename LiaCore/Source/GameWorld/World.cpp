#include "World.h"

namespace Lia
{


	World::World()
	{
	}
	World::~World()
	{
	}
	void World::AddVoxels(const std::vector<VoxelData>& voxels)
	{

		mVoxels.insert(mVoxels.end(), voxels.begin(), voxels.end());
		VoxelsUpdated = true;
	}
}