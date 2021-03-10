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
    double wishX = x;
    double wishY = y;


    if (left) {
        if (velocityX > -movementSpeed)
            velocityX -= movementSpeed * 0.5 * delta;
    wishX += velocityX * delta * (run ? 2.0 : 1.0);
    }
    if (right) {
        if (velocityX < movementSpeed)
            velocityX += movementSpeed * 0.5 * delta;
        wishX += velocityX * delta * (run ? 2.0 : 1.0);
    }

    if (velocityY > -gravity) {
        velocityY -= gravity * delta / 3.0f;
    }

    wishY -= velocityY * delta;

    // finn brikker som er rundt og så stopp om du må.
        // går oppover

    float centerX = wishX + 0.5f;
    float centerY = wishY + 0.5f;

    Tile *stopX = map.shouldStopAtTileNearX(velocityX, centerX, centerY);
    if (stopX != nullptr) {
        x = stopX->x + (velocityX < 0 ? 1 : -1); // - (velocityX < 0 ? 1 : -1);
        velocityX = 0;
    } else {
        x = wishX;
    }

    auto stopY = map.shouldStopAtTileNearY(velocityY, centerX, centerY);
    if (stopY != nullptr) {
        y = stopY->y - (velocityY < 0 ? 1 : -1);
        velocityY = 0;
    } else {
        y = wishY;
    }


    // tegning av figur status velging
    // Oppover
    if (velocityY >= 0.3) {
        status = 1;
    // Fall
    } else if (velocityY <= -0.3) {
        status = 2;
    // I luften
    } else if (velocityY != 0) {
        status = 3;
    // I bevegelse
    } else if (velocityX != 0){
        status = 4;
    // Stillestående
    } else {
        status = 0;
    }
}

void Player::render(Camera &camera, Shader &shader) {
    int realSelectedSprite = 0;
    switch (status) {
        // Stillestående
        case 0:
            realSelectedSprite = ((int) selectedSprite) % idleSize;
        break;
        // Oppover
        case 1:
            realSelectedSprite = idleSize + 1;
        break;
        // Fall
        case 2:
            realSelectedSprite = idleSize + jumpSize;
        break;
        // I luften
        case 3:
            realSelectedSprite = idleSize + (jumpSize - 1);
        break;
        // Bevegelse
        case 4:
            realSelectedSprite = ((int)selectedSprite) % runSize + idleSize + jumpSize + fallSize;
        break;
    }

    sprites.at(realSelectedSprite).render(x, y, camera.pos, shader, flipDirectionX);
}
