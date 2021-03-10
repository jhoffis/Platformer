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

void Player::tick(double delta) {
    selectedSprite += delta * 0.5;

    if (left) {
        if (velocityX > -movementSpeed)
            velocityX -= movementSpeed * 0.5 * delta;
        x += velocityX * delta * (run ? 2.0 : 1.0);
    }
    if (right) {
        if (velocityX < movementSpeed)
            velocityX += movementSpeed * 0.5 * delta;
        x += velocityX * delta * (run ? 2.0 : 1.0);
    }

    if (velocityY > -gravity) {
        velocityY -= gravity * delta / 3.0f;
    }

    y -= velocityY * delta;

    if (y > 3) {
        y = 3;
        velocityY = 0;
    }

    // tegning av figur status velging
    if (velocityY > 0) {
        status = 1;
    } else if (velocityY < 0) {
        status = 2;
    } else if (velocityX != 0){
        status = 3;
    } else {
        status = 0;
    }
}

void Player::render(Camera &camera, Shader &shader) {
    int realSelectedSprite = 0;
    switch (status) {
        case 0:
            realSelectedSprite = ((int) selectedSprite) % idleSize;
        break;
        case 1:
            realSelectedSprite = ((int) selectedSprite) % idleSize + jumpSize;
        break;
        case 2:
            realSelectedSprite = ((int) selectedSprite) % idleSize + jumpSize + fallSize;
        break;
        case 3:
            realSelectedSprite = ((int) selectedSprite) % idleSize + jumpSize + fallSize + runSize;
        break;
    }

    sprites.at(realSelectedSprite).render(x, y, camera.pos, shader, flipDirectionX);
}
