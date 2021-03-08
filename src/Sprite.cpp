//
// Created by Jens Benz on 06.03.2021.
//

#include "Sprite.h"

void spriteUpdateTileSize() {
    float aspect = Window::HEIGHT / Window::WIDTH;
    realTileWidth = tileSize * aspect;
    realTileHeight = tileSize;
}

void Sprite::render(const Camera &camera, Shader &shader) {
    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

    shader.uniformMatrix4(glm::value_ptr(glm::translate(glm::mat4(1.0f), modelPos)), "model");
    shader.uniformMatrix4(glm::value_ptr(camera.view), "view");

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
