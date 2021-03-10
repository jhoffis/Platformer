#ifndef PLATFORMER_PLAYER_H
#define PLATFORMER_PLAYER_H

#include "src/Map.h"

struct Player {
    const unsigned int idleSize = 4, jumpSize = 3, fallSize = 1, runSize = 6; // hvor mange bilder der index er feks idle + jump + 3
    unsigned int status = 0;

    double selectedSprite = 0;
    std::vector<Sprite> sprites;

    double movementSpeed = 0.3;
    const double gravity = 0.65, initVelocityY = -1.4;
    float x, y, velocityX, velocityY;

    bool left, right, run, jumping, flipDirectionX;
    void setLeft(bool left) {
        if (this->left != left) {
            this->left = left;
            flipDirectionX = true;
            velocityX = 0;
        }
    }
    void setRight(bool right) {
        if (this->right != right) {
            this->right = right;
            flipDirectionX = false;
            velocityX = 0;
        }
    }

    void create(const char *imgPath, float tilemapPixelSize);
    void tick(double delta);
    void render(Camera &camera, Shader &shader);

    void jump() {
        jumping = true;
        velocityY = initVelocityY;
    }
};
static inline Player player{};

#endif //PLATFORMER_PLAYER_H
