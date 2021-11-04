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
  
  rows    = this->tileSet->GetHeight() / tileHeight;
  columns = this->tileSet->GetWidth() / tileWidth;
}

void TileSet::RenderTile(int index, float x, float y) {
  if (index < 0 || index > (rows * columns)) {
    cout << "Indice do TileSet invalido!\n";
    return;
  }
  
  tileSet->Render(x, y);
}

int TileSet::GetTileWidth() {
  return this->tileWidth;
}

int TileSet::GetTileHeight() {
  return this->tileHeight;
}
