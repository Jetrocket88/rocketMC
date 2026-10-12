#include "gameplay/world.hpp"


void World::init() {
    chunks = std::make_unique<Chunk[]>(num_chunks);
}
