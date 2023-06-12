//
// Created by Jens Benz on 06.03.2021.
//

#include "Sprite.h"

void spriteUpdateTileSize() {
    float aspect = Window::HEIGHT / Window::WIDTH;
    Sprite::realTileWidth = tileSize * aspect;
    Sprite::realTileHeight = tileSize;
}

Math::Vec3 realTilePos(float tileX, float tileY) {
    // trenger ikke å bruke annet enn window aspect for å bestemme variasjon. Bruk så opengl størrelse for å si størresle på en tile.
    return Math::Vec3{
        .x = tileX * Sprite::realTileWidth,
        .y = tileY * Sprite::realTileHeight,
        .z = 0
    };
}

void Sprite::render(float tileX, float tileY, Math::Vec3 &viewPos, Shader &shader, bool flipSideways) const {
    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

    auto modelPos = realTilePos(tileX, tileY);
    auto modelMat = Math::Mat{};
    modelMat.setTranslate(Math::Vec3(modelPos.x, -modelPos.y, 0));
    auto viewMat = Math::Mat{};
    viewMat.setTranslate(Math::Vec3(viewPos.x, -viewPos.y, 0));

    shader.uniformMatrix4(modelMat, "model");
    shader.uniformMatrix4(viewMat, "view");
    shader.uniformBool(flipSideways, "flipSideways");

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Sprite::render(int mX, int mY, Shader &shader, bool flipSideways) const {
    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);

    shader.uniformMatrix4(Math::Mat{}, "model");
    auto viewMat = Math::Mat{};
    viewMat.setTranslate(Math::Vec3(mX / Window::WIDTH * 2.0f - Sprite::realTileWidth / 2.0f,
                                    -mY / Window::HEIGHT * 2.0f + Sprite::realTileHeight / 2.0f, 0));
    shader.uniformMatrix4(viewMat, "view");
    shader.uniformBool(flipSideways, "flipSideways");

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

bool Sprite::isAbove(int tileX, int tileY, Math::Vec3 &viewPos, int mX, int mY) {
    auto modelPos = realTilePos(tileX, tileY);
    int x = (viewPos.x + modelPos.x) / 2.0f * Window::WIDTH;
    int y = -(-viewPos.y - modelPos.y) / 2.0f * Window::HEIGHT;
    int w = realTileWidth / 2.0f * Window::WIDTH;
    int h = realTileHeight / 2.0f * Window::HEIGHT;

    return (mX < x + w && mX >= x) && (mY < y + h && mY >= y);
}
