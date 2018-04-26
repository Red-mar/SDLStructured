#ifndef TILEMAP_H
#define TILEMAP_H


#include "sprite.h"
#include "tile.h"
#include <vector>

class TileMap
{

  public:
    TileMap(Window *window, std::string filename);
    ~TileMap();

    void render(float cameraX, float cameraY);
    void update(float dt);

    std::vector<Tile *> getTiles();
    std::string getMapFilename();
    void reloadSprite();

  private:
    Window *window;
    int tileHeight;
    int tileWidth;

    int levelWidth;
    int levelHeight;

    std::string mapFilename;

    Sprite *tilesheet;
    std::vector<Rectangle *> tileClips;
    std::vector<Tile *> tiles;

    void loadTiles(std::string filename);
};

#endif // !TILEMAP_H
