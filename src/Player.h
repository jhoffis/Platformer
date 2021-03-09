#ifndef PLATFORMER_PLAYER_H
#define PLATFORMER_PLAYER_H

#include "src/Map.h"

struct Player {
    const unsigned int idleSize = 4, jumpSize = 3, fallSize = 1, runSize = 6; // hvor mange bilder der index er feks idle + jump + 3
    unsigned int status = 0;

    double selectedSprite = 0;
    std::vector<Sprite> sprites;

    float x, y;
    bool left, right, jump;

    void create(const char *imgPath, float tilemapPixelSize);
    void render(Camera &camera, Shader &shader, double delta);
};
static inline Player player{};

#endif //PLATFORMER_PLAYER_H
