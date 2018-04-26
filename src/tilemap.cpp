#include "tilemap.h"
#include <fstream>
#include "log.h"
#include "tiletype.h"

TileMap::TileMap(Window *window, std::string filename) : mapFilename(filename),
                                                         window(window)
{
    tilesheet = new Sprite(window, "assets/tileset.png");
    loadTiles(mapFilename);
}

TileMap::~TileMap()
{
    delete tilesheet;
    for(std::vector<Rectangle*>::iterator it = tileClips.begin(); it != tileClips.end(); it++ )
    {
        delete (*it);
    }
    tileClips.clear();
    tiles.clear();
}

void TileMap::render(float cameraX, float cameraY)
{
    for (auto tile : tiles)
    {
        tilesheet->crop(tileClips[tile->getTileType()]);
        tilesheet->render(tile->position->x - cameraX,
                          tile->position->y - cameraY);
    }
}

void TileMap::loadTiles(std::string filename)
{
    std::ifstream map(filename);
    int totalTiles;
    int tilesOnY;

    if (!map.is_open())
    {
        Log::error("Unable to load file: " + filename);
    }
    else
    {
        map >> totalTiles;
        map >> tileWidth;
        map >> tileHeight;
        map >> levelWidth;
        map >> levelHeight;
        map >> tilesOnY;

        if (map.fail())
        {
            Log::error("Error: unexpected end of file!");
            map.close();
            return;
        }
        //empty
        tileClips.reserve(1);
        int widthX = 0;
        int heightY = 0;
        int yTiles = 0;
        for (size_t i = 0; i < totalTiles; i++)
        {
            yTiles ++;
            tileClips.push_back(new Rectangle((float)widthX, (float)heightY, tileWidth, tileHeight));
            widthX += tileWidth;
            if (yTiles >= tilesOnY)
            {
                yTiles = 0;
                widthX = 0;
                heightY += tileHeight;
            }
        }
        tileClips[0] = new Rectangle((float)widthX, (float)heightY, tileWidth, tileHeight);

        for (size_t y = 0; y < levelHeight; y++)
        {
            for (size_t x = 0; x < levelWidth; x++)
            {
                int type;
                map >> type;
                if (type != TileType::EMPTY_TILE){
                    tiles.push_back(new Tile((float)x * tileWidth, (float)y * tileHeight, tileWidth, tileHeight, (TileType)type));
                }
            }
        }
        
    }
    
    map.close();
}

std::vector<Tile *> TileMap::getTiles()
{
    return tiles;
}

std::string TileMap::getMapFilename()
{
    return mapFilename;
}