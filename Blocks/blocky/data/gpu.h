#pragma once

#include "block.h"
#include "vertex.h"

#include <cstdint>

namespace Blocky {
	struct BlockVertexPull {
		uint16_t blockID;
		uint16_t metadata;

		uint8_t xz;
		uint8_t y;

		BlockVertexPull(Voxel block, LocalPosition localPos) 
			: blockID(static_cast<uint16_t>(block.id)),
			  metadata(block.metadata.raw),
			  xz(static_cast<uint8_t>((localPos.x << 4) | (localPos.z))),
			y(static_cast<uint8_t>(localPos.y)) {
		}
	};
} // namespace Blocky
