#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "GameObject.hpp"
#include "Component.hpp"
#include "TileSet.hpp"
#include <vector>
#include <string>

#define TILEMAP_WIDTH  1408
#define TILEMAP_HEIGHT 1280

using namespace std;

class TileMap : public Component {
  private:
    vector<int> tileMatrix;
    TileSet *tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
  
  public:
    TileMap(GameObject &associated, string file, TileSet *tileSet);
    
    void Load(string file);
    void SetTileSet(TileSet *tileSet);
    int& At(int x, int y, int z = 0);
    void Render();
    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
    int  GetWidth();
    int  GetHeight();
    int  GetDepth();
    void Update(float dt) {}
    void Start() {}
    bool Is(string type);
};

#endif
