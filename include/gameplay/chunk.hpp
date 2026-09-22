#pragma once

#include <array>
#include "block.hpp"

class Chunk {
  private:
    std::array<BlockType, 16*16*256> blocks {};

  public:
};
