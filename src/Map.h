//
// Created by jh on 3/8/2021.
//

#ifndef PLATFORMER_MAP_H
#define PLATFORMER_MAP_H
#include <vector>
#include "Sprite.h"

struct Tile {
    int x, y;
    unsigned int pointerToSprite;
};

struct Map {
    int selectedSprite = -1;
    std::vector<Sprite> palette;
    glm::vec3 palettePos;
    std::vector<Tile> mapPointToTileIndices;
    float width, height;
    void destroy();
    void selectPalette(int button, int mX, int mY, glm::vec3 &viewPos);
    void create(const char *imgPath, float tilemapPixelSize);
    void render(Camera &camera, Shader &shader);
};
inline Map map{};


#endif //PLATFORMER_MAP_H
