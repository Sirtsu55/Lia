#pragma once

namespace Lia
{
	struct Voxel
	{
		glm::vec3 Position;
		float Size;
	};
	class World
	{

	public:
		World();

		~World();

		World(World&) = delete;
		World& operator=(World&) = delete;

		void AddVoxels(const std::vector<Voxel>& voxels);


		const std::vector<Voxel>& GetAllVoxels() const { return mVoxels; }
		bool AnyVoxelsUpdated() const { return VoxelsUpdated; }

		void _resetvoxelupdated() { VoxelsUpdated = false; }
	private:
		bool VoxelsUpdated = false;
		
		//std::Vector<SVOTree> mVoxels
		std::vector<Voxel> mVoxels;


	};
}