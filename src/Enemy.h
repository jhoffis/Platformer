#ifndef PLATFORMER_ENEMY_H
#define PLATFORMER_ENEMY_H
#include "src/Map.h"

class Enemy {
    double selectedSprite = 0;
    std::vector<Sprite> sprites;



    Enemy(const char *imgPath, float tilemapPixelSize);
    void tick(double delta);
    void render(Camera &camera, Shader &shader);
};


#endif //PLATFORMER_ENEMY_H
