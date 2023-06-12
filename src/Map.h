//
// Created by jh on 3/8/2021.
//

#ifndef PLATFORMER_MAP_H
#define PLATFORMER_MAP_H
#include <vector>
#include "Sprite.h"
#include "camera.h"

enum TileType {
    NORMAL, SPIKE, FINISH
};

struct Tile {
    TileType tileType = NORMAL;
    int x = 0, y = 0;
    unsigned int pointerToSprite = 0, frames = 1;
    double selectedSprite = 0.0;
};

struct Map {
    int selectedSprite = -1;
    std::vector<Sprite> palette;
    Math::Vec3 palettePos;
    std::vector<Tile> mapOfTiles;
    float width, height;
    void destroy();
    bool selectPalette(int button, int mX, int mY);
    void placePalette(Math::Vec3 &newTilePos);
    void removePalette(Math::Vec3 &newTilePos);
    int getTileIndex(int pal, int x, int y);
    void updateTileIndex(int pal, int x, int y);
    void create(const char *imgPath, float tilemapPixelSize);
    void render(Camera::Cam &camera, Shader &shader);

    void load();
    void save();

    Tile* getTileAt(int x, int y);
    Tile*  shouldStopAtTileNearX(float velocityX, float x, float y);
    Tile*  shouldStopAtTileNearY(float velocityY, float x, float y);
};
inline Map map{};
inline bool editMode = true;


#endif //PLATFORMER_MAP_H
