#pragma once

#include "block.hpp"
#include "renderer/vertex.hpp"

#include <array>
#include <cstdint>
#include <iostream>
#include <vector>

struct ChunkMesh {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

class Chunk {
  private:
    ChunkMesh m_chunk_mesh{};
    std::array<BlockType, 16 * 16 * 256> m_blocks{};

  public:
    //Generates the chunk mesh from the visible faces
    //and adds that information to the internal chunk mesh struct
    void generate_chunk_mesh();
};
