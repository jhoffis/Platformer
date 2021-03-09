//
// Created by Jens Benz on 06.03.2021.
//

#include "Sprite.h"

void spriteUpdateTileSize() {
    float aspect = Window::HEIGHT / Window::WIDTH;
    Sprite::realTileWidth = tileSize * aspect;
    Sprite::realTileHeight = tileSize;
}

glm::vec3 realTilePos(int tileX, int tileY) {
    // trenger ikke å bruke annet enn window aspect for å bestemme variasjon. Bruk så opengl størrelse for å si størresle på en tile.
    return glm::vec3((float) tileX * Sprite::realTileWidth, (float) tileY * Sprite::realTileHeight, 0);
}

void Sprite::render(int tileX, int tileY, glm::vec3 &viewPos, Shader &shader) const {
    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

    auto modelPos = realTilePos(tileX, tileY);
    shader.uniformMatrix4(glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(modelPos.x, -modelPos.y, 0))), "model");
    shader.uniformMatrix4(glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(viewPos.x, -viewPos.y, 0))), "view");

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Sprite::render(int mX, int mY, Shader &shader) const {
    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);

    shader.uniformMatrix4(glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(0))), "model");
    shader.uniformMatrix4(glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(
            mX / Window::WIDTH * 2.0f - Sprite::realTileWidth / 2.0f,
            -mY / Window::HEIGHT * 2.0f + Sprite::realTileHeight / 2.0f, 0))), "view");

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}


bool Sprite::isAbove(int tileX, int tileY, glm::vec3 &viewPos, int mX, int mY) {
    auto modelPos = realTilePos(tileX, tileY);
    int x = (viewPos.x + modelPos.x) / 2.0f * Window::WIDTH;
    int y = -(-viewPos.y - modelPos.y) / 2.0f * Window::HEIGHT;
    int w = realTileWidth / 2.0f * Window::WIDTH;
    int h = realTileHeight / 2.0f * Window::HEIGHT;

    return (mX < x + w && mX >= x) && (mY < y + h && mY >= y);
}
