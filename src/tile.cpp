#include "tile.h"

Tile::Tile(float x, float y, int w, int h, TileType type) : GameObject(x, y, w, h),
                                                            tileType(type)
{
}

Tile::~Tile()
{
}

TileType Tile::getTileType()
{
    return tileType;
}

void Tile::update(float dt)
{
}
void Tile::render(float cameraX, float cameraY)
{
}
