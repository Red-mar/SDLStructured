#ifndef TILE_H
#define TILE_H

#include "gameobject.h"
#include "tiletype.h"

class Tile : public GameObject
{
  public:
    Tile(float x, float y, int w, int h, TileType type);
    ~Tile();

    TileType getTileType();

    void update(float dt);
    void render(float cameraX = 0, float cameraY = 0);

  private:
    TileType tileType;
};

#endif // !TILE_H
