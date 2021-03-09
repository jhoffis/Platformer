//
// Created by jh on 3/8/2021.
//

#ifndef PLATFORMER_MAP_H
#define PLATFORMER_MAP_H
#include <vector>
#include "Sprite.h"

struct Tile {
    int x, y;
    bool collideTop{}, collideBot{}, collideLeft{}, collideRight{};
    unsigned int pointerToSprite;
};

struct Map {
    int selectedSprite = -1;
    std::vector<Sprite> palette;
    glm::vec3 palettePos;
    std::vector<Tile> mapOfTiles;
    float width, height;
    void destroy();
    bool selectPalette(int button, int mX, int mY);
    void placePalette(glm::vec3 &newTilePos);
    void removePalette(glm::vec3 &newTilePos);
    void create(const char *imgPath, float tilemapPixelSize);
    void render(Camera &camera, Shader &shader);
};
inline Map map{};
inline bool editMode = true;


#endif //PLATFORMER_MAP_H
