#include "blocky/engine.h"

#include <thread>

int main() {
	// Construct a new world
	Blocky::World world;

	// Average MC world with 32 chunk render distance is
	// 128 x 128 x 16 chunks in our engine

	for (size_t x = 0; x < 128 * 32; x++) {
		for (size_t z = 0; z < 128 * 32	;z++) {
			for (size_t y = 0; y < 16 * 32; y++) {
				Blocky::WorldPosition pos = {
					.x = static_cast<int64_t>(x),
					.y = static_cast<int64_t>(y),
					.z = static_cast<int64_t>(z)
				};

				Blocky::Voxel voxel{};
				voxel.colour = static_cast<Blocky::Colour>((x + y + z) % 6);
				voxel.isSolid = true;

				world.setVoxel(pos, voxel);
			}
		}
	}

	while (true) { std::this_thread::sleep_for(std::chrono::seconds(1)); }

	return 0;
}
