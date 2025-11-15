#pragma once

//#include "block.h"

#include <glm/glm.hpp>

#include <map>
#include <vector>
#include <optional>

namespace Blocky {
	/// Specifies the size of a sub-chunk along one axis, total volume would be SUBCHUNK_SIZE^3
	constexpr int SUBCHUNK_SIZE = 32; // should be a cache/SIMD friendly size

	enum class Colour : uint8_t {
		Red = 0,
		Green,
		Blue,
		Yellow,
		Black,
		White
	};

	union Voxel {
		struct {
			Colour colour : 5; /// 32 possible colours
			bool isSolid : 1; /// 1 bit for solid/non-solid
			uint8_t reserved : 2; /// 2 bits reserved for future use
		};

		uint8_t rawByte; /// Raw byte representation, whole 8 bits
	};

	/// Vertex pull data to represent a voxel face, these are sent in a SSBO to the GPU
	struct VoxelFaceVertex {
		glm::vec3 position; // Position in world space
		glm::vec3 normal;   // Normal vector for lighting
		Colour colour;      // Colour of the voxel
	};

	/**
	 * @brief Represents a sub-chunk of blocks within a chunk.
	 */
	struct SubChunk {
		Voxel voxels[SUBCHUNK_SIZE * SUBCHUNK_SIZE * SUBCHUNK_SIZE];

		std::vector<VoxelFaceVertex> faceVertices; /// Precomputed face vertices for rendering

		void calculateFaceVertices();
	};

	/**
	 * @brief Represents a 3D position relative to the world
	 */
	union WorldPosition {
		struct {
			int64_t x : 22;
			int64_t y : 22;
			int64_t z : 20;
		};
		int64_t raw; /// Raw 64-bit representation

		bool operator==(const WorldPosition& other) const {
			return raw == other.raw;
		}

		bool operator<(const WorldPosition& other) const {
			return raw < other.raw;
		}
	};

	class World {
	private:
		std::map<WorldPosition, SubChunk> subChunks;

	public:
		/// @remarks Creates the sub-chunk if it does not already exist
		SubChunk* getSubChunk(const WorldPosition& pos);

		/// @returns std::nullopt if no voxel exists at the given position
		std::optional<Voxel> getVoxel(const WorldPosition& pos);

		/// @remarks Pass std::nullopt to remove the voxel at the given position
		void setVoxel(const WorldPosition& pos, std::optional<Voxel> voxel);

	private:
		void ensureSubChunkExists(const WorldPosition& pos);
		void removeSubChunkIfEmpty(const WorldPosition& pos);
	};
} // namespace Blocky
