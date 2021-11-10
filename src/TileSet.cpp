#include "TileSet.hpp"
#include <iostream>

TileSet::TileSet(int tileWidth, int tileHeight, string file) {
  this->tileWidth  = tileWidth;
  this->tileHeight = tileHeight;

  GameObject *go = new GameObject();
  go->box.x = 0;
  go->box.y = 0;

  tileSet = new Sprite(*go);
  tileSet->Open(file);
  
  rows    = tileSet->GetHeight() / tileHeight;
  columns = tileSet->GetWidth() / tileWidth;
}

void TileSet::RenderTile(int index, float x, float y) {
  if (index < 0 || index > (rows * columns)) {
    return;
  }
  int xpos = (index < columns) ? (index * tileWidth) : ((index % columns) * tileWidth);
  int ypos = (index / columns) * tileHeight;
  tileSet->SetClip(xpos, ypos, tileWidth, tileHeight);
  
  tileSet->Render(x, y);
}

int TileSet::GetTileWidth() {
  return this->tileWidth;
}

int TileSet::GetTileHeight() {
  return this->tileHeight;
}
