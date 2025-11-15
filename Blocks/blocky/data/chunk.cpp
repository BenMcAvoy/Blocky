#include "chunk.h"

#include <print>

using namespace Blocky;

void World::ensureSubChunkExists(const WorldPosition& pos) {
	if (subChunks.find(pos) == subChunks.end()) {
		/*static int chunksAllocated = 0;
		chunksAllocated++;

		std::println("Allocating new sub-chunk at ({}, {}, {}), total allocated: {}", pos.x, pos.y, pos.z, chunksAllocated);*/

		SubChunk newSubChunk = {};
		subChunks[pos] = newSubChunk;
	}
}

SubChunk* World::getSubChunk(const WorldPosition& pos) {
	ensureSubChunkExists(pos);
	return &subChunks[pos];
}

std::optional<Voxel> World::getVoxel(const WorldPosition& pos) {
	WorldPosition subChunkPos = {
		.x = pos.x / SUBCHUNK_SIZE,
		.y = pos.y / SUBCHUNK_SIZE,
		.z = pos.z / SUBCHUNK_SIZE
	};

	auto it = subChunks.find(subChunkPos);
	if (it == subChunks.end()) {
		return std::nullopt;
	}

	int localX = pos.x % SUBCHUNK_SIZE;
	int localY = pos.y % SUBCHUNK_SIZE;
	int localZ = pos.z % SUBCHUNK_SIZE;

	int index = localY * SUBCHUNK_SIZE * SUBCHUNK_SIZE + localZ * SUBCHUNK_SIZE + localX;

	SubChunk& subChunk = it->second;
	return subChunk.voxels[index];
}

void World::setVoxel(const WorldPosition& pos, std::optional<Voxel> voxel) {
	WorldPosition subChunkPos = {
		.x = pos.x / SUBCHUNK_SIZE,
		.y = pos.y / SUBCHUNK_SIZE,
		.z = pos.z / SUBCHUNK_SIZE
	};

	int localX = pos.x % SUBCHUNK_SIZE;
	int localY = pos.y % SUBCHUNK_SIZE;
	int localZ = pos.z % SUBCHUNK_SIZE;

	int index = localY * SUBCHUNK_SIZE * SUBCHUNK_SIZE + localZ * SUBCHUNK_SIZE + localX;

	if (voxel.has_value()) {
		ensureSubChunkExists(subChunkPos);
		SubChunk& subChunk = subChunks[subChunkPos];
		subChunk.voxels[index] = voxel.value();
	} else {
		auto it = subChunks.find(subChunkPos);

		if (it != subChunks.end()) {
			SubChunk& subChunk = it->second;
			subChunk.voxels[index] = Voxel{ .rawByte = 0 };
			bool isEmpty = true;

			for (const auto& v : subChunk.voxels) {
				if (v.rawByte != 0) {
					isEmpty = false;
					break;
				}
			}

			if (isEmpty) {
				subChunks.erase(it);
			}
		}
	}
}

void World::removeSubChunkIfEmpty(const WorldPosition& pos) {
	auto it = subChunks.find(pos);

	if (it != subChunks.end()) {
		SubChunk& subChunk = it->second;
		bool isEmpty = true;
		for (const auto& v : subChunk.voxels) {
			if (v.rawByte != 0) {
				isEmpty = false;
				break;
			}
		}

		if (isEmpty) {
			subChunks.erase(it);
		}
	}
}

void SubChunk::calculateFaceVertices() {

}
