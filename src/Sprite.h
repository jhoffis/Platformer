#ifndef PLATFORMER_SPRITE_H
#define PLATFORMER_SPRITE_H

#include "src/engine/io/Window.h"
#include "src/Camera.h"

static const float tileSize = 24.0f / 1440.0f * 14.0f;

void spriteUpdateTileSize();
glm::vec3 realTilePos(float tileX, float tileY);

class Sprite {
private:
    unsigned int VBO{}, VAO{}, EBO{}, texture{};
public:
    inline static float realTileWidth{}, realTileHeight{};

    Sprite(int tilemapX, int tilemapY, float texW, float texH, auto texture) {
        this->texture = texture;

        const auto realX = -1.0f;
        const auto realY = 1.0f;

        const float vertices[] = {
                realX + realTileWidth,  realY,  0.0f, 1.0f, 0.0f, 0.0f,   (tilemapX + 1) * texW,    1.0f - tilemapY * texH,          // oppe til høyre
                realX + realTileWidth , realY - realTileHeight, 0.0f,  0.0f, 1.0f, 0.0f,   (tilemapX + 1) * texW,    1.0f - (tilemapY + 1) * texH,      // nede til høyre
                realX,                  realY - realTileHeight, 0.0f,  0.0f, 0.0f, 1.0f,   tilemapX * texW,    1.0f - (tilemapY + 1) * texH,      // nede til venstre
                realX,                  realY, 0.0f,   0.5f, 0.5f, 1.0f,  tilemapX * texW,    1.0f - tilemapY * texH,          // oppe til venstre
        };

        unsigned int indices[] = {  // note that we start from 0!
                0, 1, 3,   // first triangle
                1, 2, 3    // second triangle
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);

    }

    void destroy() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void render(float tileX, float tileY, glm::vec3 &viewPos, Shader &shader, bool flipSideways) const;
    void render(int mX, int mY, Shader &shader, bool flipSideways) const;

    static bool isAbove(int tileX, int tileY, glm::vec3 &viewPos, int mX, int mY);
};


inline static const glm::vec3 screenCoordToTilePos(int mX, int mY, glm::vec3 &viewPos) {
    // trenger ikke å bruke annet enn window aspect for å bestemme variasjon. Bruk så opengl størrelse for å si størresle på en tile.

    auto asd =  0.0f;

    auto pos = glm::vec3( (int) (((float) mX * 2.0f / Window::WIDTH + asd - viewPos.x) / Sprite::realTileWidth),
                          (int) (((float)mY * 2.0f / Window::HEIGHT + asd - viewPos.y) / Sprite::realTileHeight), 0);
    std::cout << "Place X: " << pos.x << " Place Y: " << pos.y << std::endl;
    return pos;
}



#endif //PLATFORMER_SPRITE_H
