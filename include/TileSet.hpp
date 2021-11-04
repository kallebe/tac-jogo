#ifndef TILESET_HPP
#define TILESET_HPP

#include "Sprite.hpp"
#include <string.h>

using namespace std;

class TileSet {
  private:
    Sprite *tileSet;
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;
  
  public:
    TileSet(int tileWidth, int tileHeight, string file);
    void RenderTile(int index, float x, float y);
    int GetTileWidth();
    int GetTileHeight();
};

#endif
