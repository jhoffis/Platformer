//
// Created by jh on 3/9/2021.
//

#include "Player.h"

void Player::create(const char *imgPath, float tilemapPixelSize) {
    auto img = createCharImage(imgPath, true);
    auto w = static_cast<unsigned>((float) img.w / tilemapPixelSize);
    auto h = static_cast<unsigned>((float) img.h / tilemapPixelSize);

    float texW = tilemapPixelSize / (float) img.w;
    float texH = tilemapPixelSize / (float) img.h;

    unsigned int texture = createTexture(img);

    for (int i = 0; i < w * h; i++) {
        int x = i % w;
        int y = i / w;
        sprites.emplace_back(x, y, texW, texH, texture);
    }
}

void Player::render(Camera &camera, Shader &shader, double delta) {
    selectedSprite += delta * 0.5;

    double movementSpeed = 0.3;
    if (left) {
        x -= movementSpeed * delta;
    }
    if (right) {
        x += movementSpeed * delta;
    }
    if (jump) {
        y -= movementSpeed * delta;
    }

    int realSelectedSprite = 0;
    switch (status) {
        case 0:
            realSelectedSprite = ((int) selectedSprite) % idleSize;
        break;
        case 1:
            realSelectedSprite = ((int) selectedSprite) % idleSize + jumpSize;
        break;
        case 2:
        break;
        case 3:
            realSelectedSprite = ((int) selectedSprite) % idleSize + jumpSize + fallSize + runSize;
        break;
    }

    sprites.at(realSelectedSprite).render(x, y, camera.pos, shader);
}
