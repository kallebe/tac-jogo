#include "TileMap.hpp"
#include <fstream>
#include <iostream>

TileMap::TileMap(GameObject &associated, string file, TileSet *tileSet) : Component(associated) {
  Load(file);
  SetTileSet(tileSet);
}

void TileMap::Load(string file) {
  ifstream infile(file);

  if (infile.is_open()) {
    int number;
    char comma;

    infile >> number >> comma;
    mapWidth = number;

    infile >> number >> comma;
    mapHeight = number;

    infile >> number >> comma;
    mapDepth = number;

    while (!infile.eof()) {
      infile >> number >> comma;
      tileMatrix.push_back(number);
    }
    
    infile.close();
  }
}

void TileMap::SetTileSet(TileSet *tileSet) {
  this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
  int position = x + (mapWidth * y) + (mapHeight * z);
  return tileMatrix[position];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      tileSet->RenderTile(At(x, y, layer), (x * tileSet->GetTileWidth() + cameraX), (y * tileSet->GetTileHeight() + cameraY));
    }
  }
}

void TileMap::Render() {
  for (int z = 0; z < mapDepth; z++)
    RenderLayer(z, associated.box.x, associated.box.y);
}

int TileMap::GetWidth() {
  return mapWidth;
}

int TileMap::GetHeight() {
  return mapHeight;
}

int TileMap::GetDepth() {
  return mapDepth;
}

bool TileMap::Is(string type) {
  return type == "TileMap";
}
