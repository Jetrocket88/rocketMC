#pragma once

#include "chunk.hpp"

#include <iostream>
#include <memory>
#include <vector>

class World {
  public:
    void init();
    size_t num_chunks{1};
    std::unique_ptr<Chunk[]> chunks{};
  private:
};
