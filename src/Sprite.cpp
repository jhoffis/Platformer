//
// Created by Jens Benz on 06.03.2021.
//

#include "Sprite.h"

void spriteUpdateTileSize() {
    float aspect = Window::HEIGHT / Window::WIDTH;
    Sprite::realTileWidth = tileSize * aspect;
    Sprite::realTileHeight = tileSize;
}

void Sprite::render(glm::vec3 viewPos, Shader &shader, bool keepModelPos) {
    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

//    viewPos.y = 1.0f - viewPos.y;

    if (keepModelPos)
        shader.uniformMatrix4(glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(modelPos.x, -modelPos.y, 0))), "model");
    else
        shader.uniformMatrix4(glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(0))), "model");
    shader.uniformMatrix4(glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(viewPos.x, -viewPos.y, 0))), "view");

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}


// FIXME Skal egt telle fra -1.0 til 1.0
bool Sprite::isAbove(glm::vec3 viewPos, int mX, int mY) {
    int x = (viewPos.x + modelPos.x) / 2.0f * Window::WIDTH;
    int y = -(-viewPos.y - modelPos.y) / 2.0f * Window::HEIGHT;
    int w = realTileWidth / 2.0f * Window::WIDTH;
    int h = realTileHeight / 2.0f * Window::HEIGHT;

    return (mX < x + w && mX >= x) && (mY < y + h && mY >= y);
}
