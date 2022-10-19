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

		void AddVoxels(const std::vector<VoxelData>& voxels);


		const std::vector<VoxelData>& GetAllVoxels() const { return mVoxels; }
		bool AnyVoxelsUpdated() const { return VoxelsUpdated; }

		void _resetvoxelupdated() { VoxelsUpdated = false; }
	private:
		bool VoxelsUpdated = false;
		
		//std::Vector<SVOTree> mVoxels
		std::vector<VoxelData> mVoxels;


	};
}