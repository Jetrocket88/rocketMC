#pragma once

enum class BlockType {
    AIR,
    DIRT,
    GRASS,
    STONE
};

enum class BlockShape {
    FULL,
    HALF
};

struct BlockGpu {
    size_t tex_atlas; 
    /*
        Ok so this is important
        This number, tex_atlas, tells us where the first face of that block is in the texture atlas
        All the other faces, can be determined from an offset to that number 
        Once we have the row and col of the face we want (in the atlas), we can use the tile_uv function from the renderer
        to convert this to the raw tex coordinates
    */
    BlockShape shape;
    float transparency;
};


